/*
 * Started 2021-08-17
 * 
 * GOAL:
 * 
 * 
 * to be done:
 * send data via mqtt                                                        // done - test5
 * MQTT inputs                                                               // 
 *   - per port current config                                               // done
 *   - over ride mode                                                        // 
 *   - led control                                                           // 
 *   - port control                                                          // started 2021-08-17
 *   - brightness (non override mode)                                        //
 * over ride mode                                                            // 
 *   - control ports                                                         //
 *   - control leds                                                          //
 * OTA + config                                                              // 
 * webpage                                                                   // 
 * 
 * over current port state = 10 / double flash blue
 * over current hub        = 11 / double flash purple
 * 
 */

#include <ESP8266WiFi.h>        // For WiFi
#include <PubSubClient.h>       // For MQTT
#include "buttons.h"            // embeded button library for handling multi press events
#include "varibles.h"           // non-edited varibles
#include "config.h"             // varibles that my be edited upon upload or replaced by json
#include <Adafruit_MCP23008.h>  // For Output Enables
#include <Adafruit_INA219.h>    // For Current Measurements
#include <Adafruit_NeoPixel.h>  // for SK6812 RGBW LEDs

WiFiClient espClient;
PubSubClient client(espClient);

/* library constructors here */
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, LED_TYPE + NEO_KHZ800);
multiButton button = multiButton();
Adafruit_MCP23008 mcp;
Adafruit_INA219 ina219_0(0x40);
Adafruit_INA219 ina219_1(0x41);
Adafruit_INA219 ina219_2(0x44);
Adafruit_INA219 ina219_3(0x45);

#include "neopixel.h"           // embedded animations for neopixels
#include "ina219.h"             // embedded functions for INA219 measurements
#include "press.h"              // emdedded functions for handling port state
#include "wifi_setup.h"         // emdedded functions for wifi and mqtt



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

  last_press[raw_button] = state;
  lastINAread[raw_button] = millis();
  lastINAmqtt[raw_button] = millis();

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
  Serial.begin(SERIAL_BAUD_RATE); // start serial debugging
  delay(200);
  Serial.println("\n Starting");

  mcp.begin();                    //              - start MCP - controls data lines and power fets
  portlockout();                  // press.h      - resets all ports to off

  strip.begin();                  //              - INITIALIZE NeoPixel strip object (REQUIRED)
  colorWipe(0,0,0,0);             // neopixel.h   - turn all the led's off

  INA_SETUP();                    // ina219.h     - setup the INA sensors

  settopics();                    // wifi_setup.h - set mqtt topics
  WiFi.hostname(host);
  setup_wifi();                   // wifi_setup.h - starts wifi connection
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);

  for (uint8_t o = 0; o < 8; o++) // set all the MCP pins to output
  {
    mcp.pinMode(o, OUTPUT);
  }

  for (uint8_t i = 0; i < 4; i++) // setup all the GPIO buttons
  {
   button.setup(i, buttons[i]);   // buttons.h - setup gpio butons
  }

  button.onButtonPressed(buttonPressed);

  Serial.println("Setup Complete");

}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
   client.loop();

   if (connected_update == true){ // if we are conencted to wifi and mqtt go green briefly
      success();
    }

voltread();           // ina219.h  - read bus voltage
voltanimation();      // ina219.h  - handles the led aniamtions on under/over volt condition

if (voltlockout == 0) // not in voltage lockout condition
{
  button.process();   // buttons.h - process a button press
  handleportstate();  // press.h   - handles what state a port is in
  portsSTATE();       // press.h   - handles the ports being on, and led color
}
else                  // turn ports off
{
  portlockout();      // press.h   - shuts off the ports in low / high voltage condition
  /* add volt readout to mqtt  (delay 500)*/
}



}
