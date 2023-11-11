// wifi.h
#ifndef CONNECT_H
#define CONNECT_H

#include <NTPClient.h>
#include <WiFi.h>

extern NTPClient timeClient;

void initializeWifi();

#endif  // DISPLAY_H