#include "EZMatrix.h"

EZMatrix::EZMatrix(LedControl &controller)
  : lc(controller) {}

void EZMatrix::begin(uint8_t intensity) {
  lc.shutdown(0, false);      // turn on display
  lc.setIntensity(0, intensity);
  lc.clearDisplay(0);
}

void EZMatrix::clear() {
  lc.clearDisplay(0);
}

// Draw frame rotated 90° clockwise to face DOWN
void EZMatrix::draw(byte grid[8][8]) {
  for (int r = 0; r < 8; r++) {           // target row
    byte rowByte = 0;
    for (int c = 0; c < 8; c++) {         // source column
      rowByte |= (grid[7 - c][r] << (7 - c));  // rotate 90° clockwise
    }
    lc.setRow(0, r, rowByte);
  }
}

// Animate frames
void EZMatrix::animate(byte* frames[], uint8_t numFrames, uint16_t delayMs, uint8_t repeats) {
  for (uint8_t r = 0; r < repeats; r++) {
    for (uint8_t f = 0; f < numFrames; f++) {
      draw((byte (*)[8])frames[f]);  // convert pointer back to 2D array
      delay(delayMs);
    }
  }
}
