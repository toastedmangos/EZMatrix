#include "EZMatrix.h"

// ---------------------------
// Constructor
// ---------------------------
EZMatrix::EZMatrix(LedControl &controller) : lc(controller) {}

// ---------------------------
// Initialization
// ---------------------------
void EZMatrix::begin(uint8_t intensity) {
  lc.shutdown(0, false);
  setBrightness(intensity);
  lc.clearDisplay(0);
}

void EZMatrix::setBrightness(uint8_t intensity) {
  if (intensity > 15) intensity = 15;
  lc.setIntensity(0, intensity);
}

void EZMatrix::clear() {
  lc.clearDisplay(0);
}

// ---------------------------
// Draw (8x8 grid, rotation to 6 o'clock)
// Input: grid[row][col], row=0 top, col=0 left
// We rotate so pattern faces 6 o'clock (as requested)
// ---------------------------
void EZMatrix::draw(byte grid[8][8]) {
  for (int r = 0; r < 8; ++r) {
    uint8_t rowByte = 0;
    for (int c = 0; c < 8; ++c) {
      rowByte |= (grid[7 - c][r] << (7 - c));
    }
    lc.setRow(0, r, rowByte);
  }
}

// ---------------------------
// Glyph tables (complete)
// LSB = top row bit0
// Each glyph is 5 columns (5 bytes). We'll add a spacer column after each glyph when composing.
// ---------------------------

// Letters A-Z (5x7)
static const uint8_t GL_AZ[26][5] = {
  {0x7E,0x09,0x09,0x09,0x7E}, // A
  {0x7F,0x49,0x49,0x49,0x36}, // B
  {0x3E,0x41,0x41,0x41,0x22}, // C
  {0x7F,0x41,0x41,0x22,0x1C}, // D
  {0x7F,0x49,0x49,0x49,0x41}, // E
  {0x7F,0x09,0x09,0x09,0x01}, // F
  {0x3E,0x41,0x49,0x49,0x7A}, // G
  {0x7F,0x08,0x08,0x08,0x7F}, // H
  {0x00,0x41,0x7F,0x41,0x00}, // I
  {0x20,0x40,0x41,0x3F,0x01}, // J
  {0x7F,0x08,0x14,0x22,0x41}, // K
  {0x7F,0x40,0x40,0x40,0x40}, // L
  {0x7F,0x02,0x04,0x02,0x7F}, // M
  {0x7F,0x04,0x08,0x10,0x7F}, // N
  {0x3E,0x41,0x41,0x41,0x3E}, // O
  {0x7F,0x09,0x09,0x09,0x06}, // P
  {0x3E,0x41,0x51,0x21,0x5E}, // Q
  {0x7F,0x09,0x19,0x29,0x46}, // R
  {0x46,0x49,0x49,0x49,0x31}, // S
  {0x01,0x01,0x7F,0x01,0x01}, // T
  {0x3F,0x40,0x40,0x40,0x3F}, // U
  {0x1F,0x20,0x40,0x20,0x1F}, // V
  {0x3F,0x40,0x38,0x40,0x3F}, // W
  {0x63,0x14,0x08,0x14,0x63}, // X
  {0x07,0x08,0x70,0x08,0x07}, // Y
  {0x61,0x51,0x49,0x45,0x43}  // Z
};

// Digits 0-9
static const uint8_t GL_09[10][5] = {
  {0x3E,0x45,0x49,0x51,0x3E}, // 0
  {0x00,0x21,0x7F,0x01,0x00}, // 1
  {0x21,0x43,0x45,0x49,0x31}, // 2
  {0x22,0x41,0x49,0x49,0x36}, // 3
  {0x0C,0x14,0x24,0x7F,0x04}, // 4
  {0x72,0x51,0x51,0x51,0x4E}, // 5
  {0x3E,0x49,0x49,0x49,0x26}, // 6
  {0x40,0x47,0x48,0x50,0x60}, // 7
  {0x36,0x49,0x49,0x49,0x36}, // 8
  {0x32,0x49,0x49,0x49,0x3E}  // 9
};

// Symbols and punctuation table
// We'll include a large set. If a requested symbol isn't present, the library falls back to a blank column.
struct Sym { char ch; uint8_t cols[5]; };

