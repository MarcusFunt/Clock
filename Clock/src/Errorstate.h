#ifndef ERRORSTATE_H
#define ERRORSTATE_H

#include "common.h"
#include "DisplayStuff.h"

bool checkForErrors();
void blinkCornerLED();
void displayErrorScreen();
void handleErrors();



bool checkForErrors() {
    bool hasErrors = false;

    // Check WiFi connection status
    if (WiFi.status() != WL_CONNECTED) {
        hasErrors = true;
    }

    // Check NTP sync status
    if (!getLocalTime(&timeinfo)) {
        hasErrors = true;
    }

    return hasErrors;
}

void blinkCornerLED() {
    if (checkForErrors() && (millis() - lastBlinkTime >= blinkInterval)) {
        matrix.drawPixel(0, 0, matrix.Color(0, 0, 255)); // Blue LED
        matrix.show();
        lastBlinkTime = millis();
        blinkLED = !blinkLED; // Toggle the blinkLED flag
    } else if (!checkForErrors() && (millis() - lastBlinkTime >= blinkInterval)) {
        matrix.drawPixel(0, 0, 0); // Turn off the LED
        matrix.show();
        lastBlinkTime = millis();
        blinkLED = !blinkLED; // Toggle the blinkLED flag
    }
}

void displayErrorScreen() {
    matrix.fillScreen(0);
    matrix.setCursor(4, 2);
    matrix.setTextColor(matrix.Color(255, 0, 0));
    matrix.print("ERR");
    matrix.show();
}

void handleErrors() {
    if (checkForErrors()) {
        if (hour != fallbackHour || minute != fallbackMinute) {
            // Display the time with a blinking blue LED in the corner
            updateTimeDisplay(displayErrorScreen);
            blinkCornerLED();
        } else {
            // Display the full error screen
            displayErrorScreen();
        }
    } else {
        // Clear the error state
        matrix.drawPixel(0, 0, 0); // Turn off the LED
        matrix.show();
    }
}

#endif