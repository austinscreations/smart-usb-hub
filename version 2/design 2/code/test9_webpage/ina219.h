/* functions for INA219 measurements */ 

#ifndef ina219_h
#define ina219_h

bool INA_SETUP()
{
  if (! ina219_0.begin()) 
   {
    Serial.println("Failed to find INA219 on port 1 - INA_SETUP");
    port_INA[0] = true;
   }
   if (! ina219_1.begin()) 
   {
    Serial.println("Failed to find INA219 on port 2 - INA_SETUP");
    port_INA[1] = true;
   }
   if (! ina219_2.begin()) 
   {
    Serial.println("Failed to find INA219 on port 3 - INA_SETUP");
    port_INA[2] = true;
   }
   if (! ina219_3.begin()) 
   {
    Serial.println("Failed to find INA219 on port 4 - INA_SETUP");
    port_INA[3] = true;
   }

   EMA_C[0] = ina219_0.getCurrent_mA();  //set EMA C for t=1
   EMA_C[1] = ina219_1.getCurrent_mA();  //set EMA C for t=1
   EMA_C[2] = ina219_2.getCurrent_mA();  //set EMA C for t=1
   EMA_C[3] = ina219_3.getCurrent_mA();  //set EMA C for t=1
   
   EMA_W[0] = ina219_0.getPower_mW();    //set EMA W for t=1
   EMA_W[1] = ina219_1.getPower_mW();    //set EMA W for t=1
   EMA_W[2] = ina219_2.getPower_mW();    //set EMA W for t=1
   EMA_W[3] = ina219_3.getPower_mW();    //set EMA W for t=1

   portcurrent[0] = portcurrent0;
   portcurrent[1] = portcurrent1;
   portcurrent[2] = portcurrent2;
   portcurrent[3] = portcurrent3;

   Serial.println("INA_SETUP done");
}

