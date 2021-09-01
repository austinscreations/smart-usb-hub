#ifndef config_h
#define config_h

/* ----------------- General config -------------------------------- */

/* Debugging */
#define DEBUG_BUTTONS          true  // prints out button state
#define DEBUG_WIFIBUTTONS      true  // prints out webpage button state
#define DEBUG_JSON             false // prints out parsed json
#define DEBUG_voltage          false // prints out voltage infomation
#define DEBUG_current          false // prints out current information

uint16_t    portcurrent[4] = {0};  // max current for a port - max 3A (parts limit) // over ridden by config above


/* Varibles here are filled in by the config system */
char        host[32];
char        ssid[32];
char        password[64];

char        AP_SSID[32];
char        AP_PASS[64];
uint8_t     AP_CHANNEL  = 1; // not written over
uint8_t     AP_HIDDEN;
uint8_t     AP_MAX_CON  = 1; // not written over

char        mqtt_broker[32];
uint16_t    mqtt_port;
char        mqtt_username[32];
char        mqtt_password[32];

uint8_t     darkState;
char        htmltitle[32];
char        htmltype[32];
char        htmlcolor[10];
char        htmlhover[10];

uint16_t    systemcurrent;         // max current availble to the system (accounts for esp usage)***
uint16_t    portcurrent0;          // max current for a port - max 3A (parts limit) // will be used in json config
uint16_t    portcurrent1;          // max current for a port - max 3A (parts limit) // will be used in json config
uint16_t    portcurrent2;          // max current for a port - max 3A (parts limit) // will be used in json config
uint16_t    portcurrent3;          // max current for a port - max 3A (parts limit) // will be used in json config

uint8_t     brightness;            // set strip brightness

uint8_t     overrideMODE;          // are we allowing local control or only mqtt?
uint8_t     overrideWEB;           // can the web interface control the hub?

#endif
