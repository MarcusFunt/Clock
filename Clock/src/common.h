#ifndef COMMON_H
#define COMMON_H

#include <Arduino.h>
#include <WiFi.h>
#include "time.h"
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include "esp_timer.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "config.h"



// config.h

#define EMA_ALPHA 0.15


int previousbrightness = 0; // Initialize with default values
int previousminute = 0;

int blue, red, green;
int lightIntensity = 0;
void WiFiReconnectTask(void* parameter);

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
const char* ntpServer = NTP_SERVER;
const long gmtOffset_sec = GMT_OFFSET;
const int daylightOffset_sec = DAYLIGHT_OFFSET;

const int fallbacktimeupdate = FALLBACKTIMEUPDATE;

bool Softerror = false;
bool Harderror = false;

const float emalimmitMAX = EMACALIBRATIONMAX;
const float emalimmitMIN = EMACALIBRATIONMIN;

const int loopdelay = UPDATESPEED;

int fallbackHour, fallbackMinute;
const int DisplayPin = DISPLAY_PIN;
const int SensorPin = SENSOR_PIN;
int hour, minute;

const int brightnessofdisplay = BRIGHTNESS;

const int numreadings = NUMBEROFREADINGSPERREADING;

const int maxreading = MAXACTUALLIGHT;

bool displayUpdateRequired = true;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, DisplayPin, NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG, NEO_GRB + NEO_KHZ800);

#endif // COMMON_H