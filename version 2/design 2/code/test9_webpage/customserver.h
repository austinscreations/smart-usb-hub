/* Handles The ASYNC server webpages*/

#ifndef customserver_h
#define customserver_h

const char* PARAM_INPUT_1 = "state";

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
    switch (type) {
      case WS_EVT_CONNECT:
        ws_connected++; // add to our connected websocket counted
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
        break;
      case WS_EVT_DISCONNECT:
        ws_connected--; // subtract from our websocket count
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
        break;
      case WS_EVT_DATA:
      case WS_EVT_PONG:
      case WS_EVT_ERROR:
        break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}


void OTA_Restart()
{
    yield();
    delay(250);
    yield();
#if defined(ESP8266)
    ESP.restart();
#elif defined(ESP32)
    // ESP32 will commit sucide
    esp_task_wdt_init(1, true);
    esp_task_wdt_add(NULL);
    while (true);
#endif
}

boolean customInit() {
    DEBUG_Init("ASYNC Server Starting");

    server.on("/pressed", HTTP_GET, [] (AsyncWebServerRequest *request) {
    // Serial.print("pressed : ");
    if (request->hasParam(PARAM_ID)) {
     String inputMessage1 = request->getParam(PARAM_ID)->value();
      //  Serial.println(inputMessage1);
//      WIFIbuttonSTATE[inputMessage1.toInt()] = LOW;
    }
    request->send(200, "text/plain", "OK");
    });

    server.on("/released", HTTP_GET, [] (AsyncWebServerRequest *request) {
    //Serial.print("Released : ");
    if (request->hasParam(PARAM_ID)) {
      String inputMessage2 = request->getParam(PARAM_ID)->value();
     // Serial.println(inputMessage2);
//      WIFIbuttonSTATE[inputMessage2.toInt()] = HIGH;
    }
    request->send(200, "text/plain", "OK");
    });

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->redirect("/home");
    });
    DEBUG_LineOut("Page: /");

    server.on("/home", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/html", home_html, processor);
    });
    DEBUG_LineOut("Page: /home");

    server.on("/config", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/html", config_form, processor);
    });
    DEBUG_LineOut("Page: /config");

    server.on("/state", HTTP_GET, [](AsyncWebServerRequest *request){ // sets online status
     if (WiFi.status() != WL_CONNECTED)
     {
      request->send_P(200, "text/plain", "orange");
     }
     else
     {
      request->send_P(200, "text/plain", "green");
     }
//    Serial.print("Received request from client with IP: ");         /////////////
//    Serial.println(request->client()->remoteIP());                  /////////////
     });

    server.on("/management", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/html", management_html, processor);
    });
    DEBUG_LineOut("Page: /management");

    server.on("/complete", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/html", finished_html, processor );
        restartRequired = true;
    });

    server.on("/failedOTA", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/html", failed_html, processor );
    });

    server.on("/reboot", HTTP_GET, [](AsyncWebServerRequest *request) {
     request->send_P(200, "text/html", reboot_html, processor );
     restartRequired = true;
    });

    server.on("/factory", HTTP_GET, [](AsyncWebServerRequest *request) {            
//     request->send_P(200, "text/html", reboot_html, processor );
     request->redirect("/factorypage");
     lastDelete = millis();
     factoryRequired = true;
    });

    server.on("/factorypage", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/html", factory_page, processor );
    });

    server.on("/wifisave", HTTP_GET, [](AsyncWebServerRequest *request) {
        wifisaving(request);
        request->send_P(200, "text/html", finished_config, processor );
//        restartRequired = true;
    });

    server.on("/darkmode", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage1;
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
      if (inputMessage1 == "1"){ darkState = !darkState;}
    }
    request->send(200, "text/plain", "OK");
    });

    server.on("/management", HTTP_POST, [&](AsyncWebServerRequest *request) {
                // the request handler is triggered after the upload has finished... 
                // create the response, add header, and send response
//                 if (!_server->authenticate(_username.c_str(), _password.c_str())) {
//                  return;
//                 }
                AsyncWebServerResponse *response = request->beginResponse((Update.hasError())?500:200, "text/plain", (Update.hasError())?"FAIL":"OK");
                response->addHeader("Connection", "close");
                response->addHeader("Access-Control-Allow-Origin", "*");
                request->send(response);
                restartRequired = true;
            }, [&](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
                //Upload handler chunks in data
                
                if (!index) 
                {

             #if defined(ESP8266)
                int cmd = (filename == "filesystem") ? U_FS : U_FLASH;
                Update.runAsync(true);
                size_t fsSize = ((size_t)&_FS_end - (size_t)&_FS_start);
                uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
                if (!Update.begin((cmd == U_FS) ? fsSize : maxSketchSpace, cmd))
                { // Start with max available size
             #elif defined(ESP32)
                int cmd = (filename == "filesystem") ? U_SPIFFS : U_FLASH;
                if (!Update.begin(UPDATE_SIZE_UNKNOWN, cmd))
                { // Start with max available size
             #endif
                    Update.printError(Serial);
                    return request->send(400, "text/plain", "OTA could not begin");
                }
            }

            // Write chunked data to the free sketch space
            if (len)
            {
                if (Update.write(data, len) != len)
                {
                    return request->send(400, "text/plain", "OTA could not begin");
                }
            }

            if (final)
            { // if the final flag is set then this is the last frame of data
                if (!Update.end(true))
                { //true to set the size to the current progress
                    Update.printError(Serial);
                    return request->send(400, "text/plain", "Could not end OTA");
                }
            }
             else
             {
                return;
             } } 
        );

  server.onNotFound([](AsyncWebServerRequest *request){request->send(404);});
  server.begin();
  DEBUG_Success("ASYNC Server Started - customInit");
  DEBUG_Separator();
  return true;
}


#endif
