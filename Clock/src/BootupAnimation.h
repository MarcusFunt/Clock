
#include "common.h"


void bootupAnimation() {
  // Play a simple animation with bouncing dots
  int x = 0, y = 0, dx = 1, dy = 1;
  for (int i = 0; i < 40; i++) {
    matrix.fillScreen(0);
    matrix.drawPixel(x, y, matrix.Color(128, 128, 128));
    matrix.show();
    delay(50);
    x += dx;
    y += dy;
    if (x <= 0 || x >= matrix.width() - 1) {
      dx *= -1;
    }
    if (y <= 0 || y >= matrix.height() - 1) {
      dy *= -1;
    }
  }
  // Clear the display after the animation
  matrix.fillScreen(0);
  matrix.show();
}
