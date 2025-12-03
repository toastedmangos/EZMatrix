#ifndef EZMATRIX_H
#define EZMATRIX_H

#include <Arduino.h>
#include <LedControl.h>

class EZMatrix {
public:
  EZMatrix(LedControl &controller);
  void begin(uint8_t intensity = 8);
  void draw(byte grid[8][8]);
  void clear();

private:
  LedControl &lc;
};

#endif
