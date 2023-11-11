#include <Wire.h>
#include <connect.h>
#include <display.h>
//#include <overair.h>
//#include <L298N.h>
//#include <time.h>

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

#define BUTTON_PIN 36
static int count = 0;
int powerState = 0;
bool updateInProgress = false;

void initializeCounter(){
    pinMode(BUTTON_PIN, INPUT);
    int powerState = digitalRead(BUTTON_PIN);
}

void initializeSecondCounter() {
    display.fillRect(0, 0, 90, 15, BLACK); //keep space clean for next count
    display.setCursor(0,0);
    display.print(count);
    display.display();
    //count--;
    delay(150); // Delay for 1 second
}

//START OF THE PROGRAM
void setup() {
    pinMode(BUTTON_PIN, INPUT);
    Serial.begin(9600);
    initializeDisplay();
    initializeWifi();
    initializeOTA();
    initializeSecondCounter();
    initializeMessage();
    //countdownDisplay();
}

void loop() {
    ArduinoOTA.handle(); //OTA handler
    //Serial.println(clock_gettime());
    //initializeSecondCounter(); 


    powerState = digitalRead(BUTTON_PIN);

    if (powerState == HIGH) {
        powerState = LOW;
        count++;   
        initializeSecondCounter();
        timeClient.update();
        Serial.println(timeClient.getFormattedTime());
    }
    //display.startscrollleft(0x00, 0x01);

/*     if (digitalRead(BUTTON_PIN) == HIGH ) {
        count += 1;
        Serial.print("fuck");
    }
    display.fillRect(70, 0, 70, 20, BLACK); //keep space clean for next count
    display.setCursor(75,0);
    display.print(count);
    display.display(); */
    //Serial.print(digitalRead(BUTTON_PIN));
}
