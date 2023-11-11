#include <NTPClient.h>
#include <WiFi.h>
#include <display.h>

WiFiUDP ntpUDP;//time stuff
NTPClient timeClient(ntpUDP, "time.google.com");

void initializeWifi(){
    timeClient.setTimeOffset(-28800);
    const char* networkName = "Benji";
    const char* password = "SuperMiso01!";
    WiFi.begin(networkName, password);
    display.print("Connecting to WiFi...");

    while (WiFi.status() != WL_CONNECTED) {
        display.print(".");
        display.display();
        delay(2000);
    }

    if (WiFi.status() == WL_CONNECTED) {
        display.println("Connected!");
        display.println(WiFi.localIP());
        display.display();
    } else {
        display.println("Failed to connect");
        display.display();
    }
    display.println(WiFi.localIP());
    delay(2500);

}