#ifndef __MAIN_H__
#define __MAIN_H__

#include <Arduino.h>
#include "rtos_main.h"


// Button
#define BUTTON_PIN_1 10
#define BUTTON_PIN_2 11
#define BUTTON_PIN_3 12
#define BUTTON_PIN_4 13

// WS2812B
#define PINSLED 21

// MICROPHONE
#define PIN_MICROPHONE 7

// TFT config
// #define PIN_SHUN
#ifdef PIN_SHUN

#define CS1_PIN 1
#define CS2_PIN 2
#define CS3_PIN 3
#define CS4_PIN 4
#define CS5_PIN 5
#define CS6_PIN 6

#else

#define CS1_PIN 6
#define CS2_PIN 5
#define CS3_PIN 4
#define CS4_PIN 3
#define CS5_PIN 2
#define CS6_PIN 1

#endif


// #define TOUCH_CS -1
// #define TFT_MISO -1
// #define TFT_RST 33
// #define TFT_DC 34
// #define TFT_MOSI 35
// #define TFT_SCLK 36
// #define TFT_BL 37

// #define TFT_WIDTH 80
// #define TFT_HEIGHT 160
// #define SPI_FREQUENCY 20000000
// #define SPI_READ_FREQUENCY 20000000
// #define SPI_TOUCH_FREQUENCY 2500000
// #define ST7735_DRIVER
// #define ST7735_GREENTAB160x80
// #define TFT_INVERSION_ON
// #define LOAD_GLCD
// #define SMOOTH_FONT
// #define TFT_RGB_ORDER TFT_BGR

#endif // __MAIN_H__
