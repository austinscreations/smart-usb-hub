// mqtt setup information

#ifndef mqtt_setup_h
#define mqtt_setup_h


void settopics(){ // sets mqtt topics based on hostname
  // *** outputs *** //
  strcpy(clientheart, host);
  strcat(clientheart,"/LWT");
  
  strcpy(clientoutput1, host);
  strcat(clientoutput1,"/button");

  strcpy(clientoutput2, host);
  strcat(clientoutput2,"/port");

  strcpy(clientoutput3, host);
  strcat(clientoutput3,"/volt");

  // *** inputs ***  //
  strcpy(clientinput1, host);
  strcat(clientinput1,"/current");

  /* used in normal mode */
  strcpy(clientinput2, host);
  strcat(clientinput2,"/state");

  strcpy(clientinput3, host);
  strcat(clientinput3,"/brightness");

  strcpy(clientinput4, host);
  strcat(clientinput4,"/override");

  strcpy(clientinput5, host);
  strcat(clientinput5,"/rgbw");

  strcpy(clientinput6, host);
  strcat(clientinput6,"/flash");

  out_heart = clientheart;
  out_topic1 = clientoutput1;
  out_topic2 = clientoutput2;
  out_topic3 = clientoutput3;
  in_topic1 = clientinput1;
  in_topic2 = clientinput2;
  in_topic3 = clientinput3;
  in_topic4 = clientinput4;
  in_topic5 = clientinput5;
  in_topic6 = clientinput6;

  Serial.println(out_heart);
  Serial.println("*** OUTPUTS ***");
  Serial.println(out_topic1);
  Serial.println(out_topic2);
  Serial.println(out_topic3);
  Serial.println("*** INPUTS ***");
  Serial.println(in_topic1);
  Serial.println(in_topic2);
  Serial.println(in_topic3);
  Serial.println(in_topic4);
  Serial.println(in_topic5);
  Serial.println(in_topic6);
  Serial.println("*** Flash Control ***");
  Serial.println("flash");
}


void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  payload[length] = '\0';
   Serial.print("payload: [");
   Serial.print((char *)payload);
   Serial.println("]");

    if (strcmp(topic,"flash")==0){ // flash rate for leds
    if ((char)payload[0] == '1') {ledState = HIGH;} // on
    if ((char)payload[0] == '0') {ledState = LOW;} // off
     if (overrideMODE == true)
     {
      for (uint8_t y = 0; y < 4; y++) // check all the override led states
      {
        if (ledmode[y] == 2) // we are in a flash state so make sure we do regular updates on websocket
        {
          if (ws_connected != 0){webSENDjson();}
        }
      }
     }
    }

  if (strcmp(topic,in_topic4)==0){  // request to activate override mode
   if ((char)payload[0] == '1')     // override active - all hub control goes through mqtt
   {
    overrideMODE = true;
    for (uint8_t y = 0; y < 4; y++) // resetting all 4 led colors
    {
      ledmode[y]= {0}; // what mode the leds are in           -- used in overrideMODE control
      rednew[y] = {0}; // new LED color for override MODE     -- RED
      grnnew[y] = {0}; // new LED color for override MODE     -- GREEN
      blunew[y] = {0}; // new LED color for override MODE     -- BLUE
      whinew[y] = {0}; // new LED color for override MODE     -- WHITE
    }
   }
   if ((char)payload[0] == '0'){overrideMODE = false;} // override NOT active - hub can be controlled locally
  }

  if (strcmp(topic,in_topic1)==0){ // call to configure per port current

   String value = String((char*)payload);

   int iStart, iEnd;
   iStart = 0;
    iEnd = value.indexOf(',', iStart);
     mqttC = value.substring(iStart, iEnd).toInt();
   iStart = iEnd + 1;
    iEnd = value.indexOf(',', iStart);
     mqttCur = value.substring(iStart, iEnd).toInt();

    if (mqttC != 0)
    {
      if (mqttC > 4)
      {
        Serial.println("We only have 4 ports to configure - change your value");
      }
      else
      {
       if (mqttCur > 3000)
       {
        Serial.println("Max port current is 3000mA - setting to max");
        mqttCur = 3000;
       }
       if (mqttCur < 0)
       {
        Serial.println("Current Limit can't be negative - setting to 0");
        mqttCur = 0;
       }

        /* need for future use */
        if (mqttC == 1)
        {
          portcurrent0 = mqttCur;
        }
        if (mqttC == 2)
        {
          portcurrent1 = mqttCur;
        }
        if (mqttC == 3)
        {
          portcurrent2 = mqttCur;
        }
        if (mqttC == 4)
        {
          portcurrent3 = mqttCur;
        }
        
       portcurrent[(mqttC-1)] = mqttCur;
       Serial.print("Port ");
       Serial.print(mqttC);
       Serial.print(" Current Set to: ");
       Serial.print(mqttCur);
       Serial.println("mA");
       DEBUG_Separator();
       saveConfignew();  // save the config
      }
  }
  else
  {
    Serial.println("Ports are 1-based number - change your value");
  }
} // end of per port mqtt config

