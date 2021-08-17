#ifndef config_h
#define config_h

/* ----------------- General config -------------------------------- */

/* Debugging */
#define DEBUG_BUTTONS          true
#define DEBUG_voltage          false
#define DEBUG_current          false


/* Serial */
#define SERIAL_BAUD_RATE       115200

/* Variables */



/* Varibles here are filled in by the config system */
//char        host[32];
//char        ssid[32];
//char        password[64];

char        AP_SSID[32];
char        AP_PASS[64];
uint8_t     AP_CHANNEL  = 1; // not written over
uint8_t     AP_HIDDEN;
uint8_t     AP_MAX_CON  = 1; // not written over

//char        mqtt_broker[32];
//uint16_t    mqtt_port;
//char        mqtt_username[32];
//char        mqtt_password[32];

uint16_t    systemcurrent  = 650; // max current availble to the system (accounts for esp usage)***
uint16_t    portcurrent0   = 3000; // max current for a port - max 3A (parts limit) // will be used in json config
uint16_t    portcurrent1   = 3000; // max current for a port - max 3A (parts limit) // will be used in json config
uint16_t    portcurrent2   = 3000; // max current for a port - max 3A (parts limit) // will be used in json config
uint16_t    portcurrent3   = 3000; // max current for a port - max 3A (parts limit) // will be used in json config
uint16_t    portcurrent[5] = {0};  // max current for a port - max 3A (parts limit) // over ridden by config above

uint8_t     darkState;
char        htmltitle[32];
char        htmltype[32];
char        htmlcolor[10];
char        htmlhover[10];

uint8_t     overrideMODE = false; // are we allowing local control or only mqtt?
uint8_t     overrideWEB  = false; // can the web interface control the hub?

/* WIFI */ 
const char*   host             = "smartHUB";        // host name to show on wifi network && mqtt topics
const char*   ssid             = "";
const char*   password         = "";

/* MQTT */
const char*   mqtt_broker      = "192.168.0.54";    // IP address or host name of your MQTT broker
const int     mqtt_port        = 1883;

const char*   mqtt_username    = "";
const char*   mqtt_password    = "";

const uint8_t mqtt_lwt_qos     = 0;
const uint8_t mqtt_lwt_retain  = 1;


#endif
