
#include "common.h"






void Display() {

    


   int Brightness = map(lightIntensity, 0, 255, 1, 40);
       


         if (Brightness != previousbrightness || minute != previousminute) {
             Serial.println("Updating display");

             matrix.setBrightness(Brightness);

          previousbrightness = Brightness;
          previousminute = minute;


                matrix.fillScreen(0);  // Clear the screen
                matrix.setCursor(1, 0);  // Set the cursor position to the top-left corner
            matrix.setTextSize(1.175);
            matrix.setTextColor(matrix.Color(red, 0, blue));  // Set the text color


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
            
           } else {
        // Variables haven't changed, skip the function
        Serial.println("Variables have not changed. Skipping function.");
        }

    
    
}
