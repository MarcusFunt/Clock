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

// config.h
#define SENSOR_PIN 33
#define EMA_ALPHA 0.15
#define LIGHT_HISTORY_SIZE 10

int previousbrightness = 0; // Initialize with default values
int previousminute = 0;

int blue, red;
int lightIntensity = 0;
void WiFiReconnectTask(void* parameter);

const char* ssid = "33bGuest";
const char* password = "Holmsteen";
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

bool Softerror = false;
bool Harderror = false;


int fallbackHour, fallbackMinute;
const int DisplayPin = 32;
const int SensorPin = 33;
int hour, minute;

bool displayUpdateRequired = true;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, DisplayPin, NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG, NEO_GRB + NEO_KHZ800);

#endif // COMMON_H