// Carefully choose a set that includes your requested symbols.
static const Sym SYMBOLS[] = {
  {'@', {0x3E,0x49,0x55,0x59,0x4E}},
  {'#', {0x14,0x7F,0x14,0x7F,0x14}},
  {'$', {0x24,0x7E,0x25,0x12,0x00}},
  {'%', {0x62,0x64,0x08,0x13,0x0B}},
  {'^', {0x04,0x02,0x01,0x02,0x04}},
  {'&', {0x36,0x49,0x55,0x22,0x50}},
  {'*', {0x14,0x08,0x3E,0x08,0x14}},
  {'(', {0x00,0x1C,0x22,0x41,0x00}},
  {')', {0x00,0x41,0x22,0x1C,0x00}},
  {'-', {0x00,0x08,0x08,0x08,0x00}},
  {'_', {0x00,0x00,0x00,0x00,0x7F}},
  {'=', {0x14,0x14,0x14,0x14,0x14}},
  {'+', {0x08,0x08,0x3E,0x08,0x08}},
  {'.', {0x00,0x00,0x60,0x60,0x00}},
  {'!', {0x00,0x00,0x6F,0x00,0x00}},
  {'?', {0x20,0x40,0x44,0x48,0x30}},
  {':', {0x00,0x18,0x18,0x00,0x00}},
  {',', {0x00,0x40,0x20,0x00,0x00}},
  {'\'',{0x00,0x00,0x0E,0x00,0x00}},
  {'"', {0x00,0x03,0x00,0x03,0x00}},
  {'/', {0x40,0x20,0x10,0x08,0x04}},
  {'\\',{0x04,0x08,0x10,0x20,0x40}},
  {'[', {0x00,0x7F,0x41,0x41,0x00}},
  {']', {0x00,0x41,0x41,0x7F,0x00}},
  {'<', {0x41,0x22,0x14,0x08,0x00}},
  {'>', {0x00,0x08,0x14,0x22,0x41}},
  {'~', {0x02,0x01,0x02,0x04,0x02}},
  {'`', {0x00,0x02,0x04,0x00,0x00}},
  {'|', {0x00,0x00,0x7F,0x00,0x00}},
  {';', {0x00,0x40,0x30,0x00,0x00}}
};

// Named special glyphs (5 columns each)
static const uint8_t GL_HEART[5]  = {0x0A,0x1F,0x3E,0x7C,0x38};
static const uint8_t GL_SMILE[5]  = {0x3C,0x42,0xA5,0x81,0x42};
static const uint8_t GL_STAR[5]   = {0x14,0x08,0x3E,0x08,0x14};
static const uint8_t GL_SECT[5]   = {0x1E,0x21,0x1E,0x21,0x1E};
static const uint8_t GL_CAKE[5]   = {0x0E,0x15,0x15,0x0E,0x00}; // tiny cake
static const uint8_t GL_PARTY[5]  = {0x1B,0x1F,0x1B,0x1F,0x1B}; // party sparkle
static const uint8_t GL_CONFETTI[5] = {0x24,0x00,0x18,0x00,0x24}; // small motif

// token lookup
const uint8_t* EZMatrix::tokenGlyph(const char* token, size_t tokenLen) {
  // compare literal tokens (case-insensitive)
  // common tokens:
  if (tokenLen == 4 && (strncasecmp(token,"star",4) == 0)) return GL_STAR;
  if (tokenLen == 5 && (strncasecmp(token,"heart",5) == 0)) return GL_HEART;
  if ((tokenLen == 6 && strncasecmp(token,"smiley",6) == 0) || (tokenLen == 5 && strncasecmp(token,"smile",5) == 0)) return GL_SMILE;
  if (tokenLen == 4 && (strncasecmp(token,"sect",4) == 0)) return GL_SECT;
  if (tokenLen == 4 && (strncasecmp(token,"cake",4) == 0)) return GL_CAKE;
  if (tokenLen == 5 && (strncasecmp(token,"party",5) == 0)) return GL_PARTY;
  if (tokenLen == 8 && (strncasecmp(token,"confetti",8) == 0)) return GL_CONFETTI;
  return nullptr;
}

