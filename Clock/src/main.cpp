
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#include "common.h"


#include "LightSensor.h"
#include "TimeNTC.h"

#include "WifiRetry.h"
#include "DisplayStuff.h"
#include "BootupAnimation.h"

#include "ErrorState.h"

ErrorState errorState;


void lightSensorTask(void* parameter) {
    while (true) {
        Light();
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}


    bool isWifiConnected = false;

void setup() {
    Serial.begin(115200);
    // Initialize the NeoMatrix display
    matrix.begin();
    matrix.setTextWrap(false);
    matrix.setBrightness(20); // Set the brightness to a moderate level
    // Play the bootup animation
    bootupAnimation();
    // Connect to WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    isWifiConnected = true;
    // Configure time
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    // Initialize the RTC
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    getLocalTime(&timeinfo);
    // Load the fallback time from the RTC
    fallbackHour = timeinfo.tm_hour;
    fallbackMinute = timeinfo.tm_min;
        // Create a new task for WiFi reconnection
        xTaskCreate(
            WiFiReconnectTask,   // Function to be called
            "WiFiReconnect",     // Name of the task
            4096,                // Stack size (in words)
            NULL,                // Parameter to pass to the function
            1,                   // Priority (higher number is higher priority)
            NULL                 // Task handle (not needed in this case)
        );

        xTaskCreate(
        lightSensorTask,   // Function to be called
        "LightSensor",     // Name of the task
        4096,              // Stack size (in words)
        NULL,              // Parameter to pass to the function
        2,                 // Priority (higher number is higher priority)
        NULL               // Task handle (not needed in this case)
    );

        errorState.setErrorHandler(ErrorCode::WIFI_DISCONNECTED, [](ErrorCode code) {
        // Handle WiFi disconnection error
        Serial.println("WiFi disconnected");
    });

    errorState.setErrorHandler(ErrorCode::TIME_NOT_SYNCED, [](ErrorCode code) {
        // Handle time not synced error
        Serial.println("Time not synced");
    });


  matrix.fillScreen(0); // Clear the display
}



void loop() {
    time();
    if (hour != previousHour || minute != previousMinute) {
        displayUpdateRequired = true;
        previousHour = hour;
        previousMinute = minute;
    }

    if (lightIntensity != previousLightIntensity) {
        displayUpdateRequired = true;
        previousLightIntensity = lightIntensity;
    }

    Display();
    errorState.checkForErrors();

    static unsigned long lastFallbackUpdate = 0;
    if (millis() - lastFallbackUpdate >= 3600000) { // Update fallback time every hour
        updateFallbackTime();
        lastFallbackUpdate = millis();
    }

    delay(200);
}

