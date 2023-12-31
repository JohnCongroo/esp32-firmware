#include <ArduinoOTA.h>
#include <display.h>

void initializeOTA() {
    ArduinoOTA.begin();
    ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      //Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      //Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      //Serial.printf("Update Progress: %u%%\r", (progress / (total / 100)));
        display.clearDisplay();
        display.setCursor(0,0);
        display.setTextSize(2);
        display.printf("Progress: %u%%\r", (progress / (total / 100)));
        display.display();
    })
    .onError([](ota_error_t error) {
      //Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });
    

    //Serial.println("Ready");
   // Serial.print("IP address: ");
   // Serial.println(WiFi.localIP());

    ArduinoOTA.onStart([]() {
        display.clearDisplay();
        display.setCursor(0,0);
        display.setTextSize(1);
        display.println("Update in progress...");
        display.display();
    });

    ArduinoOTA.onEnd([]() {
        display.println("---------------------");
        display.println("Update Finished");
        display.display();
        delay(2000);
    });
}
