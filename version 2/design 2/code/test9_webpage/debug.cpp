
#include <Arduino.h>

#include "debug.h"

char DEBUGtxt[92];

String return_reset_reason(uint8_t reason)
{
  switch ( reason)
  {
    case 1 : return ("POWERON_RESET");break;          /**<1, Vbat power on reset*/
    case 3 : return ("SW_RESET");break;               /**<3, Software reset digital core*/
    case 4 : return ("OWDT_RESET");break;             /**<4, Legacy watch dog reset digital core*/
    case 5 : return ("DEEPSLEEP_RESET");break;        /**<5, Deep Sleep reset digital core*/
    case 6 : return ("SDIO_RESET");break;             /**<6, Reset by SLC module, reset digital core*/
    case 7 : return ("TG0WDT_SYS_RESET");break;       /**<7, Timer Group0 Watch dog reset digital core*/
    case 8 : return ("TG1WDT_SYS_RESET");break;       /**<8, Timer Group1 Watch dog reset digital core*/
    case 9 : return ("RTCWDT_SYS_RESET");break;       /**<9, RTC Watch dog Reset digital core*/
    case 10 : return ("INTRUSION_RESET");break;       /**<10, Instrusion tested to reset CPU*/
    case 11 : return ("TGWDT_CPU_RESET");break;       /**<11, Time Group reset CPU*/
    case 12 : return ("SW_CPU_RESET");break;          /**<12, Software reset CPU*/
    case 13 : return ("RTCWDT_CPU_RESET");break;      /**<13, RTC Watch dog Reset CPU*/
    case 14 : return ("EXT_CPU_RESET");break;         /**<14, for APP CPU, reseted by PRO CPU*/
    case 15 : return ("RTCWDT_BROWN_OUT_RESET");break;/**<15, Reset when the vdd voltage is not stable*/
    case 16 : return ("RTCWDT_RTC_RESET");break;      /**<16, RTC Watch dog reset digital core and rtc module*/
    default : return ("NO_MEAN");
  }
}

void DEBUG_Reset()
{
#if defined(ESP8266)
    sprintf(DEBUGtxt,
            "Reset Reason: %s",
            ESP.getResetReason().c_str());
       DEBUG_Separator();    
       DEBUG_LineOut(DEBUGtxt);
#elif defined(ESP32)
    sprintf(DEBUGtxt,
            "CPU0 reset reason:  %d - %s",
            rtc_get_reset_reason(0),
            return_reset_reason(rtc_get_reset_reason(0)).c_str());
    DEBUG_Separator();    
    DEBUG_LineOut(DEBUGtxt);
    sprintf(DEBUGtxt,
            "CPU1 reset reason:  %d - %s",
            rtc_get_reset_reason(1),
            return_reset_reason(rtc_get_reset_reason(1)).c_str());
    DEBUG_Separator();    
    DEBUG_LineOut(DEBUGtxt);
#endif
}

void DEBUG_Separator()
{
    Serial.printf(">---------------------------------------------------------------------------------------------------<\n");
}

void DEBUG_Title(const char *h, const char *t)
{
    Serial.printf("#===================================================================================================#\n");
    Serial.printf("# Hostname: %-87s #\n", h);
    Serial.printf("# Type:     %-87s #\n", t);;
    Serial.printf("#===================================================================================================#\n");
}

void DEBUG_Init(const char *InitPart)
{
    DEBUG_Separator();
    Serial.printf("| Initialising: %-83s |\n", InitPart);
}

void DEBUG_Wifi(const char *InitPart)
{
    Serial.printf("| SSID : %-90s |\n", InitPart);
}

void DEBUG_IP(const char *InitPart)
{
    Serial.printf("| IP address : %-84s |\n", InitPart);
}

void DEBUG_MAC(const char *InitPart)
{
    Serial.printf("| MAC address : %-83s |\n", InitPart);
}

void DEBUG_rssi(const char *InitPart)
{
    Serial.printf("| RSSI : %-90s |\n", InitPart);
}

void DEBUG_Trouble(const char *Line)
{
    Serial.printf("* %-97s *\n", Line);
}

void DEBUG_Success(const char *Line)
{
    Serial.printf("+ %-97s +\n", Line);
}

void DEBUG_LineOut(const char *Line)
{
    Serial.printf("|   %-95s |\n", Line);
}

void DEBUG_Boot()
{
    Serial.printf("\n\n#===================================================================================================#\n");
    Serial.printf("#                                          Device Booting                                           #\n");
    Serial.printf("#===================================================================================================#\n");
}

void DEBUG_Running()
{
    Serial.printf("#===================================================================================================#\n");
    Serial.printf("#                                          Device Running                                           #\n");
    Serial.printf("#===================================================================================================#\n");
}
