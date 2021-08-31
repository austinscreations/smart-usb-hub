/* Factory settings are saved here */

/* using factory reset button will revert to these settings */

#ifndef factory_settings_h
#define factory_settings_h

/* Device name / hostname - Hostname may not work on all DCHP setups - HOSTNAME IS USED WITH MQTT TOPICS*/
char       hostFACTORY[32]           = "smartHUB-Factory";

/* WIFI */
char       ssidFACTORY[32]           = "0";            // unconfigured ssid
char       passwordFACTORY[64]       = "0";            // wifi password

/* AP */
char       AP_SSIDFACTORY[32]         = "0";           // will revert to using host
char       AP_PASSFACTORY[64]         = "SUMpassword"; // AP password                                   *** Minimum 8 charcter value max 63 (64 with \n)
uint8_t    AP_HIDDENFACTORY           = 0;             // AP SSID brodcast                              hidden = 1

/* MQTT */
char       mqtt_brokerFACTORY[32]    = "0";            // IP address or host name of your MQTT broker
uint16_t   mqtt_portFACTORY          = 1883;           // port for MQTT broker
char       mqtt_usernameFACTORY[32]  = "0";            // undefined username for mqtt                   won't use a username or password in this case
char       mqtt_passwordFACTORY[32]  = "0";            // template password for mqtt user

/* HTML */
uint8_t   darkStateFACTORY           = 1;
char      htmltitleFACTORY[32]       = "Factory";      // main title on the top of webpage          
char      htmltypeFACTORY[32]        = "Factory";      // Device type on the bottom of webpage     
char      htmlcolorFACTORY[10]       = "#176fc1";      // main HTML webpage color                       Superhouse.tv color
char      htmlhoverFACTORY[10]       = "#00a5b4";      // html color for hovering over a menu button    Superhouse.tv color

/* smartHUB*/
uint16_t    systemcurrentFACTORY   = 5000;             // max current availble to the system - max 5A (parts limit)  -- rating of power supply
uint16_t    portcurrent0FACTORY    = 3000;             // max current for a port             - max 3A (parts limit)  // will be used in json config
uint16_t    portcurrent1FACTORY    = 3000;             // max current for a port             - max 3A (parts limit)  // will be used in json config
uint16_t    portcurrent2FACTORY    = 3000;             // max current for a port             - max 3A (parts limit)  // will be used in json config
uint16_t    portcurrent3FACTORY    = 3000;             // max current for a port             - max 3A (parts limit)  // will be used in json config

uint8_t     brightnessFACTORY      = 30;               // set strip brightness

uint8_t     overrideMODEFACTORY    = false;            // are we allowing local control or only mqtt?
uint8_t     overrideWEBFACTORY     = false;            // can the web interface control the hub?

#endif
