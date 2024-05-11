
#include "common.h"







int previousHour = -1;
int previousMinute = -1;
int previousBrightness = -1;
int previousLightIntensity = -1;

void Display() {
    if (displayUpdateRequired) {
        int Brightness = map(lightIntensity, 0, 255, 5, brightnessofdisplay);

    
            Serial.println("Updating display");

            matrix.setBrightness(Brightness);

            previousHour = hour;
            previousMinute = minute;
            previousBrightness = Brightness;

            matrix.fillScreen(0);  // Clear the screen
            matrix.setCursor(1, 0);  // Set the cursor position to the top-left corner
            matrix.setTextSize(1.175);
            matrix.setTextColor(matrix.Color(red, blue, blue));  // Set the text color

            if (!matrix.printf("%02d:%02d\n", hour, minute)) {
                // Display update failed
                Serial.println("Display update failed.");
                // Add a fallback display mechanism, such as a blinking error message
                matrix.fillScreen(0);
                matrix.setCursor(1, 0);
                matrix.setTextColor(matrix.Color(255, 0, 0));
                matrix.printf("DISP ERR\n");
                matrix.show();
            } else {
                matrix.show();  // Update the display
            }

            displayUpdateRequired = false;

    } else {
        // No update required, skip the function
        Serial.println("No display update required. Skipping function.");
    }}