if (strcmp(topic,in_topic2)==0){ // request to change port state

  String value = String((char*)payload);

   int iStart, iEnd;
   iStart = 0;
    iEnd = value.indexOf(',', iStart);
     mqttC = value.substring(iStart, iEnd).toInt();
   iStart = iEnd + 1;
    iEnd = value.indexOf(',', iStart);
//     mqttState = value.substring(iStart, iEnd).c_str();
     mqttState = value.substring(iStart, iEnd);
//     strcpy(clientoutput1, host);

      // override changes neopixel update
   if (mqttC != 0)
    {
      if (mqttC > 4)
      {
        Serial.println("We only have 4 ports to configure - change your value");
      }
      else
      {
        Serial.print("Setting Port ");
        Serial.print(mqttC);

        if(mqttState == "off"){
          if (port_state[(mqttC-1)] != 0 && voltlockout == 0) // not already off or in over / under current / voltage state
          {
            if (port_state[(mqttC-1)] == 11)                 // over current on hub
            {
              for (uint8_t y = 0; y < 4; y++)                // resetting all 4 port states
              {
                port_state[y] = 0;                           // this is actully setting all ports off
              }
              Serial.println(" HUB State To: off");
            }
            else                                            // other wise we are jsu tsetting a port off (or reseting that port from over current)
            {
              port_state[(mqttC-1)] = 0;                    // turn this port off / reset
              Serial.println(" State To: off");
            }
            if (overrideMODE == false){ neo_update[(mqttC-1)] = true; } // update leds directly if we aren't in override mode
            mcp_update[(mqttC-1)] = true;                               // ensure mcp's update
          }
        }
        else if(mqttState == "power"){
          if (port_state[(mqttC-1)] != 1 && port_state[(mqttC-1)] != 10 && port_state[(mqttC-1)] != 11 && voltlockout == 0) // not already off or in over / under current / voltage state
          {
            Serial.println(" State To: power");
            port_state[(mqttC-1)] = 1;
            if (overrideMODE == false){ neo_update[(mqttC-1)] = true; } // update leds directly if we aren't in override mode
            mcp_update[(mqttC-1)] = true;                               // ensure mcp's update
            lastINAread[(mqttC-1)] = millis();                          // resets the time readout for reading current usage
            lastINAmqtt[(mqttC-1)] = millis();                          // resets the time for the for mqtt current readout
          }
        }
        else if(mqttState == "data"){
          if (port_state[(mqttC-1)] != 2 && port_state[(mqttC-1)] != 10 && port_state[(mqttC-1)] != 11 && voltlockout == 0) // not already off or in over / under current / voltage state
          {
            Serial.println(" State To: data");
            port_state[(mqttC-1)] = 2;
            if (overrideMODE == false){ neo_update[(mqttC-1)] = true; } // update leds directly if we aren't in override mode
            mcp_update[(mqttC-1)] = true;                               // ensure mcp's update
            lastINAread[(mqttC-1)] = millis();                          // resets the time readout for reading current usage
            lastINAmqtt[(mqttC-1)] = millis();                          // resets the time for the for mqtt current readout
          }
        }
        else
        {
          Serial.print(" not a valid state");
          Serial.print(" Attemped State: ");
          Serial.println(mqttState);
        }
      }
    }
    else
    {
      Serial.println("Ports are 1-based number - change your value");
    }
  
} // end of change port state

if (strcmp(topic,in_topic3)==0){ // request to change LED brightness
  String value = String((char*)payload);

  if (value.toInt() >= 0 && value.toInt() <=255)
  {
    brightness = value .toInt();
    strip.setBrightness(brightness);
    if (overrideMODE == false)  // not in overrideMODE - update LED brightness normally
    {
      for(int a=0; a<4; a++) 
      {
        neo_update[a] = true;   // time to update the neopixel
      }
    }
    else                        // in overrideMODE - update the LED's accordingly
    {
      for(int a=0; a<4; a++) 
      {
        neo_override[a] = true; // time to update the neopixel in override mode
      }
    }
    Serial.print("brightness set to: ");
    Serial.println(brightness);
  }
  else
  {
    Serial.println("incompatible LED brightness level - 0-255 allowed");
    Serial.print("recieved value: "); Serial.println(value);
  }
} // end of change LED brightness

