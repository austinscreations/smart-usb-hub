/*
 * varibles used by main program
 * 
 * shouldn't need to be edited
 */

#ifndef varibles_h
#define varibles_h

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
unsigned long lastdouble;                           // used for double flash animation
uint8_t       doubletime;                           // used for double flash animation
uint8_t       ledState         = LOW;               // ledState used to set the LED flash
uint8_t       connected_update = false;             // update leds to show connection progress
uint8_t       ringspeed        = 250;               // speed in millis() for ring animation in voltage lockout

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
uint16_t       EMA_C[5]       = {0}; // initialization of EMA C  - filtered current measurement
uint16_t       EMA_W[5]       = {0}; // initialization of EMA C  - filtered current measurement
float          EMA_a          = 0.9; // initialization of EMA alpha
unsigned long  lastINAread[5] = {0}; // last time the current was read
unsigned long  lastINAmqtt[5] = {0}; // last time the current was sent via mqtt



/* mqtt topics */
const char* out_heart  = "-";

const char* out_topic1  = "-";
const char* out_topic2 = "-";
const char* out_topic3 = "-";

const char* in_topic1 = "-";
const char* in_topic2 = "-";

char clientheart[60];
char clientoutput1[60];
char clientoutput2[60];
char clientoutput3[60];

char clientinput1[60];
char clientinput2[60];

char connectphrase[140];     // publishes to 'outTopic' when connected
String IPaddress;            // IP address for 'outTopic'
char mqtt_button_buffer[40]; // message from button buffer
char mqtt_amp_buffer[100];   // message from INA buffer
char mqtt_volt_buffer[40];   // message from Volts buffer

/* mqtt config input */
uint8_t  mqttC;     // what port to change
uint16_t mqttCur;   // current that a port is being set to
String mqttState;   // state that a port is being set to
 

 #endif
