/*
 * varibles used by main program
 * 
 * shouldn't need to be edited
 */

#ifndef varibles_h
#define varibles_h

/* General */
bool restartRequired = false;   // have we told the device to restart?
bool factoryRequired = false;   // have we told the device to factory reset?

const char* PARAM_ID = "ID"; // used for wifi button
unsigned long timeout;       // used to ensure we don't get an indefinetly hold from wifi button
uint8_t WIFIbuttonSTATE[4] = {1,1,1,1};

unsigned long lastDelete = 0;   // gives time for factory reset to change url then delete data and reboot

unsigned long lastUpdate;       // used to keep track of updates to webpage with websocket json
uint8_t ws_connected;           // keep track of the number of clients connected

float new_sat;                  // used by ESP_color for calculating the Saturation Level
uint8_t white_reverse;          // used for flipping the white LED level for calculating the new Saturation level

/* Buttons */
int buttons[5]  = {13,14,12,2};        // pin button is connected to

/* MCP Pinout */
uint8_t mcp_update[5] = {false};       // used to limit constant updates
uint8_t MCP_en[5]     = {7,5,3,1};     // pin power fets connected on mcp
uint8_t MCP_data[5]   = {6,4,2,0};     // pin data  fets connected on mcp

/* LED's */
#define LED_PIN                0                    // pin neopixels are connected to -- shouldn't need to be changed
#define LED_COUNT              4                    // number of neopixels
#define LED_TYPE               NEO_GRBW             // type of led's used
uint8_t neo_update[5]          = {false};           // do led's need to be updated - prevents flickering from constant updates
uint8_t neo_override[5]        = {false};           // do led's need to be updated - prevents flickering from constant updates -- used in overrideMODE
unsigned long lastdouble;                           // used for double flash animation
uint8_t       doubletime;                           // used for double flash animation
uint8_t       ledState         = LOW;               // ledState used to set the LED flash
uint8_t       connected_update = false;             // update leds to show connection progress
uint8_t       ringspeed        = 250;               // speed in millis() for ring animation in voltage lockout
uint8_t       flashState[5]    = {LOW};             // array of current flash state -- helps with ensureing neopixel updates without spamming neopixel line causing flickering
uint8_t       prevflash[5]     = {LOW};             // array of last flash state    -- helps with ensureing neopixel updates without spamming neopixel line causing flickering
uint8_t       ledmode[5]       = {0};               // what mode the leds are in    -- used in overrideMODE control

/* varibles */
 uint8_t port_state[5] = {0,0,0,0}; //sets the state of the port 0 off, 1 power, 2 data+power
 uint8_t last_press[5] = {0,0,0,0}; // stores the last press if a button for the sketch to process, then reset (15 = hold)
 uint8_t port_INA[5]   = {0,0,0,0}; // state of an INA on a port - if failed to load it disables the port

/* voltage varibles */
float         busvoltage = 0;      // average voltage from all 4 sensors
unsigned long lastvoltread;        // last voltage reading
unsigned long lastvoltmqtt;        // last time the voltage was sent via mqtt
uint8_t       voltlockout;         // voltage lockout - 0 = off / safe 1 = under volt 2 = over volt
uint8_t       voltlockout_prev;    // last volatge lockout varible - for reseting led's
uint8_t       fwd;                 // led aniamtion
uint8_t       fwd_prev;            // led aniamtion prev value
unsigned long prevringMillis = 0;  // speed of animation

/* current measurement varibles */
uint16_t       CALCmaxtotal   =  0 ; // how much power used by all ports
int            currentValue[5]= {0}; // initialization of current measurement
int            wattsValue[5]  = {0}; // initialization of current measurement
int            EMA_C[5]       = {0}; // initialization of EMA C  - filtered current measurement
int            EMA_W[5]       = {0}; // initialization of EMA C  - filtered current measurement
float          EMA_a          = 0.9; // initialization of EMA alpha
unsigned long  lastINAread[5] = {0}; // last time the current was read
unsigned long  lastINAmqtt[5] = {0}; // last time the current was sent via mqtt

/* mqtt topics */
const char* out_heart  = "-";  // LWT        topic

const char* out_topic1  = "-"; // button     topic
const char* out_topic2 = "-";  // port       topic
const char* out_topic3 = "-";  // volt       topic

const char* in_topic1 = "-";   // current    topic
const char* in_topic2 = "-";   // state      topic
const char* in_topic3 = "-";   // brightness topic
const char* in_topic4 = "-";   // override   topic
const char* in_topic5 = "-";   // RGBW       topic **only works in override mode**
const char* in_topic6 = "-";   // flash      topic **only works in override mode**

char clientheart[60];
char clientoutput1[60];
char clientoutput2[60];
char clientoutput3[60];

char clientinput1[60];
char clientinput2[60];
char clientinput3[60];
char clientinput4[60];
char clientinput5[60];
char clientinput6[60];

char connectphrase[140];     // publishes to 'outTopic' when connected
String IPaddress;            // IP address for 'outTopic'
char mqtt_button_buffer[40]; // message from button buffer
char mqtt_amp_buffer[100];   // message from INA buffer
char mqtt_volt_buffer[40];   // message from Volts buffer

const uint8_t mqtt_lwt_qos     = 0;
const uint8_t mqtt_lwt_retain  = 1;

/* mqtt config input */
uint8_t  mqttC;           // what port to change
uint16_t mqttCur;         // current that a port is being set to
String   mqttState;       // state that a port is being set to
uint8_t  rednew[5] = {0}; // new LED color for override MODE     -- RED
uint8_t  grnnew[5] = {0}; // new LED color for override MODE     -- GREEN
uint8_t  blunew[5] = {0}; // new LED color for override MODE     -- BLUE
uint8_t  whinew[5] = {0}; // new LED color for override MODE     -- WHITE
 
 #endif
