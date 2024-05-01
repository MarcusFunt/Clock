
#include "common.h"

struct tm timeinfo;



void time() {
    static int failedAttempts = 0;
    if (getLocalTime(&timeinfo)) {
        hour = timeinfo.tm_hour;
        minute = timeinfo.tm_min;
        Serial.printf("Current time: %02d:%02d\n", hour, minute);
        failedAttempts = 0; // Reset the failed attempts counter
    } else {
        failedAttempts++;
        Serial.printf("Failed to obtain time from NTP server. Using fallback time. Failed attempts: %d\n", failedAttempts);
        hour = fallbackHour;
        minute = fallbackMinute;



    }
}



void updateFallbackTime() {
    time_t now;
    time(&now);
    struct tm* localTime = localtime(&now);
    fallbackHour = localTime->tm_hour;
    fallbackMinute = localTime->tm_min;
}