// ---------------------------
// Helper: copy 5-col glyph into out and add spacer
// outCols must have space for at least 6 bytes
// ---------------------------
void EZMatrix::placeGlyphCols(const uint8_t glyph[5], uint8_t* outCols, uint8_t &colsCount) {
  for (uint8_t i=0;i<5;i++) outCols[i] = glyph[i];
  outCols[5] = 0x00;
  colsCount = 6;
}

// ---------------------------
// Parse next glyph/token from pointer p
// Writes column bytes into outCols and sets colsCount
// Advances p past consumed characters/token
// ---------------------------
void EZMatrix::drawCharToCols(const char* &p, uint8_t* outCols, uint8_t &colsCount) {
  colsCount = 0;
  if (!p || *p == '\0') { outCols[0]=0x00; colsCount=1; return; }

  // handle named token [token]
  if (*p == '[') {
    // find closing ]
    const char* s = p + 1;
    size_t len = 0;
    while (*s && *s != ']' && len < 32) { ++s; ++len; }
    if (*s == ']') {
      // token text located at p+1, length len
      const char* tokStart = p+1;
      const size_t tokLen = len;
      const uint8_t* tg = tokenGlyph(tokStart, tokLen);
      p = s + 1; // advance p past token
      if (tg) {
        placeGlyphCols((const uint8_t*)tg, outCols, colsCount);
        return;
      } else {
        // unknown token -> produce blank column
        outCols[0]=0x00; colsCount=1; return;
      }
    }
    // if no closing ']', treat '[' as literal
  }

  // normal single char
  char c = *p++;
  // map lowercase to uppercase letters
  if (c >= 'a' && c <= 'z') c = c - 'a' + 'A';

  if (c >= 'A' && c <= 'Z') {
    uint8_t idx = c - 'A';
    placeGlyphCols(GL_AZ[idx], outCols, colsCount);
    return;
  }

  if (c >= '0' && c <= '9') {
    uint8_t d = c - '0';
    placeGlyphCols(GL_09[d], outCols, colsCount);
    return;
  }

  // search SYMBOLS
  for (size_t i=0;i<sizeof(SYMBOLS)/sizeof(SYMBOLS[0]); ++i) {
    if (SYMBOLS[i].ch == c) {
      placeGlyphCols(SYMBOLS[i].cols, outCols, colsCount);
      return;
    }
  }

  // convenience single-char aliases
  if (c == '<') { placeGlyphCols(GL_HEART, outCols, colsCount); return; } // '<' -> heart
  if (c == ':') { placeGlyphCols(GL_SMILE, outCols, colsCount); return; } // ':' -> smiley
  if (c == '*') { placeGlyphCols(GL_STAR, outCols, colsCount); return; }  // '*' -> star

  // unknown => blank column
  outCols[0] = 0x00; colsCount = 1;
}

// ---------------------------
// draw an 8-column window from a columns buffer
// cols: array of bytes (LSB top). totalCols length.
// offset: which column index maps to left-most column of the 8x8
// offset can be negative
// ---------------------------
void EZMatrix::drawColsSlice(const uint8_t* cols, uint16_t totalCols, int offset) {
  byte grid[8][8];
  memset(grid,0,sizeof(grid));
  for (int x = 0; x < 8; ++x) {
    int src = x + offset;
    uint8_t col = 0;
    if (src >= 0 && src < (int)totalCols) col = cols[src];
    for (int row = 0; row < 8; ++row) {
      grid[row][x] = (col >> row) & 0x01;
    }
  }
  draw(grid);
}

