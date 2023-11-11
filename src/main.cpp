#include <Wire.h>
#include <connect.h>
#include <display.h>
#include <overair.h>
//#include <L298N.h>

#define BUTTON_PIN 36
static int count = 0;
int powerState = 0;
bool updateInProgress = false;

void initializeCounter(){
    pinMode(BUTTON_PIN, INPUT);
    int powerState = digitalRead(BUTTON_PIN);
}

void initializeSecondCounter() {
    display.fillRect(50, 50, 90, 15, BLACK); //keep space clean for next count
    display.setCursor(0,50);
    display.print(count);g
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
    
    //countdownDisplay();
}

void loop() {
    ArduinoOTA.handle(); //OTA handler
    //Serial.println(clock_gettime());
    //initializeSecondCounter(); 
    powerState = digitalRead(BUTTON_PIN);
    timeClient.update();
    initializeMessage(timeClient.getFormattedTime());
    //initializeSecondCounter();

    if (powerState == HIGH) {
        powerState = LOW;
        count++;   
        initializeSecondCounter();
        
        Serial.println("yahoy");
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
