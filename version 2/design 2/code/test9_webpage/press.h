/* handles local control from button presses */

#ifndef press_h
#define press_h

void portlockout()
{
  for (uint8_t p = 0; p < 4; p++)
 {
   mcp.digitalWrite(MCP_en[p], LOW);
   mcp.digitalWrite(MCP_data[p], LOW);
 }
}

void handleportstate()
{
   for (uint8_t x = 0; x < 4; x++)
 {
   if (last_press[x] != 0 && port_state[x] != 10 && port_state[x] != 11)        // a button was pressed  // makes sure that port isn't locked out for over current
   {
     if (last_press[x] == 1)      // last press was single 
     {
       if (port_state[x] != 1)    // port isn't already on
       {
        port_state[x] = 1;        // turn port on
       }
       else                       // already on, turn off
       {
        port_state[x] = 0;        // turning port off
       }
      last_press[x] = 0;          // resetting press detection
     }
     else if (last_press[x] == 2) // last press was double 
     {
      if (port_state[x] != 2)     // data + power aren't already on
      {
        port_state[x] = 2;        // data + power on
      }
      else                        // already on, turn off
      {
        port_state[x] = 0;        // port turned off
      }
      last_press[x] = 0;          // reset press detection
     }
     else                         // don't care about other presses
     {
      last_press[x] = 0;          // reset press detection
     }
     neo_update[x] = true;        // tell status led's to update
     mcp_update[x] = true;        // tell status led's to update
   }
   else                                                               // we're in a current lockout mode
   {
    if (last_press[x] == 3)      // last press was triple
     {
      if (port_state[x] == 10 )   // port is in over current
       {
        port_state[x] = 0;        // turn port normal
        neo_update[x] = true;     // tell status led's to update
        mcp_update[x] = true;     // tell status led's to update
       }
      if (port_state[x] == 11 )   // hub is in over current
       {
        for (uint8_t c = 0; c < 4; c++)
        {
          port_state[c] = 0;      // turn port hub normal
          neo_update[c] = true;   // tell status led's to update
          mcp_update[c] = true;   // tell status led's to update
        }
       }
      last_press[x] = 0;          // reset press detection
     }
   }
 }
}

void portsSTATE() // handles the state of ports
{
  for (uint8_t y = 0; y < 4; y++)
 {
  if (port_state[y] == 0)
  {
    if (neo_update[y] == true)
    {
      colorSet(y,0,0,0,0); // led off
    }
    if (mcp_update[y] == true)
    {
      mcp.digitalWrite(MCP_en[y], LOW);
      mcp.digitalWrite(MCP_data[y], LOW);
      if (ws_connected != 0){ webSENDjson(); }
      mcp_update[y] = false;
    }
  }
  if (port_state[y] == 1) // power only
  {
    if (neo_update[y] == true)
    {
      colorSet(y,255,255,0,0); // led yellow
    }
    if (mcp_update[y] == true)
    {
      mcp.digitalWrite(MCP_en[y], HIGH);
      mcp.digitalWrite(MCP_data[y], LOW);
      if (ws_connected != 0){ webSENDjson(); }
      mcp_update[y] = false;
    }
      get_INA(y);   // get current measurements for ports / trigger for over current when needed
      mqtt_INA(y, "Power");  // send mqtt message for active port
  }
  if (port_state[y] == 2) // Data + Power
  {
    if (neo_update[y] == true)
    {
      colorSet(y,0,255,0,0); // led green
    }
    if (mcp_update[y] == true)
    {
      mcp.digitalWrite(MCP_en[y], HIGH);
      mcp.digitalWrite(MCP_data[y], HIGH);
      if (ws_connected != 0){ webSENDjson(); }
      mcp_update[y] = false;
    }
      get_INA(y);   // get current measurements for ports / trigger for over current when needed
      mqtt_INA(y, "Data");  // send mqtt message for active port
  }


  /* current states for hub */
  if (port_state[y] == 10) // over current on port
  {
    if (mcp_update[y] == true)
    {
      if (ws_connected != 0){ webSENDjson(); }
      mcp_update[y] = false;
      mcp.digitalWrite(MCP_en[y], LOW);
      mcp.digitalWrite(MCP_data[y], LOW);
    }
    doubleflash(y,255,0,0,0,0,0,0,50); // double red, wait white
  }
  if (port_state[y] == 11) // over current on hub
  {
    if (mcp_update[y] == true)
    {
      mcp.digitalWrite(MCP_en[y], LOW);
      mcp.digitalWrite(MCP_data[y], LOW);
      if (ws_connected != 0){ webSENDjson(); }
      mcp_update[y] = false;
    }
    doubleflashHUB(0,0,0,255,50,0,0,0); // double white, wait red
  }
 }
}

#endif
