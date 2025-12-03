#include "EZMatrix.h"

EZMatrix::EZMatrix(LedControl &controller)
  : lc(controller) {}

void EZMatrix::begin(uint8_t intensity) {
  lc.shutdown(0, false);
  lc.setIntensity(0, intensity);
  lc.clearDisplay(0);
}

void EZMatrix::clear() {
  lc.clearDisplay(0);
}

// auto-rotated 90 degrees clockwise
void EZMatrix::draw(byte grid[8][8]) {
  for (int r = 0; r < 8; r++) {
    byte rowByte = 0;
    for (int c = 0; c < 8; c++) {
      // rotate: new[r][c] = old[7-c][r]
      byte pixel = grid[7 - c][r];
      rowByte |= (pixel << (7 - c));
    }
    lc.setRow(0, r, rowByte);
  }
}
