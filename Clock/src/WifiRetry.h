
#include "common.h"



void WiFiReconnectTask(void* parameter) {
    int retryDelay = 1000; // Initial delay of 1 second
    const int maxRetryDelay = 60000; // Maximum delay of 1 minute
    int connectionLossCount = 0;


    while (true) {
        if (WiFi.status() != WL_CONNECTED) {
            connectionLossCount++;
            Serial.printf("WiFi disconnected. Attempting to reconnect... Connection loss count: %d\n", connectionLossCount);





            WiFi.reconnect();
            unsigned long startTime = millis();
            const unsigned long timeout = 10000; // 10 seconds


            while (WiFi.status() != WL_CONNECTED) {
                if (millis() - startTime > timeout) {
                    Serial.println("Failed to reconnect to WiFi. Retrying...");
                    break;
                }
                vTaskDelay(retryDelay / portTICK_PERIOD_MS);
                Serial.print(".");
            }


            if (WiFi.status() == WL_CONNECTED) {
                Serial.println("WiFi reconnected.");
                connectionLossCount = 0; // Reset the connection loss count
                retryDelay = 1000; // Reset the retry delay


                // Clear the warning message on the matrix
                matrix.fillScreen(0);
                matrix.show();
            } else {
                Serial.println("Failed to reconnect to WiFi.");
                retryDelay *= 2; // Double the retry delay
                if (retryDelay > maxRetryDelay) {
                    retryDelay = maxRetryDelay; // Cap the retry delay at the maximum
                }
            }
        }
        vTaskDelay(10000 / portTICK_PERIOD_MS); // Check WiFi connection every 10 seconds
    }
}