if (strcmp(topic,in_topic5)==0){ // call to set regular rgbw color

String value = String((char*)payload);

int iStart, iEnd;
iStart = 0;
iEnd = value.indexOf(',', iStart);
mqttC = value.substring(iStart, iEnd).toInt();

    if (mqttC != 0)
    {
      iStart = iEnd + 1;
      iEnd = value.indexOf(',', iStart);
      rednew[(mqttC-1)] = value.substring(iStart, iEnd).toInt();
      iStart = iEnd + 1;
      iEnd = value.indexOf(',', iStart);
      grnnew[(mqttC-1)] = value.substring(iStart, iEnd).toInt();
      iStart = iEnd + 1;
      iEnd = value.indexOf(',', iStart);
      blunew[(mqttC-1)] = value.substring(iStart, iEnd).toInt();
      iStart = iEnd + 1;
      iEnd = value.indexOf(',', iStart);
      whinew[(mqttC-1)] = value.substring(iStart, iEnd).toInt();
      
    Serial.print("LED #: ");
    Serial.println(mqttC);

    Serial.print("RED: ");
    Serial.println(rednew[(mqttC-1)]);

    Serial.print("GREEN: ");
    Serial.println(grnnew[(mqttC-1)]);

    Serial.print("BLUE: ");
    Serial.println(blunew[(mqttC-1)]); 

    Serial.print("WHITE: ");
    Serial.println(whinew[(mqttC-1)]); 

    ledmode[(mqttC-1)] = 1; // set led to normal color
    neo_override[(mqttC-1)] = true; // time to update the neopixel
    if (ws_connected != 0){ webSENDjson(); }
  }
  else
  {
    Serial.println("LED's are 1-based number - change your value");
  }
} // end of rgbw color set

 if (strcmp(topic,in_topic6)==0){ // call to set RGB color with flash enabled

String value = String((char*)payload);

int iStart, iEnd;
iStart = 0;
iEnd = value.indexOf(',', iStart);
mqttC = value.substring(iStart, iEnd).toInt();

// ****************************************add provisions for lockout modes
    if (mqttC != 0)
    {
      iStart = iEnd + 1;
      iEnd = value.indexOf(',', iStart);
      rednew[(mqttC-1)] = value.substring(iStart, iEnd).toInt();
      iStart = iEnd + 1;
      iEnd = value.indexOf(',', iStart);
      grnnew[(mqttC-1)] = value.substring(iStart, iEnd).toInt();
      iStart = iEnd + 1;
      iEnd = value.indexOf(',', iStart);
      blunew[(mqttC-1)] = value.substring(iStart, iEnd).toInt();
      iStart = iEnd + 1;
      iEnd = value.indexOf(',', iStart);
      whinew[(mqttC-1)] = value.substring(iStart, iEnd).toInt();
      
    Serial.print("LED #: ");
    Serial.println(mqttC);

    Serial.print("RED: ");
    Serial.println(rednew[(mqttC-1)]);

    Serial.print("GREEN: ");
    Serial.println(grnnew[(mqttC-1)]);

    Serial.print("BLUE: ");
    Serial.println(blunew[(mqttC-1)]); 

    Serial.print("WHITE: ");
    Serial.println(whinew[(mqttC-1)]); 

    ledmode[(mqttC-1)] = 2; // set led to normal color
    if (ws_connected != 0){ webSENDjson(); }
  }
  else
  {
    Serial.println("LED's are 1-based number - change your value");
  }
} // end of flash color set



} // end of mqtt callback



void reconnect() {
  
  // Loop until we're reconnected
  while (!client.connected()) {
   colorWipe(0,0,0,220);

    Serial.print("Attempting MQTT connection...");
    if (client.connect(host,mqtt_username,mqtt_password,out_heart, mqtt_lwt_qos, mqtt_lwt_retain, "0")) {
      IPaddress =  WiFi.localIP().toString();
      Serial.println("mqtt connected");
      connected_update = true;
      // Once connected, publish an announcement...
      strcpy(connectphrase, "connected = ");
      strcat(connectphrase, host);
      strcat(connectphrase, "  IP Address = ");
      const char * c = IPaddress.c_str();
      strcat(connectphrase, c); // ip address
      const char* phrase = connectphrase;
      client.publish("outTopic",phrase);
      byte lwt_payload[] = { '1' };
      client.publish(out_heart, lwt_payload, 1, mqtt_lwt_retain);
      // ... and resubscribe
      client.subscribe("flash");
      client.subscribe(in_topic1);
      client.subscribe(in_topic2);
      client.subscribe(in_topic3);
      client.subscribe(in_topic4);
      client.subscribe(in_topic5);
      client.subscribe(in_topic6);

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
//       Wait 5 seconds before retrying
      delay(5000);
     }
  }
}

#endif