void voltread()
{
    if ((millis() - lastvoltread) > 50) // our last voltage reading
    {
      uint8_t divnum = 0;
      busvoltage = 0;
      if (port_INA[0] != true)
      {
        busvoltage = busvoltage + ina219_0.getBusVoltage_V();
        divnum++;
      }
      if (port_INA[1] != true)
      {
        busvoltage = busvoltage + ina219_1.getBusVoltage_V();
        divnum++;
      }
      if (port_INA[2] != true)
      {
        busvoltage = busvoltage + ina219_2.getBusVoltage_V();
        divnum++;
      }
      if (port_INA[3] != true)
      {
        busvoltage = busvoltage + ina219_3.getBusVoltage_V();
        divnum++;
      }
      busvoltage = (busvoltage/divnum);
      
//      busvoltage = ((ina219_1.getBusVoltage_V() + ina219_2.getBusVoltage_V() + ina219_3.getBusVoltage_V() + ina219_4.getBusVoltage_V()) / 4);
     if (DEBUG_voltage){Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");}
     if (busvoltage <= 4.70)                       //under voltage condition
     {
      if (DEBUG_voltage){Serial.println("under voltage");}
      voltlockout = 1;
     }
     if (busvoltage >= 5.70)                       //over voltage condition
     {
      if (DEBUG_voltage){Serial.println("over voltage");}
      voltlockout = 2;
     }
     if (busvoltage >= 4.90 && busvoltage <= 5.40) //normal condition
     {
      if (DEBUG_voltage){Serial.println("normal voltage");}
      voltlockout = 0;
     }
      lastvoltread = millis(); 
    }
    if ((millis() - lastvoltmqtt) > 500)
    {
      if (voltlockout == 1)                      //under voltage condition
     {
       sprintf_P(mqtt_volt_buffer, PSTR("{\"Mode\":\"%s\", \"Volts\":%.2f}"), "Under Voltage", busvoltage);
       client.publish(out_topic3, mqtt_volt_buffer);
     }
     if (voltlockout == 2)                       //over voltage condition
     {
       sprintf_P(mqtt_volt_buffer, PSTR("{\"Mode\":\"%s\", \"Volts\":%.2f}"), "Over Voltage", busvoltage);
       client.publish(out_topic3, mqtt_volt_buffer);
     }
     if (voltlockout == 0)                       //normal condition
     {
       sprintf_P(mqtt_volt_buffer, PSTR("{\"Mode\":\"%s\", \"Volts\":%.2f}"), "Normal", busvoltage);
       client.publish(out_topic3, mqtt_volt_buffer);
     }
      lastvoltmqtt = millis(); 
    }
    
}

void voltanimation() // animation of volt conditions on led's
{
 if (voltlockout != 0) //we have a lock out condition
 {
  ringupdate(); // update led ring animation varibles
  if (voltlockout == 1)
  {
    if (fwd != fwd_prev)
    {
      voltring(255,0,0,0,0,0,0,255); //red with white dot
      voltlockout_prev = true;
    }
  }
  if (voltlockout == 2)
  {
    if (fwd != fwd_prev)
    {
      voltring(0,0,0,255,255,0,0,0); //white with red dot
      voltlockout_prev = true;
    }
  }
 }
 else // all good on voltage
 {
  if (voltlockout_prev == true) // we had a lockout - cleared now, reset leds
  {
    colorWipe(0,0,0,0);
    voltlockout_prev = false;
  }
 }
}

void get_INA(uint8_t port) // send what port you need a value calcuated for
{
  if ((millis() - lastINAread[port]) > 10)
    {
      CALCmaxtotal = 0; // reset our total
      for (uint8_t x = 0; x <=4; x++)
      {
        if (x == 0)
        {
          currentValue[x] = ina219_0.getCurrent_mA();
          wattsValue[x]   = ina219_0.getPower_mW();
        }
        if (x == 1)
        {
         currentValue[x] = ina219_1.getCurrent_mA();
         wattsValue[x]   = ina219_1.getPower_mW();
        }
        if (x == 2)
        {
         currentValue[x] = ina219_2.getCurrent_mA();
         wattsValue[x]   = ina219_2.getPower_mW();
        }
        if (x == 3)
        {
         currentValue[x] = ina219_3.getCurrent_mA();
         wattsValue[x]   = ina219_3.getPower_mW();
        }
 
        EMA_C[x] = (EMA_a*currentValue[x]) + ((1-EMA_a)*EMA_C[x]);  //run the EMA
        EMA_W[x] = (EMA_a*wattsValue[x]) + ((1-EMA_a)*EMA_W[x]);    //run the EMA
        if (EMA_C[x] <= 1)
        {
         EMA_C[x] = 0;
         EMA_W[x] = 0;
        }
        CALCmaxtotal = CALCmaxtotal + EMA_C[x];  // add the power being used by this port to system usage
      }
     
      if (EMA_C[port] >= portcurrent[port])      // over current on the port
      {
        // send mqtt message
        port_state[port] = 10;                   // this port is over current set error mode
        neo_update[port] = true;
        mcp_update[port] = true;
        sprintf_P(mqtt_amp_buffer, PSTR("{\"NOTE\":\"%s\", \"Set Point\":%d, \"Port \":%d, \"milliAmps\":%d}"), "Over Current On Port", (int)portcurrent[port], (port+1), (int)EMA_C[port]);
        client.publish(out_topic2, mqtt_amp_buffer);
      }

    // calulate max current
    if (CALCmaxtotal >= (systemcurrent - 500)) // check the system curent isn't above max - accounting for onbaord esp and led power
    {
      for (uint8_t c = 0; c <=4; c++)
      {
        // send mqtt message
        port_state[c] = 11;                    // hub is over current set error mode
        neo_update[c] = true;
        mcp_update[c] = true;
      }
        sprintf_P(mqtt_amp_buffer, PSTR("{\"NOTE\":\"%s\", \"Set Point\":%d, \"Total mA\":%d, \"Port 1 mA\":%d, \"Port 2 mA\":%d, \"Port 3 mA\":%d, \"Port 4 mA\":%d }"), "Over Current On HUB", (int)(systemcurrent - 500), (int)CALCmaxtotal, (int)EMA_C[0], (int)EMA_C[1] , (int)EMA_C[2], (int)EMA_C[3]);
        client.publish(out_topic2, mqtt_amp_buffer);
    }
    lastINAread[port] = millis();
  }
}

void mqtt_INA(uint8_t port, const char* m) // send what port you need a value sent for
{
  if ((millis() - lastINAmqtt[port]) > 250)
  {
    // send mqtt , add voltage to this message
    if (DEBUG_current){Serial.print("Port ");Serial.print((port+1));Serial.print(" Power:     "); Serial.print(EMA_W[port]); Serial.println(" mW");}
    if (DEBUG_current){Serial.print("Port ");Serial.print((port+1));Serial.print(" Current:   "); Serial.print(EMA_C[port]); Serial.println(" mA");}

    sprintf_P(mqtt_amp_buffer, PSTR("{\"Port\":%d, \"Mode\":\"%s\", \"Volts\":%.2f, \"milliWatts\":%d, \"milliAmps\":%d }"), (port+1), m, busvoltage ,(int)EMA_W[port], (int)EMA_C[port]);
    client.publish(out_topic2, mqtt_amp_buffer);
    lastINAmqtt[port] = millis();
  }
}

#endif
