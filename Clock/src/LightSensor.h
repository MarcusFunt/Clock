// LightSensor.h


#define LIGHT_HISTORY_SIZE 10
#include "common.h"


float emaAlpha = 0.15; // Smoothing factor for the EMA (between 0 and 1)
int emaAverage = 0; // Exponential moving average of the light sensor readings

int         light;
int lightHistory[LIGHT_HISTORY_SIZE];
int lightHistoryIndex = 0;



void Light() {
    int sum = 0;
    int validReadings = 0;
    static int errorCount = 0;

    for (int i = 0; i < 5; i++) { // Take 5 readings
        int rawinputlight = analogRead(SensorPin);

        if (rawinputlight < 0 || rawinputlight > 4095) { // Check if the reading is within the valid range
            errorCount++;
            // Light sensor error, use a fallback value
            emaAverage = emaAverage * (1 - emaAlpha) + 450 * emaAlpha; // Use a fallback value of 450 (mid-range)
            Serial.printf("Light sensor error, using fallback value. Error count: %d\n", errorCount);
        } else {
            sum += rawinputlight;
            validReadings++;
        }
        delay(10); // Delay to allow the sensor to stabilize
    }

     if (validReadings > 0) {
        int average = sum / validReadings;

        // Compute the exponential moving average
        emaAverage = emaAverage * (1 - emaAlpha) + average * emaAlpha;

        // Adjust the EMA factor based on the difference between the current reading and the EMA
        int difference = abs(average - emaAverage);
        if (difference > 100) { // Adjust the threshold as needed
            emaAlpha = constrain(emaAlpha + 0.01, 0.01, 0.3); // Increase the EMA factor
        } else if (difference < 50) { // Adjust the threshold as needed
            emaAlpha = constrain(emaAlpha - 0.01, 0.01, 0.3); // Decrease the EMA factor
        }

        // Add the new reading to the history
        lightHistory[lightHistoryIndex] = emaAverage;
        lightHistoryIndex = (lightHistoryIndex + 1) % LIGHT_HISTORY_SIZE;

        // Compute the average of the last 10 readings
        sum = 0;
        for (int i = 0; i < LIGHT_HISTORY_SIZE; i++) {
            sum += lightHistory[i];
        }
        int overallAverage = sum / LIGHT_HISTORY_SIZE;

        // Print the overall average light reading
        Serial.printf("Overall average light reading: %d\n", overallAverage);

        if (overallAverage > (maxreading-1)) {
            overallAverage = (maxreading-1);
        }

        lightIntensity = map(overallAverage, 0, maxreading, 0, 255);

        // Update red and blue based on lightIntensity
        red = 255 - lightIntensity;
        blue = lightIntensity;

        // Ensure the sum of red and blue is always 255
        if (red + blue > 255) {
            red = 255;
            blue = 0;
        }

        Serial.printf("Light Intensity: %d, Red: %d, Blue: %d\n", lightIntensity, red, blue);
    } else {
        // No valid readings, use the fallback value
        Serial.printf("No valid light sensor readings. Using fallback value. Error count: %d\n", errorCount);
    }
}
