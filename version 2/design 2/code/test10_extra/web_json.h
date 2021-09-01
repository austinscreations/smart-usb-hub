#ifndef web_json_h
#define web_json_h

void webSENDjson(){
//      Serial.println("[WSc] SENT: Broadcast message!!");   // debug
      const size_t capacity = 1024;
      DynamicJsonDocument doc(capacity);

      if (port_INA[0] != true){                           // INA on port 1 has been found
           char webvolt1[8];
           sprintf(webvolt1, "%.2f", busvoltage);         // find the current system voltage
           strcat(webvolt1," V");                         // and V to the end

           char webmA1[8];
           itoa(EMA_C[0], webmA1, 10);                    // find port current
           strcat(webmA1," mA");                          // add mA to it

        doc["volt0"] = webvolt1;                          // set voltage here (on page)
        if (darkState == false)                           // light mode on the webpage
        {
          doc["port0"] = "black";                         // text is black
          doc["mastyle0"] = "black";                      // text is black
          if (voltlockout == 0)                           // not in voltage lockout
          {
            doc["voltstyle0"] = "black";                  // text is black
          }
          else                                            // in voltage lcokout
          {
            doc["voltstyle0"] = "red";                    // issue with voltage show it red
          }
          if (port_state[0] != 10 && port_state[0] != 11) // not in current lockout
          {
            if (port_state[0] == 0)                       // port is off
            {
              if (overrideMODE == false)                  // not in override mode
              {
                doc["border0"] = "#000000";                // LED is considered off
              }
              else                                        // in override mode (true) - LED can be anything we want
              {
                if (whinew[0] == 0)                       // white LED is off do basic RGB to HEX conversion
                {
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", rednew[0],grnnew[0],blunew[0]);
                  if (ledmode[0] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border0"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border0"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border0"] = hex;                  // set custom HEX color
                  }
                }
                else if (whinew[0] == 255)                // full white called - it will overpower the colors
                {
                  if (ledmode[0] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border0"] = "#ffffff";          // set border to white
                    }
                    else                                  // LED is off
                    {
                      doc["border0"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border0"] = "#ffffff";          // set border to white
                  }
                }
                else                                      // the RGBW color is mixed time for Math
                {
                  ESP_Color::Color color(rednew[0],grnnew[0],blunew[0]);  // normal RGB value
                  auto hsv = color.ToHsv();                               // change it to HSV
                  white_reverse = map(whinew[0],0,255,255,0);             // flip white value
                  new_sat = (hsv.S * (white_reverse / 255.0F));           // calculate the new saturation level
                  auto RGB = color.FromHsv(hsv.H, new_sat, hsv.V);        // create our new RGB value
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", RGB.R, RGB.G, RGB.B);       // create our HEX value
                  if (ledmode[0] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border0"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border0"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border0"] = "#ffffff";            // set border to white
                  }
                }
              }
              doc["ma0"] = "0 mA";                        // no power is flowing
              doc["p0"] = "DISABLE";                      // power is disabled
              doc["d0"] = "DISABLE";                      // data is disabled
            }
            if (port_state[0] == 1)                       // power is on
            {
              if (overrideMODE == false)                  // not in override mode
              {
                doc["border0"] = "#ffff00";                // LED is considered yellow
              }
              else                                        // in override mode (true) - LED can be anything we want
              {
                if (whinew[0] == 0)                       // white LED is off do basic RGB to HEX conversion
                {
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", rednew[0],grnnew[0],blunew[0]);
                  if (ledmode[0] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border0"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border0"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border0"] = hex;                  // set custom HEX color
                  }
                }
                else if (whinew[0] == 255)                // full white called - it will overpower the colors
                {
                  if (ledmode[0] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border0"] = "#ffffff";          // set border to white
                    }
                    else                                  // LED is off
                    {
                      doc["border0"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border0"] = "#ffffff";            // set border to white
                  }
                }
                else                                      // the RGBW color is mixed time for Math
                {
                  ESP_Color::Color color(rednew[0],grnnew[0],blunew[0]);  // normal RGB value
                  auto hsv = color.ToHsv();                               // change it to HSV
                  white_reverse = map(whinew[0],0,255,255,0);             // flip white value
                  new_sat = (hsv.S * (white_reverse / 255.0F));           // calculate the new saturation level
                  auto RGB = color.FromHsv(hsv.H, new_sat, hsv.V);        // create our new RGB value
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", RGB.R, RGB.G, RGB.B);       // create our HEX value
                  if (ledmode[0] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border0"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border0"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border0"] = hex;                  // set custom HEX color
                  }
                }
              }
              doc["ma0"] = webmA1;                        // show mA
              doc["p0"] = "ENABLE";                       // power is enabled
              doc["d0"] = "DISABLE";                      // data is disabled
            }
            if (port_state[0] == 2)                       // data is on
            {
              if (overrideMODE == false)                  // not in override mode
              {
                doc["border0"] = "#00ff00";                // LED is considered green
              }
              else                                        // in override mode (true) - LED can be anything we want
              {
                if (whinew[0] == 0)                       // white LED is off do basic RGB to HEX conversion
                {
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", rednew[0],grnnew[0],blunew[0]);
                  if (ledmode[0] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border0"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border0"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border0"] = hex;                  // set custom HEX color
                  }
                }
                else if (whinew[0] == 255)                // full white called - it will overpower the colors
                {
                  if (ledmode[0] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border0"] = "#ffffff";          // set border to white
                    }
                    else                                  // LED is off
                    {
                      doc["border0"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border0"] = "#ffffff";            // set border to white
                  }
                }
                else                                      // the RGBW color is mixed time for Math
                {
                  ESP_Color::Color color(rednew[0],grnnew[0],blunew[0]);  // normal RGB value
                  auto hsv = color.ToHsv();                               // change it to HSV
                  white_reverse = map(whinew[0],0,255,255,0);             // flip white value
                  new_sat = (hsv.S * (white_reverse / 255.0F));           // calculate the new saturation level
                  auto RGB = color.FromHsv(hsv.H, new_sat, hsv.V);        // create our new RGB value
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", RGB.R, RGB.G, RGB.B);       // create our HEX value
                  if (ledmode[0] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border0"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border0"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border0"] = hex;                  // set custom HEX color
                  }
                }
              }
              doc["ma0"] = webmA1;                        // show mA
              doc["p0"] = "ENABLE";                       // power is enabled
              doc["d0"] = "ENABLE";                       // data is enabled
            }
          }
          else                                            // in current lockout
          {
            doc["mastyle0"] = "red";                      // current state - show red in lockout
            doc["border0"] = "#8a8a8a";
            doc["ma0"] = "----";   
            doc["p0"] = "DISABLE";
            doc["d0"] = "DISABLE"; 
          }
        }
        else                                              // dark mode on the webpage
        {
          doc["port0"] = "white";
          doc["mastyle0"] = "white";
          if (voltlockout == 0)                           // not in voltage lockout
          {
            doc["voltstyle0"] = "white";
          }
          else                                            // in voltage lcokout
          {
            doc["voltstyle0"] = "red";
          }
          if (port_state[0] != 10 && port_state[0] != 11) // not in current lockout
          {
            if (port_state[0] == 0)                       // port is off
            {
              if (overrideMODE == false)                  // not in override mode
              {
                doc["border0"] = "#000000";                // LED is considered off
              }
              else                                        // in override mode (true) - LED can be anything we want
              {
                if (whinew[0] == 0)                       // white LED is off do basic RGB to HEX conversion
                {
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", rednew[0],grnnew[0],blunew[0]);
                  if (ledmode[0] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border0"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border0"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border0"] = hex;                  // set custom HEX color
                  }
                }
                else if (whinew[0] == 255)                // full white called - it will overpower the colors
                {
                  if (ledmode[0] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border0"] = "#ffffff";            // set border to white
                    }
                    else                                  // LED is off
                    {
                      doc["border0"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border0"] = "#ffffff";            // set border to white
                  }
                }
                else                                      // the RGBW color is mixed time for Math
                {
                  ESP_Color::Color color(rednew[0],grnnew[0],blunew[0]);  // normal RGB value
                  auto hsv = color.ToHsv();                               // change it to HSV
                  white_reverse = map(whinew[0],0,255,255,0);             // flip white value
                  new_sat = (hsv.S * (white_reverse / 255.0F));           // calculate the new saturation level
                  auto RGB = color.FromHsv(hsv.H, new_sat, hsv.V);        // create our new RGB value
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", RGB.R, RGB.G, RGB.B);       // create our HEX value
                  if (ledmode[0] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border0"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border0"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border0"] = hex;                  // set custom HEX color
                  }
                }
              }
              doc["ma0"] = "0 mA";                        // no power is flowing
              doc["p0"] = "DISABLE";                      // power is disabled
              doc["d0"] = "DISABLE";                      // data is disabled
            }

            if (port_state[0] == 1)                       // power is on
            {
              if (overrideMODE == false)                  // not in override mode
              {
                doc["border0"] = "#ffff00";                // LED is considered yellow
              }
              else                                        // in override mode (true) - LED can be anything we want
              {
                if (whinew[0] == 0)                       // white LED is off do basic RGB to HEX conversion
                {
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", rednew[0],grnnew[0],blunew[0]);
                  if (ledmode[0] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border0"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border0"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border0"] = hex;                  // set custom HEX color
                  }
                }
                else if (whinew[0] == 255)                // full white called - it will overpower the colors
                {
                  if (ledmode[0] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border0"] = "#ffffff";            // set border to white
                    }
                    else                                  // LED is off
                    {
                      doc["border0"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border0"] = "#ffffff";            // set border to white
                  }
                }
                else                                      // the RGBW color is mixed time for Math
                {
                  ESP_Color::Color color(rednew[0],grnnew[0],blunew[0]);  // normal RGB value
                  auto hsv = color.ToHsv();                               // change it to HSV
                  white_reverse = map(whinew[0],0,255,255,0);             // flip white value
                  new_sat = (hsv.S * (white_reverse / 255.0F));           // calculate the new saturation level
                  auto RGB = color.FromHsv(hsv.H, new_sat, hsv.V);        // create our new RGB value
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", RGB.R, RGB.G, RGB.B);       // create our HEX value
                  if (ledmode[0] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border0"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border0"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border0"] = hex;                  // set custom HEX color
                  }
                }
              }
              doc["ma0"] = webmA1;                        // ******** show mA
              doc["p0"] = "ENABLE";                       // power is enabled
              doc["d0"] = "DISABLE";                      // data is disabled
            }
            if (port_state[0] == 2)                       // data is on
            {
              if (overrideMODE == false)                  // not in override mode
              {
                doc["border0"] = "#00ff00";                // LED is considered green
              }
              else                                        // in override mode (true) - LED can be anything we want
              {
                if (whinew[0] == 0)                       // white LED is off do basic RGB to HEX conversion
                {
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", rednew[0],grnnew[0],blunew[0]);
                  if (ledmode[0] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border0"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border0"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border0"] = hex;                  // set custom HEX color
                  }
                }
                else if (whinew[0] == 255)                // full white called - it will overpower the colors
                {
                  if (ledmode[0] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border0"] = "#ffffff";            // set border to white
                    }
                    else                                  // LED is off
                    {
                      doc["border0"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border0"] = "#ffffff";            // set border to white
                  }
                }
                else                                      // the RGBW color is mixed time for Math
                {
                  ESP_Color::Color color(rednew[0],grnnew[0],blunew[0]);  // normal RGB value
                  auto hsv = color.ToHsv();                               // change it to HSV
                  white_reverse = map(whinew[0],0,255,255,0);             // flip white value
                  new_sat = (hsv.S * (white_reverse / 255.0F));           // calculate the new saturation level
                  auto RGB = color.FromHsv(hsv.H, new_sat, hsv.V);        // create our new RGB value
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", RGB.R, RGB.G, RGB.B);       // create our HEX value
                  if (ledmode[0] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border0"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border0"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border0"] = hex;                  // set custom HEX color
                  }
                }
              }
              doc["ma0"] = webmA1;                        // ******** show mA
              doc["p0"] = "ENABLE";                       // power is enabled
              doc["d0"] = "ENABLE";                       // data is enabled
            }
          }
          else                                            // in current lockout
          {
            doc["mastyle0"] = "red";                      // current state - show red in lockout
            doc["border0"] = "#8a8a8a";
            doc["ma0"] = "----";   
            doc["p0"] = "DISABLE";
            doc["d0"] = "DISABLE";
            
          }
        }
      }
      else                                                // not found INA port 1
      {
        doc["border0"] = "#422a2a";
        doc["port0"] = "red";
        doc["volt0"] = "----";                            // no volts to calculate
        doc["voltstyle0"] = "red";
        doc["mastyle0"] = "red";                          // current state - show red in lockout
        doc["ma0"] = "----";                              // no power to calculate
        doc["p0"] = "DISABLE";                            // power is disabled
        doc["d0"] = "DISABLE";                            // data is disabled
      }

//--------------------------------------------------------
      if (port_INA[1] != true){                           // INA on port 2 has been found
           char webvolt1[8];
           sprintf(webvolt1, "%.2f", busvoltage);         // find the current system voltage
           strcat(webvolt1," V");                         // and V to the end

           char webmA1[8];
           itoa(EMA_C[1], webmA1, 10);                    // find port current
           strcat(webmA1," mA");                          // add mA to it

        doc["volt1"] = webvolt1;                          // set voltage here (on page)
        if (darkState == false)                           // light mode on the webpage
        {
          doc["port1"] = "black";                         // text is black
          doc["mastyle1"] = "black";                      // text is black
          if (voltlockout == 0)                           // not in voltage lockout
          {
            doc["voltstyle1"] = "black";                  // text is black
          }
          else                                            // in voltage lcokout
          {
            doc["voltstyle1"] = "red";                    // issue with voltage show it red
          }
          if (port_state[1] != 10 && port_state[1] != 11) // not in current lockout
          {
            if (port_state[1] == 0)                       // port is off
            {
              if (overrideMODE == false)                  // not in override mode
              {
                doc["border1"] = "#000000";                // LED is considered off
              }
              else                                        // in override mode (true) - LED can be anything we want
              {
                if (whinew[1] == 0)                       // white LED is off do basic RGB to HEX conversion
                {
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", rednew[1],grnnew[1],blunew[1]);
                  if (ledmode[1] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border1"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border1"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border1"] = hex;                  // set custom HEX color
                  }
                }
                else if (whinew[1] == 255)                // full white called - it will overpower the colors
                {
                  if (ledmode[1] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border1"] = "#ffffff";          // set border to white
                    }
                    else                                  // LED is off
                    {
                      doc["border1"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border1"] = "#ffffff";          // set border to white
                  }
                }
                else                                      // the RGBW color is mixed time for Math
                {
                  ESP_Color::Color color(rednew[1],grnnew[1],blunew[1]);  // normal RGB value
                  auto hsv = color.ToHsv();                               // change it to HSV
                  white_reverse = map(whinew[1],0,255,255,0);             // flip white value
                  new_sat = (hsv.S * (white_reverse / 255.0F));           // calculate the new saturation level
                  auto RGB = color.FromHsv(hsv.H, new_sat, hsv.V);        // create our new RGB value
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", RGB.R, RGB.G, RGB.B);       // create our HEX value
                  if (ledmode[1] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border1"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border1"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border1"] = "#ffffff";            // set border to white
                  }
                }
              }
              doc["ma1"] = "0 mA";                        // no power is flowing
              doc["p1"] = "DISABLE";                      // power is disabled
              doc["d1"] = "DISABLE";                      // data is disabled
            }
            if (port_state[1] == 1)                       // power is on
            {
              if (overrideMODE == false)                  // not in override mode
              {
                doc["border1"] = "#ffff00";                // LED is considered yellow
              }
              else                                        // in override mode (true) - LED can be anything we want
              {
                if (whinew[1] == 0)                       // white LED is off do basic RGB to HEX conversion
                {
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", rednew[1],grnnew[1],blunew[1]);
                  if (ledmode[1] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border1"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border1"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border1"] = hex;                  // set custom HEX color
                  }
                }
                else if (whinew[1] == 255)                // full white called - it will overpower the colors
                {
                  if (ledmode[1] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border1"] = "#ffffff";          // set border to white
                    }
                    else                                  // LED is off
                    {
                      doc["border1"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border1"] = "#ffffff";            // set border to white
                  }
                }
                else                                      // the RGBW color is mixed time for Math
                {
                  ESP_Color::Color color(rednew[1],grnnew[1],blunew[1]);  // normal RGB value
                  auto hsv = color.ToHsv();                               // change it to HSV
                  white_reverse = map(whinew[1],0,255,255,0);             // flip white value
                  new_sat = (hsv.S * (white_reverse / 255.0F));           // calculate the new saturation level
                  auto RGB = color.FromHsv(hsv.H, new_sat, hsv.V);        // create our new RGB value
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", RGB.R, RGB.G, RGB.B);       // create our HEX value
                  if (ledmode[1] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border1"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border1"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border1"] = hex;                  // set custom HEX color
                  }
                }
              }
              doc["ma1"] = webmA1;                        // show mA
              doc["p1"] = "ENABLE";                       // power is enabled
              doc["d1"] = "DISABLE";                      // data is disabled
            }
            if (port_state[1] == 2)                       // data is on
            {
              if (overrideMODE == false)                  // not in override mode
              {
                doc["border1"] = "#00ff00";                // LED is considered green
              }
              else                                        // in override mode (true) - LED can be anything we want
              {
                if (whinew[1] == 0)                       // white LED is off do basic RGB to HEX conversion
                {
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", rednew[1],grnnew[1],blunew[1]);
                  if (ledmode[1] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border1"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border1"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border1"] = hex;                  // set custom HEX color
                  }
                }
                else if (whinew[1] == 255)                // full white called - it will overpower the colors
                {
                  if (ledmode[1] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border1"] = "#ffffff";          // set border to white
                    }
                    else                                  // LED is off
                    {
                      doc["border1"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border1"] = "#ffffff";            // set border to white
                  }
                }
                else                                      // the RGBW color is mixed time for Math
                {
                  ESP_Color::Color color(rednew[1],grnnew[1],blunew[1]);  // normal RGB value
                  auto hsv = color.ToHsv();                               // change it to HSV
                  white_reverse = map(whinew[1],0,255,255,0);             // flip white value
                  new_sat = (hsv.S * (white_reverse / 255.0F));           // calculate the new saturation level
                  auto RGB = color.FromHsv(hsv.H, new_sat, hsv.V);        // create our new RGB value
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", RGB.R, RGB.G, RGB.B);       // create our HEX value
                  if (ledmode[1] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border1"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border1"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border1"] = hex;                  // set custom HEX color
                  }
                }
              }
              doc["ma1"] = webmA1;                        // show mA
              doc["p1"] = "ENABLE";                       // power is enabled
              doc["d1"] = "ENABLE";                       // data is enabled
            }
          }
          else                                            // in current lockout
          {
            doc["mastyle1"] = "red";                      // current state - show red in lockout
            doc["border1"] = "#8a8a8a";
            doc["ma1"] = "----";   
            doc["p1"] = "DISABLE";
            doc["d1"] = "DISABLE"; 
          }
        }
        else                                              // dark mode on the webpage
        {
          doc["port1"] = "white";
          doc["mastyle1"] = "white";
          if (voltlockout == 0)                           // not in voltage lockout
          {
            doc["voltstyle1"] = "white";
          }
          else                                            // in voltage lcokout
          {
            doc["voltstyle1"] = "red";
          }
          if (port_state[1] != 10 && port_state[1] != 11) // not in current lockout
          {
            if (port_state[1] == 0)                       // port is off
            {
              if (overrideMODE == false)                  // not in override mode
              {
                doc["border1"] = "#000000";                // LED is considered off
              }
              else                                        // in override mode (true) - LED can be anything we want
              {
                if (whinew[1] == 0)                       // white LED is off do basic RGB to HEX conversion
                {
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", rednew[1],grnnew[1],blunew[1]);
                  if (ledmode[1] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border1"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border1"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border1"] = hex;                  // set custom HEX color
                  }
                }
                else if (whinew[1] == 255)                // full white called - it will overpower the colors
                {
                  if (ledmode[1] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border1"] = "#ffffff";            // set border to white
                    }
                    else                                  // LED is off
                    {
                      doc["border1"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border1"] = "#ffffff";            // set border to white
                  }
                }
                else                                      // the RGBW color is mixed time for Math
                {
                  ESP_Color::Color color(rednew[1],grnnew[1],blunew[1]);  // normal RGB value
                  auto hsv = color.ToHsv();                               // change it to HSV
                  white_reverse = map(whinew[1],0,255,255,0);             // flip white value
                  new_sat = (hsv.S * (white_reverse / 255.0F));           // calculate the new saturation level
                  auto RGB = color.FromHsv(hsv.H, new_sat, hsv.V);        // create our new RGB value
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", RGB.R, RGB.G, RGB.B);       // create our HEX value
                  if (ledmode[1] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border1"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border1"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border1"] = hex;                  // set custom HEX color
                  }
                }
              }
              doc["ma1"] = "0 mA";                        // no power is flowing
              doc["p1"] = "DISABLE";                      // power is disabled
              doc["d1"] = "DISABLE";                      // data is disabled
            }
            if (port_state[1] == 1)                       // power is on
            {
              if (overrideMODE == false)                  // not in override mode
              {
                doc["border1"] = "#ffff00";                // LED is considered yellow
              }
              else                                        // in override mode (true) - LED can be anything we want
              {
                if (whinew[1] == 0)                       // white LED is off do basic RGB to HEX conversion
                {
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", rednew[1],grnnew[1],blunew[1]);
                  if (ledmode[1] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border1"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border1"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border1"] = hex;                  // set custom HEX color
                  }
                }
                else if (whinew[1] == 255)                // full white called - it will overpower the colors
                {
                  if (ledmode[1] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border1"] = "#ffffff";            // set border to white
                    }
                    else                                  // LED is off
                    {
                      doc["border1"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border1"] = "#ffffff";            // set border to white
                  }
                }
                else                                      // the RGBW color is mixed time for Math
                {
                  ESP_Color::Color color(rednew[1],grnnew[1],blunew[1]);  // normal RGB value
                  auto hsv = color.ToHsv();                               // change it to HSV
                  white_reverse = map(whinew[1],0,255,255,0);             // flip white value
                  new_sat = (hsv.S * (white_reverse / 255.0F));           // calculate the new saturation level
                  auto RGB = color.FromHsv(hsv.H, new_sat, hsv.V);        // create our new RGB value
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", RGB.R, RGB.G, RGB.B);       // create our HEX value
                  if (ledmode[1] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border1"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border1"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border1"] = hex;                  // set custom HEX color
                  }
                }
              }
              doc["ma1"] = webmA1;                        // ******** show mA
              doc["p1"] = "ENABLE";                       // power is enabled
              doc["d1"] = "DISABLE";                      // data is disabled
            }
            if (port_state[1] == 2)                       // data is on
            {
              if (overrideMODE == false)                  // not in override mode
              {
                doc["border1"] = "#00ff00";                // LED is considered green
              }
              else                                        // in override mode (true) - LED can be anything we want
              {
                if (whinew[1] == 0)                       // white LED is off do basic RGB to HEX conversion
                {
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", rednew[1],grnnew[1],blunew[1]);
                  if (ledmode[1] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border1"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border1"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border1"] = hex;                  // set custom HEX color
                  }
                }
                else if (whinew[1] == 255)                // full white called - it will overpower the colors
                {
                  if (ledmode[1] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border1"] = "#ffffff";            // set border to white
                    }
                    else                                  // LED is off
                    {
                      doc["border1"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border1"] = "#ffffff";            // set border to white
                  }
                }
                else                                      // the RGBW color is mixed time for Math
                {
                  ESP_Color::Color color(rednew[1],grnnew[1],blunew[1]);  // normal RGB value
                  auto hsv = color.ToHsv();                               // change it to HSV
                  white_reverse = map(whinew[1],0,255,255,0);             // flip white value
                  new_sat = (hsv.S * (white_reverse / 255.0F));           // calculate the new saturation level
                  auto RGB = color.FromHsv(hsv.H, new_sat, hsv.V);        // create our new RGB value
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", RGB.R, RGB.G, RGB.B);       // create our HEX value
                  if (ledmode[1] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border1"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border1"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border1"] = hex;                  // set custom HEX color
                  }
                }
              }
              doc["ma1"] = webmA1;                        // ******** show mA
              doc["p1"] = "ENABLE";                       // power is enabled
              doc["d1"] = "ENABLE";                       // data is enabled
            }
          }
          else                                            // in current lockout
          {
            doc["mastyle1"] = "red";                      // current state - show red in lockout
            doc["border1"] = "#8a8a8a";
            doc["ma1"] = "----";   
            doc["p1"] = "DISABLE";
            doc["d1"] = "DISABLE";
            
          }
        }
      }
      else                                                // not found INA port 1
      {
        doc["border1"] = "#422a2a";
        doc["port1"] = "red";
        doc["volt1"] = "----";                            // no volts to calculate
        doc["voltstyle1"] = "red";
        doc["mastyle1"] = "red";                          // current state - show red in lockout
        doc["ma1"] = "----";                              // no power to calculate
        doc["p1"] = "DISABLE";                            // power is disabled
        doc["d1"] = "DISABLE";                            // data is disabled
      }

      //--------------------------------------------------------
      if (port_INA[2] != true){                           // INA on port 2 has been found
           char webvolt1[8];
           sprintf(webvolt1, "%.2f", busvoltage);         // find the current system voltage
           strcat(webvolt1," V");                         // and V to the end

           char webmA1[8];
           itoa(EMA_C[2], webmA1, 10);                    // find port current
           strcat(webmA1," mA");                          // add mA to it

        doc["volt2"] = webvolt1;                          // set voltage here (on page)
        if (darkState == false)                           // light mode on the webpage
        {
          doc["port2"] = "black";                         // text is black
          doc["mastyle2"] = "black";                      // text is black
          if (voltlockout == 0)                           // not in voltage lockout
          {
            doc["voltstyle2"] = "black";                  // text is black
          }
          else                                            // in voltage lcokout
          {
            doc["voltstyle2"] = "red";                    // issue with voltage show it red
          }
          if (port_state[2] != 10 && port_state[2] != 11) // not in current lockout
          {
            if (port_state[2] == 0)                       // port is off
            {
              if (overrideMODE == false)                  // not in override mode
              {
                doc["border2"] = "#000000";                // LED is considered off
              }
              else                                        // in override mode (true) - LED can be anything we want
              {
                if (whinew[2] == 0)                       // white LED is off do basic RGB to HEX conversion
                {
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", rednew[2],grnnew[2],blunew[2]);
                  if (ledmode[2] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border2"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border2"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border2"] = hex;                  // set custom HEX color
                  }
                }
                else if (whinew[2] == 255)                // full white called - it will overpower the colors
                {
                  if (ledmode[2] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border2"] = "#ffffff";          // set border to white
                    }
                    else                                  // LED is off
                    {
                      doc["border2"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border2"] = "#ffffff";          // set border to white
                  }
                }
                else                                      // the RGBW color is mixed time for Math
                {
                  ESP_Color::Color color(rednew[2],grnnew[2],blunew[2]);  // normal RGB value
                  auto hsv = color.ToHsv();                               // change it to HSV
                  white_reverse = map(whinew[2],0,255,255,0);             // flip white value
                  new_sat = (hsv.S * (white_reverse / 255.0F));           // calculate the new saturation level
                  auto RGB = color.FromHsv(hsv.H, new_sat, hsv.V);        // create our new RGB value
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", RGB.R, RGB.G, RGB.B);       // create our HEX value
                  if (ledmode[2] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border2"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border2"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border2"] = "#ffffff";            // set border to white
                  }
                }
              }
              doc["ma2"] = "0 mA";                        // no power is flowing
              doc["p2"] = "DISABLE";                      // power is disabled
              doc["d2"] = "DISABLE";                      // data is disabled
            }
            if (port_state[2] == 1)                       // power is on
            {
              if (overrideMODE == false)                  // not in override mode
              {
                doc["border2"] = "#ffff00";                // LED is considered yellow
              }
              else                                        // in override mode (true) - LED can be anything we want
              {
                if (whinew[2] == 0)                       // white LED is off do basic RGB to HEX conversion
                {
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", rednew[2],grnnew[2],blunew[2]);
                  if (ledmode[2] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border2"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border2"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border2"] = hex;                  // set custom HEX color
                  }
                }
                else if (whinew[2] == 255)                // full white called - it will overpower the colors
                {
                  if (ledmode[2] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border2"] = "#ffffff";          // set border to white
                    }
                    else                                  // LED is off
                    {
                      doc["border2"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border2"] = "#ffffff";            // set border to white
                  }
                }
                else                                      // the RGBW color is mixed time for Math
                {
                  ESP_Color::Color color(rednew[2],grnnew[2],blunew[2]);  // normal RGB value
                  auto hsv = color.ToHsv();                               // change it to HSV
                  white_reverse = map(whinew[2],0,255,255,0);             // flip white value
                  new_sat = (hsv.S * (white_reverse / 255.0F));           // calculate the new saturation level
                  auto RGB = color.FromHsv(hsv.H, new_sat, hsv.V);        // create our new RGB value
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", RGB.R, RGB.G, RGB.B);       // create our HEX value
                  if (ledmode[2] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border2"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border2"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border2"] = hex;                  // set custom HEX color
                  }
                }
              }
              doc["ma2"] = webmA1;                        // show mA
              doc["p2"] = "ENABLE";                       // power is enabled
              doc["d2"] = "DISABLE";                      // data is disabled
            }
            if (port_state[2] == 2)                       // data is on
            {
              if (overrideMODE == false)                  // not in override mode
              {
                doc["border2"] = "#00ff00";                // LED is considered green
              }
              else                                        // in override mode (true) - LED can be anything we want
              {
                if (whinew[2] == 0)                       // white LED is off do basic RGB to HEX conversion
                {
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", rednew[2],grnnew[2],blunew[2]);
                  if (ledmode[2] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border2"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border2"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border2"] = hex;                  // set custom HEX color
                  }
                }
                else if (whinew[2] == 255)                // full white called - it will overpower the colors
                {
                  if (ledmode[2] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border2"] = "#ffffff";          // set border to white
                    }
                    else                                  // LED is off
                    {
                      doc["border2"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border2"] = "#ffffff";            // set border to white
                  }
                }
                else                                      // the RGBW color is mixed time for Math
                {
                  ESP_Color::Color color(rednew[2],grnnew[2],blunew[2]);  // normal RGB value
                  auto hsv = color.ToHsv();                               // change it to HSV
                  white_reverse = map(whinew[2],0,255,255,0);             // flip white value
                  new_sat = (hsv.S * (white_reverse / 255.0F));           // calculate the new saturation level
                  auto RGB = color.FromHsv(hsv.H, new_sat, hsv.V);        // create our new RGB value
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", RGB.R, RGB.G, RGB.B);       // create our HEX value
                  if (ledmode[2] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border2"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border2"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border2"] = hex;                  // set custom HEX color
                  }
                }
              }
              doc["ma2"] = webmA1;                        // show mA
              doc["p2"] = "ENABLE";                       // power is enabled
              doc["d2"] = "ENABLE";                       // data is enabled
            }
          }
          else                                            // in current lockout
          {
            doc["mastyle2"] = "red";                      // current state - show red in lockout
            doc["border2"] = "#8a8a8a";
            doc["ma2"] = "----";   
            doc["p2"] = "DISABLE";
            doc["d2"] = "DISABLE"; 
          }
        }
        else                                              // dark mode on the webpage
        {
          doc["port2"] = "white";
          doc["mastyle2"] = "white";
          if (voltlockout == 0)                           // not in voltage lockout
          {
            doc["voltstyle2"] = "white";
          }
          else                                            // in voltage lcokout
          {
            doc["voltstyle2"] = "red";
          }
          if (port_state[2] != 10 && port_state[2] != 11) // not in current lockout
          {
            if (port_state[2] == 0)                       // port is off
            {
              if (overrideMODE == false)                  // not in override mode
              {
                doc["border2"] = "#000000";                // LED is considered off
              }
              else                                        // in override mode (true) - LED can be anything we want
              {
                if (whinew[2] == 0)                       // white LED is off do basic RGB to HEX conversion
                {
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", rednew[2],grnnew[2],blunew[2]);
                  if (ledmode[2] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border2"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border2"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border2"] = hex;                  // set custom HEX color
                  }
                }
                else if (whinew[2] == 255)                // full white called - it will overpower the colors
                {
                  if (ledmode[2] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border2"] = "#ffffff";            // set border to white
                    }
                    else                                  // LED is off
                    {
                      doc["border2"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border2"] = "#ffffff";            // set border to white
                  }
                }
                else                                      // the RGBW color is mixed time for Math
                {
                  ESP_Color::Color color(rednew[2],grnnew[2],blunew[2]);  // normal RGB value
                  auto hsv = color.ToHsv();                               // change it to HSV
                  white_reverse = map(whinew[2],0,255,255,0);             // flip white value
                  new_sat = (hsv.S * (white_reverse / 255.0F));           // calculate the new saturation level
                  auto RGB = color.FromHsv(hsv.H, new_sat, hsv.V);        // create our new RGB value
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", RGB.R, RGB.G, RGB.B);       // create our HEX value
                  if (ledmode[2] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border2"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border2"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border2"] = hex;                  // set custom HEX color
                  }
                }
              }
              doc["ma2"] = "0 mA";                        // no power is flowing
              doc["p2"] = "DISABLE";                      // power is disabled
              doc["d2"] = "DISABLE";                      // data is disabled
            }
            if (port_state[2] == 1)                       // power is on
            {
              if (overrideMODE == false)                  // not in override mode
              {
                doc["border2"] = "#ffff00";                // LED is considered yellow
              }
              else                                        // in override mode (true) - LED can be anything we want
              {
                if (whinew[2] == 0)                       // white LED is off do basic RGB to HEX conversion
                {
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", rednew[2],grnnew[2],blunew[2]);
                  if (ledmode[2] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border2"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border2"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border2"] = hex;                  // set custom HEX color
                  }
                }
                else if (whinew[2] == 255)                // full white called - it will overpower the colors
                {
                  if (ledmode[2] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border2"] = "#ffffff";            // set border to white
                    }
                    else                                  // LED is off
                    {
                      doc["border2"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border2"] = "#ffffff";            // set border to white
                  }
                }
                else                                      // the RGBW color is mixed time for Math
                {
                  ESP_Color::Color color(rednew[2],grnnew[2],blunew[2]);  // normal RGB value
                  auto hsv = color.ToHsv();                               // change it to HSV
                  white_reverse = map(whinew[2],0,255,255,0);             // flip white value
                  new_sat = (hsv.S * (white_reverse / 255.0F));           // calculate the new saturation level
                  auto RGB = color.FromHsv(hsv.H, new_sat, hsv.V);        // create our new RGB value
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", RGB.R, RGB.G, RGB.B);       // create our HEX value
                  if (ledmode[2] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border2"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border2"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border2"] = hex;                  // set custom HEX color
                  }
                }
              }
              doc["ma2"] = webmA1;                        // ******** show mA
              doc["p2"] = "ENABLE";                       // power is enabled
              doc["d2"] = "DISABLE";                      // data is disabled
            }
            if (port_state[2] == 2)                       // data is on
            {
              if (overrideMODE == false)                  // not in override mode
              {
                doc["border2"] = "#00ff00";                // LED is considered green
              }
              else                                        // in override mode (true) - LED can be anything we want
              {
                if (whinew[2] == 0)                       // white LED is off do basic RGB to HEX conversion
                {
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", rednew[2],grnnew[2],blunew[2]);
                  if (ledmode[2] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border2"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border2"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border2"] = hex;                  // set custom HEX color
                  }
                }
                else if (whinew[2] == 255)                // full white called - it will overpower the colors
                {
                  if (ledmode[2] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border2"] = "#ffffff";            // set border to white
                    }
                    else                                  // LED is off
                    {
                      doc["border2"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border2"] = "#ffffff";            // set border to white
                  }
                }
                else                                      // the RGBW color is mixed time for Math
                {
                  ESP_Color::Color color(rednew[2],grnnew[2],blunew[2]);  // normal RGB value
                  auto hsv = color.ToHsv();                               // change it to HSV
                  white_reverse = map(whinew[2],0,255,255,0);             // flip white value
                  new_sat = (hsv.S * (white_reverse / 255.0F));           // calculate the new saturation level
                  auto RGB = color.FromHsv(hsv.H, new_sat, hsv.V);        // create our new RGB value
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", RGB.R, RGB.G, RGB.B);       // create our HEX value
                  if (ledmode[2] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border2"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border2"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border2"] = hex;                  // set custom HEX color
                  }
                }
              }
              doc["ma2"] = webmA1;                        // ******** show mA
              doc["p2"] = "ENABLE";                       // power is enabled
              doc["d2"] = "ENABLE";                       // data is enabled
            }
          }
          else                                            // in current lockout
          {
            doc["mastyle2"] = "red";                      // current state - show red in lockout
            doc["border2"] = "#8a8a8a";
            doc["ma2"] = "----";   
            doc["p2"] = "DISABLE";
            doc["d2"] = "DISABLE";
            
          }
        }
      }
      else                                                // not found INA port 1
      {
        doc["border2"] = "#422a2a";
        doc["port2"] = "red";
        doc["volt2"] = "----";                            // no volts to calculate
        doc["voltstyle2"] = "red";
        doc["mastyle2"] = "red";                          // current state - show red in lockout
        doc["ma2"] = "----";                              // no power to calculate
        doc["p2"] = "DISABLE";                            // power is disabled
        doc["d2"] = "DISABLE";                            // data is disabled
      }

      //--------------------------------------------------------
      if (port_INA[3] != true){                           // INA on port 2 has been found
           char webvolt1[8];
           sprintf(webvolt1, "%.2f", busvoltage);         // find the current system voltage
           strcat(webvolt1," V");                         // and V to the end

           char webmA1[8];
           itoa(EMA_C[3], webmA1, 10);                    // find port current
           strcat(webmA1," mA");                          // add mA to it

        doc["volt3"] = webvolt1;                          // set voltage here (on page)
        if (darkState == false)                           // light mode on the webpage
        {
          doc["port3"] = "black";                         // text is black
          doc["mastyle3"] = "black";                      // text is black
          if (voltlockout == 0)                           // not in voltage lockout
          {
            doc["voltstyle3"] = "black";                  // text is black
          }
          else                                            // in voltage lcokout
          {
            doc["voltstyle3"] = "red";                    // issue with voltage show it red
          }
          if (port_state[3] != 10 && port_state[3] != 11) // not in current lockout
          {
            if (port_state[3] == 0)                       // port is off
            {
              if (overrideMODE == false)                  // not in override mode
              {
                doc["border3"] = "#000000";                // LED is considered off
              }
              else                                        // in override mode (true) - LED can be anything we want
              {
                if (whinew[3] == 0)                       // white LED is off do basic RGB to HEX conversion
                {
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", rednew[3],grnnew[3],blunew[3]);
                  if (ledmode[3] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border3"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border3"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border3"] = hex;                  // set custom HEX color
                  }
                }
                else if (whinew[3] == 255)                // full white called - it will overpower the colors
                {
                  if (ledmode[3] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border3"] = "#ffffff";          // set border to white
                    }
                    else                                  // LED is off
                    {
                      doc["border3"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border3"] = "#ffffff";          // set border to white
                  }
                }
                else                                      // the RGBW color is mixed time for Math
                {
                  ESP_Color::Color color(rednew[3],grnnew[3],blunew[3]);  // normal RGB value
                  auto hsv = color.ToHsv();                               // change it to HSV
                  white_reverse = map(whinew[3],0,255,255,0);             // flip white value
                  new_sat = (hsv.S * (white_reverse / 255.0F));           // calculate the new saturation level
                  auto RGB = color.FromHsv(hsv.H, new_sat, hsv.V);        // create our new RGB value
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", RGB.R, RGB.G, RGB.B);       // create our HEX value
                  if (ledmode[3] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border3"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border3"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border3"] = "#ffffff";            // set border to white
                  }
                }
              }
              doc["ma3"] = "0 mA";                        // no power is flowing
              doc["p3"] = "DISABLE";                      // power is disabled
              doc["d3"] = "DISABLE";                      // data is disabled
            }
            if (port_state[3] == 1)                       // power is on
            {
              if (overrideMODE == false)                  // not in override mode
              {
                doc["border3"] = "#ffff00";                // LED is considered yellow
              }
              else                                        // in override mode (true) - LED can be anything we want
              {
                if (whinew[3] == 0)                       // white LED is off do basic RGB to HEX conversion
                {
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", rednew[3],grnnew[3],blunew[3]);
                  if (ledmode[3] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border3"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border3"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border3"] = hex;                  // set custom HEX color
                  }
                }
                else if (whinew[3] == 255)                // full white called - it will overpower the colors
                {
                  if (ledmode[3] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border3"] = "#ffffff";          // set border to white
                    }
                    else                                  // LED is off
                    {
                      doc["border3"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border3"] = "#ffffff";            // set border to white
                  }
                }
                else                                      // the RGBW color is mixed time for Math
                {
                  ESP_Color::Color color(rednew[3],grnnew[3],blunew[3]);  // normal RGB value
                  auto hsv = color.ToHsv();                               // change it to HSV
                  white_reverse = map(whinew[3],0,255,255,0);             // flip white value
                  new_sat = (hsv.S * (white_reverse / 255.0F));           // calculate the new saturation level
                  auto RGB = color.FromHsv(hsv.H, new_sat, hsv.V);        // create our new RGB value
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", RGB.R, RGB.G, RGB.B);       // create our HEX value
                  if (ledmode[3] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border3"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border3"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border3"] = hex;                  // set custom HEX color
                  }
                }
              }
              doc["ma3"] = webmA1;                        // show mA
              doc["p3"] = "ENABLE";                       // power is enabled
              doc["d3"] = "DISABLE";                      // data is disabled
            }
            if (port_state[3] == 2)                       // data is on
            {
              if (overrideMODE == false)                  // not in override mode
              {
                doc["border3"] = "#00ff00";                // LED is considered green
              }
              else                                        // in override mode (true) - LED can be anything we want
              {
                if (whinew[3] == 0)                       // white LED is off do basic RGB to HEX conversion
                {
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", rednew[3],grnnew[3],blunew[3]);
                  if (ledmode[3] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border3"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border3"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border3"] = hex;                  // set custom HEX color
                  }
                }
                else if (whinew[3] == 255)                // full white called - it will overpower the colors
                {
                  if (ledmode[3] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border3"] = "#ffffff";          // set border to white
                    }
                    else                                  // LED is off
                    {
                      doc["border3"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border3"] = "#ffffff";            // set border to white
                  }
                }
                else                                      // the RGBW color is mixed time for Math
                {
                  ESP_Color::Color color(rednew[3],grnnew[3],blunew[3]);  // normal RGB value
                  auto hsv = color.ToHsv();                               // change it to HSV
                  white_reverse = map(whinew[3],0,255,255,0);             // flip white value
                  new_sat = (hsv.S * (white_reverse / 255.0F));           // calculate the new saturation level
                  auto RGB = color.FromHsv(hsv.H, new_sat, hsv.V);        // create our new RGB value
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", RGB.R, RGB.G, RGB.B);       // create our HEX value
                  if (ledmode[3] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border3"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border3"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border3"] = hex;                  // set custom HEX color
                  }
                }
              }
              doc["ma3"] = webmA1;                        // show mA
              doc["p3"] = "ENABLE";                       // power is enabled
              doc["d3"] = "ENABLE";                       // data is enabled
            }
          }
          else                                            // in current lockout
          {
            doc["mastyle3"] = "red";                      // current state - show red in lockout
            doc["border3"] = "#8a8a8a";
            doc["ma3"] = "----";   
            doc["p3"] = "DISABLE";
            doc["d3"] = "DISABLE"; 
          }
        }
        else                                              // dark mode on the webpage
        {
          doc["port3"] = "white";
          doc["mastyle3"] = "white";
          if (voltlockout == 0)                           // not in voltage lockout
          {
            doc["voltstyle3"] = "white";
          }
          else                                            // in voltage lcokout
          {
            doc["voltstyle3"] = "red";
          }
          if (port_state[3] != 10 && port_state[3] != 11) // not in current lockout
          {
            if (port_state[3] == 0)                       // port is off
            {
              if (overrideMODE == false)                  // not in override mode
              {
                doc["border3"] = "#000000";                // LED is considered off
              }
              else                                        // in override mode (true) - LED can be anything we want
              {
                if (whinew[3] == 0)                       // white LED is off do basic RGB to HEX conversion
                {
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", rednew[3],grnnew[3],blunew[3]);
                  if (ledmode[3] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border3"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border3"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border3"] = hex;                  // set custom HEX color
                  }
                }
                else if (whinew[3] == 255)                // full white called - it will overpower the colors
                {
                  if (ledmode[3] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border3"] = "#ffffff";            // set border to white
                    }
                    else                                  // LED is off
                    {
                      doc["border3"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border3"] = "#ffffff";            // set border to white
                  }
                }
                else                                      // the RGBW color is mixed time for Math
                {
                  ESP_Color::Color color(rednew[3],grnnew[3],blunew[3]);  // normal RGB value
                  auto hsv = color.ToHsv();                               // change it to HSV
                  white_reverse = map(whinew[3],0,255,255,0);             // flip white value
                  new_sat = (hsv.S * (white_reverse / 255.0F));           // calculate the new saturation level
                  auto RGB = color.FromHsv(hsv.H, new_sat, hsv.V);        // create our new RGB value
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", RGB.R, RGB.G, RGB.B);       // create our HEX value
                  if (ledmode[3] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border3"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border3"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border3"] = hex;                  // set custom HEX color
                  }
                }
              }
              doc["ma3"] = "0 mA";                        // no power is flowing
              doc["p3"] = "DISABLE";                      // power is disabled
              doc["d3"] = "DISABLE";                      // data is disabled
            }
            if (port_state[3] == 1)                       // power is on
            {
              if (overrideMODE == false)                  // not in override mode
              {
                doc["border3"] = "#ffff00";                // LED is considered yellow
              }
              else                                        // in override mode (true) - LED can be anything we want
              {
                if (whinew[3] == 0)                       // white LED is off do basic RGB to HEX conversion
                {
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", rednew[2],grnnew[2],blunew[2]);
                  if (ledmode[3] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border3"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border3"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border3"] = hex;                  // set custom HEX color
                  }
                }
                else if (whinew[3] == 255)                // full white called - it will overpower the colors
                {
                  if (ledmode[3] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border3"] = "#ffffff";            // set border to white
                    }
                    else                                  // LED is off
                    {
                      doc["border3"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border3"] = "#ffffff";            // set border to white
                  }
                }
                else                                      // the RGBW color is mixed time for Math
                {
                  ESP_Color::Color color(rednew[3],grnnew[3],blunew[3]);  // normal RGB value
                  auto hsv = color.ToHsv();                               // change it to HSV
                  white_reverse = map(whinew[3],0,255,255,0);             // flip white value
                  new_sat = (hsv.S * (white_reverse / 255.0F));           // calculate the new saturation level
                  auto RGB = color.FromHsv(hsv.H, new_sat, hsv.V);        // create our new RGB value
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", RGB.R, RGB.G, RGB.B);       // create our HEX value
                  if (ledmode[3] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border3"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border3"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border3"] = hex;                  // set custom HEX color
                  }
                }
              }
              doc["ma3"] = webmA1;                        // ******** show mA
              doc["p3"] = "ENABLE";                       // power is enabled
              doc["d3"] = "DISABLE";                      // data is disabled
            }
            if (port_state[3] == 2)                       // data is on
            {
              if (overrideMODE == false)                  // not in override mode
              {
                doc["border3"] = "#00ff00";                // LED is considered green
              }
              else                                        // in override mode (true) - LED can be anything we want
              {
                if (whinew[3] == 0)                       // white LED is off do basic RGB to HEX conversion
                {
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", rednew[3],grnnew[3],blunew[3]);
                  if (ledmode[3] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border3"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border3"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border3"] = hex;                  // set custom HEX color
                  }
                }
                else if (whinew[3] == 255)                // full white called - it will overpower the colors
                {
                  if (ledmode[3] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border3"] = "#ffffff";            // set border to white
                    }
                    else                                  // LED is off
                    {
                      doc["border3"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border3"] = "#ffffff";            // set border to white
                  }
                }
                else                                      // the RGBW color is mixed time for Math
                {
                  ESP_Color::Color color(rednew[3],grnnew[3],blunew[3]);  // normal RGB value
                  auto hsv = color.ToHsv();                               // change it to HSV
                  white_reverse = map(whinew[3],0,255,255,0);             // flip white value
                  new_sat = (hsv.S * (white_reverse / 255.0F));           // calculate the new saturation level
                  auto RGB = color.FromHsv(hsv.H, new_sat, hsv.V);        // create our new RGB value
                  char hex[7] = {0};
                  sprintf(hex,"%02X%02X%02X", RGB.R, RGB.G, RGB.B);       // create our HEX value
                  if (ledmode[3] == 2)                    // we are flashing this LED
                  {
                    if (ledState == HIGH)                 // LED is on
                    {
                      doc["border3"] = hex;                // set custom HEX color
                    }
                    else                                  // LED is off
                    {
                      doc["border3"] = "#000000";          // LED is considered off
                    }
                  }
                  else                                    // not in override flash mode - show normal color
                  {
                    doc["border3"] = hex;                  // set custom HEX color
                  }
                }
              }
              doc["ma3"] = webmA1;                        // ******** show mA
              doc["p3"] = "ENABLE";                       // power is enabled
              doc["d3"] = "ENABLE";                       // data is enabled
            }
          }
          else                                            // in current lockout
          {
            doc["mastyle3"] = "red";                      // current state - show red in lockout
            doc["border3"] = "#8a8a8a";
            doc["ma3"] = "----";   
            doc["p3"] = "DISABLE";
            doc["d3"] = "DISABLE";
            
          }
        }
      }
      else                                                // not found INA port 1
      {
        doc["border3"] = "#422a2a";
        doc["port3"] = "red";
        doc["volt3"] = "----";                            // no volts to calculate
        doc["voltstyle3"] = "red";
        doc["mastyle3"] = "red";                          // current state - show red in lockout
        doc["ma3"] = "----";                              // no power to calculate
        doc["p3"] = "DISABLE";                            // power is disabled
        doc["d3"] = "DISABLE";                            // data is disabled
      }

      String buf;
      serializeJson(doc, buf);                           // package the data

      ws.textAll(buf);                                   // send the data
      lastUpdate = millis();                             // last data update

}
#endif
