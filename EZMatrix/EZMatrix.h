#ifndef EZMATRIX_H
#define EZMATRIX_H

#include <Arduino.h>
#include <LedControl.h>

class EZMatrix {
public:
  EZMatrix(LedControl &controller);

  // initialize: intensity 0..15
  void begin(uint8_t intensity = 8);

  // low-level
  void clear();
  void setBrightness(uint8_t intensity);

  // draw: accepts your 8x8 grid [row][col] with 0/1
  void draw(byte grid[8][8]);

  // animate frames once
  // frames: array of pointers to byte[8][8]
  // frameCount: number of frames
  // frameDelay: ms between frames
  // restartDelay: ms to wait after animation returns (useful before print)
  // finalPause: ms to hold final frame (0 = none)
  void animate(byte* frames[], uint8_t frameCount, uint16_t frameDelay,
               uint16_t restartDelay = 0, uint16_t finalPause = 0);

  // print text (non-scrolling): shows each glyph centered, returns when done
  // supports named tokens in square brackets like [heart], [star], [smiley], [sect], [cake], [party], [confetti]
  void print(const char* text, uint16_t letterDelay = 500, uint16_t endDelay = 1000);

  // smooth leftward scrolling (pixel-by-pixel). speed = ms per column step
  // supports the same tokens as print()
  void scrollText(const char* text, uint16_t speed = 75);

  // confetti: random dots until durationMs elapses. speed = ms between frames
  void confetti(unsigned long durationMs, uint16_t speed = 120);

  // firework: spawn expanding bursts until durationMs elapses
  // spread controls maximum ring radius (1..6)
  void firework(unsigned long durationMs, uint16_t speed = 80, uint8_t spread = 3);

private:
  LedControl &lc;

  // helper: produce glyph columns from text pointer p (consumes one glyph or one token)
  // outCols must be at least 12 bytes long; colsCount returns number of columns produced
  void drawCharToCols(const char* &p, uint8_t* outCols, uint8_t &colsCount);

  // draw an 8-column slice from a columns buffer
  void drawColsSlice(const uint8_t* cols, uint16_t totalCols, int offset);

  // named token -> glyph pointer (5 bytes) or nullptr if none
  const uint8_t* tokenGlyph(const char* token, size_t tokenLen);

  // utility to copy 5-col glyph into outCols with spacer
  void placeGlyphCols(const uint8_t glyph[5], uint8_t* outCols, uint8_t &colsCount);

  // direct mapping tables are inside .cpp
};

#endif