// ---------------------------
// scrollText: build columns streaming and scroll left (pixel-by-pixel)
// ---------------------------
void EZMatrix::scrollText(const char* text, uint16_t speed) {
  if (!text) return;

  // dynamic buffer with realloc (keeps memory usage reasonable)
  size_t cap = 64;
  uint8_t* cols = (uint8_t*)malloc(cap);
  if (!cols) return;
  size_t total = 0;

  const char* p = text;
  while (*p) {
    uint8_t tmp[12];
    uint8_t w = 0;
    drawCharToCols(p, tmp, w);
    // ensure capacity
    while (total + w >= cap) {
      size_t ncap = cap * 2;
      uint8_t* n = (uint8_t*)realloc(cols, ncap);
      if (!n) { free(cols); return; }
      cols = n; cap = ncap;
    }
    for (uint8_t i=0;i<w;i++) cols[total++] = tmp[i];
  }

  // add trailing blank columns to scroll out
  for (int i=0;i<8;i++) {
    if (total + 1 >= cap) {
      size_t ncap = cap * 2;
      uint8_t* n = (uint8_t*)realloc(cols, ncap);
      if (!n) { free(cols); return; }
      cols = n; cap = ncap;
    }
    cols[total++] = 0x00;
  }

  // scroll across columns
  for (int off = 0; off <= (int)total - 8; ++off) {
    drawColsSlice(cols, total, off);
    delay(speed);
  }
  // final slide-out frames
  for (int extra = 0; extra < 8; ++extra) {
    drawColsSlice(cols, total, (int)total - 8 + extra);
    delay(speed);
  }

  free(cols);
}

// ---------------------------
// print: show each glyph centered one-by-one
// ---------------------------
void EZMatrix::print(const char* text, uint16_t letterDelay, uint16_t endDelay) {
  if (!text) return;
  const char* p = text;
  while (*p) {
    uint8_t cols[12];
    uint8_t w = 0;
    drawCharToCols(p, cols, w);

    // center horizontally
    byte grid[8][8];
    memset(grid,0,sizeof(grid));
    int left = (8 - (int)w) / 2;
    if (left < 0) left = 0;
    for (int x = 0; x < w && x < 8; ++x) {
      uint8_t col = cols[x];
      for (int row = 0; row < 8; ++row) {
        grid[row][left + x] = (col >> row) & 0x01;
      }
    }
    draw(grid);
    delay(letterDelay);
  }
  clear();
  delay(endDelay);
}

// ---------------------------
// animate: play frames once and return
// ---------------------------
void EZMatrix::animate(byte* frames[], uint8_t frameCount, uint16_t frameDelay,
                       uint16_t restartDelay, uint16_t finalPause) {
  if (!frames || frameCount == 0) return;
  for (uint8_t i=0;i<frameCount;++i) {
    draw((byte(*)[8])frames[i]);
    delay(frameDelay);
  }
  if (finalPause) delay(finalPause);
  if (restartDelay) delay(restartDelay);
}

// ---------------------------
// confetti: random dots for duration
// ---------------------------
void EZMatrix::confetti(unsigned long durationMs, uint16_t speed) {
  unsigned long end = millis() + durationMs;
  while (millis() < end) {
    byte grid[8][8];
    memset(grid,0,sizeof(grid));
    // draw ~10-20 random pixels each frame
    int dots = random(8,18);
    for (int i=0;i<dots;i++) {
      int x = random(0,8), y = random(0,8);
      grid[y][x] = 1;
    }
    draw(grid);
    delay(speed);
  }
  clear();
}

// ---------------------------
// firework: expanding bursts until duration ends
// spread: 1..6
// ---------------------------
void EZMatrix::firework(unsigned long durationMs, uint16_t speed, uint8_t spread) {
  if (spread < 1) spread = 1;
  if (spread > 6) spread = 6;
  unsigned long end = millis() + durationMs;
  while (millis() < end) {
    int cx = random(1,6); // pick center not on edges
    int cy = random(1,6);

    // small flash
    byte core[8][8];
    memset(core,0,sizeof(core));
    core[cy][cx] = 1;
    draw(core);
    delay(speed);

    // expand rings
    for (int r = 1; r <= (int)spread; ++r) {
      byte grid[8][8];
      memset(grid,0,sizeof(grid));
      for (int dx = -r; dx <= r; ++dx) {
        for (int dy = -r; dy <= r; ++dy) {
          // draw ring: either abs(dx)==r or abs(dy)==r
          if (abs(dx) == r || abs(dy) == r) {
            int x = cx + dx;
            int y = cy + dy;
            if (x >= 0 && x < 8 && y >=0 && y < 8) grid[y][x] = 1;
          }
        }
      }
      draw(grid);
      delay(speed);
    }
    delay(speed * 2); // pause between fireworks
  }
  clear();
}
