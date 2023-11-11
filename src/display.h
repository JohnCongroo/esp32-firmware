// display.h
#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 display;

//extern int count;

void initializeDisplay();

void initializeMessage(String message);

//void initializeSecondCounter();

#endif  // DISPLAY_H