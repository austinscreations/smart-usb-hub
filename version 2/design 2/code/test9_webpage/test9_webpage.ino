/*
 * Started 2021-08-21
 * 
 * GOAL: have homepage interface refreshed
 * 
 * to be done:
 * send data via mqtt                                                        // done - test5
 * MQTT inputs                                                               // done - test7
 * over ride mode                                                            // done - test7
 * OTA + config                                                              // OTA not tested
 *  - setup main setup and loop functions                                    // done
 *  - adjust json save functions                                             // done
 *  - adjust website form params                                             // done
 *  - adjust wifi save string function                                       // done
 *  - add mqtt save function                                                 // done
 *  - add config items to %processor%                                        // done
 *  
 * debug output
 *  - Buttons                                                                // 
 *  - Buttons WIFI                                                           // 
 *  - neopixel for wifi and mqtt                                             // 
 *  - mqtt payload / callback                                                // 
 *  - current                                                                // 
 *  - voltage                                                                // 
 *  - json                                                                   // done
 *  
 * webpage                                                                   // 
 * 
 * 
 * add / double check comments                                               // 
 * 
 * 
 * 
 * add more / better debug output                                            // done - in manager test 8 OTA / AP / WEB
 * 
 * over current port state = 10 / double flash blue
 * over current hub        = 11 / double flash purple
 * 
 */

#include "FS.h"
#include "ESPAsyncWebServer.h"
#include <ArduinoJson.h>
#include "debug.h"             // embeded degug library

#if defined(ESP8266)
    #include "ESP8266WiFi.h"
    #include "ESPAsyncTCP.h"
    #include "flash_hal.h"
    #include <LittleFS.h>
#elif defined(ESP32)
    #include "WiFi.h"
    #include "AsyncTCP.h"
    #include "Update.h"
    #include "esp_int_wdt.h"
    #include "esp_task_wdt.h"
    #include "LITTLEFS.h"
#endif

#include "config.h"             // config information
#include "factory_settings.h"   // factory reset config


#include <PubSubClient.h>       // For MQTT
#include "buttons.h"            // embeded button library for handling multi press events
#include "varibles.h"           // non-edited varibles
#include <Adafruit_MCP23008.h>  // For Output Enables
#include <Adafruit_INA219.h>    // For Current Measurements
#include <Adafruit_NeoPixel.h>  // for SK6812 RGBW LEDs

/* WEB PAGES */
#include "homepage.h"           // website home page
#include "management.h"         // Website OTA page
#include "config_page.h"        // ESP html configuration page
#include "failed.h"             // Something failed webpage
#include "reboot.h"             // Website - ESP rebooting
#include "finished.h"           // OTA success Webpage
#include "config_finished.h"    // Saved Config Message Webpage
#include "factory_html.h"       // Factory Reset Performed Webpage

AsyncWebServer server(80);      // declare ASYNC server library
AsyncWebSocket ws("/ws");       // declare web socket

/* library constructors here */
WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, LED_TYPE + NEO_KHZ800);
multiButton button = multiButton();                // regular GPIO button
Adafruit_MCP23008 mcp;
Adafruit_INA219 ina219_0(0x40);
Adafruit_INA219 ina219_1(0x41);
Adafruit_INA219 ina219_2(0x44);
Adafruit_INA219 ina219_3(0x45);

#include "neopixel.h"           // embedded animations for neopixels          should be cpp

#include "wifisave.h"           // Saving new Config information              should be cpp
#include "processing_items.h"   // processor for webpage varibles             should be cpp
#include "customserver.h"       // manages the ASYNC server webpage serving   should be cpp
#include "wifi.h"               // manages the wifi and AP conenctions        should be cpp

#include "ESP_Color.h"          // embede library for changing RGB - HSV - HEX for webpage
#include "web_json.h"           // embedded handling of websocket json

#include "ina219.h"             // embedded functions for INA219 measurements should be cpp
#include "press.h"              // emdedded functions for handling port state should be cpp
#include "mqtt_setup.h"         // emdedded functions for wifi and mqtt       should be cpp

/* handlers for button callback */
char * getMqttButtonAction(uint8_t state)
{
  // Determine what action we need to publish
  static char action[7];
  switch (state)
  {
    case BUTTON_HOLD_STATE:
      sprintf_P(action, PSTR("HOLD"));
      break;
    case 1:
      sprintf_P(action, PSTR("SINGLE"));
      break;
    case 2:
      sprintf_P(action, PSTR("DOUBLE"));
      break;
    case 3:
      sprintf_P(action, PSTR("TRIPLE"));
      break;
    case 4:
      sprintf_P(action, PSTR("QUAD"));
      break;
    case 5:
      sprintf_P(action, PSTR("PENTA"));
      break;
    default:
      sprintf_P(action, PSTR("ERROR"));
      break;
  }
  return action;
}

