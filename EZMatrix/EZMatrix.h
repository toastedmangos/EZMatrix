#ifndef EZMATRIX_H
#define EZMATRIX_H

#include <Arduino.h>
#include <LedControl.h>

class EZMatrix {
public:
  EZMatrix(LedControl &controller);

  void begin(uint8_t intensity = 8);                  // initialize matrix
  void draw(byte grid[8][8]);                         // draw a single frame
  void clear();                                       // clear display
  void animate(byte* frames[], uint8_t numFrames,    // animate multiple frames
               uint16_t delayMs, uint8_t repeats = 255);

private:
  LedControl &lc;
};

#endif
