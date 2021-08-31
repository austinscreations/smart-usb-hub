#ifndef debug_h
#define debug_h

#include <Arduino.h>

#if defined(ESP8266)
#elif defined(ESP32)
#include <rom/rtc.h>
#endif


// Function declarations

//void setup_DEBUG();                             // main startup
void DEBUG_Boot();                              // for when device first boots up

void DEBUG_Title(const char *h, const char *t); // shows device name
void DEBUG_Reset();                             // debugs the reset reason
String return_reset_reason(uint8_t reason);     // cases for reset reason


void DEBUG_Ready();                             // for when setup is done (and wifi connected or ap started)
void DEBUG_Separator();                         // seprates items in debug output
void DEBUG_Init(const char *InitPart);          // for initializing soemthing
void DEBUG_Wifi(const char *InitPart);          // for showing what SSID your connecting to
void DEBUG_IP(const char *InitPart);            // for showing what IP address
void DEBUG_MAC(const char *InitPart);           // for showing MAC address
void DEBUG_rssi(const char *InitPart);          // for showing RSSI strength
void DEBUG_LineOut(const char *Line);           // prints out information
void DEBUG_Running();                           // device has compeleted the main setup

void DEBUG_Success(const char *Line);
void DEBUG_Trouble(const char *Line);


#endif