void buttonPressed(uint8_t button, uint8_t state)
{
 
  // Determine the port, switch, and button numbers (1-based)
  uint8_t raw_button =  button;
  uint8_t mqtt_button = raw_button + 1;

  if (overrideMODE == false) // not in override mode --- when in override mode we only send the data out via mqtt
  {
    last_press[raw_button] = state; 
    lastINAread[raw_button] = millis(); // resets the time readout for reading current usage
    lastINAmqtt[raw_button] = millis(); // resets the time for the for mqtt current readout
  }
  else                                  // in override mode still check for triple press reset of over current port / hub
  {
    if (port_state[raw_button] == 10 )  // we are in an over port
    {
      if (state == 3)                   // make sure it was a triple press
      {
        last_press[raw_button] = state; // send triple press for reset from current cut off
      }
    }
    if (port_state[raw_button] == 11 )  // over current hub
    {
      if (state == 3)                   // make sure it was a triple press
      {
        last_press[raw_button] = state; // send triple press for reset from current cut off  
      }
    }
  }

  if (DEBUG_BUTTONS)
  {
    Serial.print(F("Press detected: "));
    Serial.print(F(" BUTTON: "));
    Serial.print(mqtt_button);
    Serial.print(F(" STATE: "));
    Serial.print(state);
    Serial.print(F(" ACTION: "));
    Serial.println(getMqttButtonAction(state));
  }
      sprintf_P(mqtt_button_buffer, PSTR("{\"BUTTON\":%d, \"ACTION\":\"%s\"}"), mqtt_button, getMqttButtonAction(state));
      client.publish(out_topic1, mqtt_button_buffer);
      Serial.print("mqtt output: ");
      Serial.println(mqtt_button_buffer);
}


void setup() {
  Serial.begin(115200);
  delay(500);                       // There has GOT to be a better way!!!
  DEBUG_Boot();                     // print device is booting

  DEBUG_Reset();                    // print reset reason

  parameterSETUP();                 // wifisave.h

  mcp.begin();                      //             - start MCP - controls data lines and power fets
    for (uint8_t o = 0; o < 8; o++) // set all the MCP pins to output
  {
    mcp.pinMode(o, OUTPUT);
  }

  portlockout();                    // press.h      - resets all ports to off

  strip.begin();                    //              - INITIALIZE NeoPixel strip object (REQUIRED)
  strip.setBrightness(brightness);  //              - set strip brightness
  colorWipe(0,0,0,0);               // neopixel.h   - turn all the led's off

  INA_SETUP();                      // ina219.h     - setup the INA sensors

  wifi_start();                     // start wifi   - will start AP / WiFi as needed - wifi.h

  initWebSocket();                  // start websocket

  customInit();                     // start server - starts ASYNC server - customserver.h


   if (strcmp(mqtt_broker, "0") == 0)               // no broker declared
    {Serial.println("no broker declared");}
    else                                            // broker declared
    {
      settopics();                                  // mqtt_setup.h - set mqtt topics
    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);
    }


  for (uint8_t i = 0; i < 4; i++)   // setup all the GPIO buttons
  {
   button.setup(i, buttons[i]);     // buttons.h - setup gpio butons
  }

  button.onButtonPressed(buttonPressed);

  DEBUG_Running();                // prints running ; as most items are setup at this point

}

void loop() {
ws.cleanupClients();                   // cleans up old websocket clients
wifi_checkup();                        // checks if wifi is still connected and starts AP as needed - wifi.h
if (restartRequired){OTA_Restart();}   // checks if the esp needs a reboot        - done via webpage / OTA - customserver.h
if (factoryRequired){deleteData();}    // checks if the esp needs a factory reset - done via webpage / OTA - customserver.h and wifisave.h

  if (WiFi.status() == WL_CONNECTED)   // check that we are connected to wifi before attempting mqtt
  {
    if (strcmp(mqtt_broker, "0") == 0) // no broker declared
    {}
    else                               // broker declared
    {
      if (!client.connected())
      {
        reconnect();
      }
     client.loop();
    }
  }

  if (connected_update == true) // if we are conencted to wifi and mqtt go green briefly
  {
    success();
  }

voltread();           // ina219.h   - read bus voltage
voltanimation();      // ina219.h   - handles the led aniamtions on under/over volt condition


if (ws_connected != 0)                 // we have a websocket client connected - send it data
{
  if ((millis() - lastUpdate) > 500)  // waiting an amount of time before resending
  {
    webSENDjson();                     // web_json.h - send json for websocket
  }
}


if (voltlockout == 0) // not in voltage lockout condition
{
  button.process();   // buttons.h  - process a button press

  handleportstate();  // press.h    - handles what state a port is in
  portsSTATE();       // press.h    - handles the ports being on, and led color
  overrideColor();    // neopixel.h - updates the neopixels when in override mode
}
else                  // turn ports off -- we are in an over / under voltage condition
{
  portlockout();      // press.h   - shuts off the ports in low / high voltage condition
}

} // end main loop
