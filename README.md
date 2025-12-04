EZMatrix Library for MAX7219 8x8 LED Matrix

EZMatrix is an Arduino library for controlling single 8x8 MAX7219 LED matrices, offering smooth text scrolling, animations, confetti and firework effects, and custom 8×8 image drawing.

It’s designed to be simple, with intuitive functions for both letters/numbers and pixel-level control.

Table of Contents

Installation

Setup

EZMatrix Commands

begin()

setBrightness()

clear()

draw()

scrollText()

print()

animate()

confetti()

firework()

Custom Images

Example Usage

Installation

Copy the EZMatrix.h and EZMatrix.cpp files into your Arduino libraries folder:

Documents/Arduino/libraries/EZMatrix/


Make sure you also have the LedControl library
 installed.

Setup

Include the library and create objects for LedControl and EZMatrix:

#include <LedControl.h>
#include "EZMatrix.h"

// Pins: DIN, CLK, CS, number of devices
LedControl lc(12, 11, 10, 1); 
EZMatrix ez(lc);

void setup() {
  ez.begin(8); // Initialize with brightness (0-15)
}

EZMatrix Commands
1. begin(uint8_t intensity)

Initializes the matrix and sets brightness.

intensity: 0 (dim) to 15 (bright).

ez.begin(10);

2. setBrightness(uint8_t intensity)

Adjusts brightness on the fly without reinitializing.

ez.setBrightness(5);

3. clear()

Clears the display immediately.

ez.clear();

4. draw(byte grid[8][8])

Draws a custom 8×8 image. Each element is 0 (off) or 1 (on).

The array is indexed as [row][col] with (0,0) top-left.

Rotation is fixed to 6 o’clock orientation.

byte smiley[8][8] = {
  {0,0,0,0,0,0,0,0},
  {0,1,0,0,0,0,1,0},
  {0,1,0,0,0,0,1,0},
  {0,0,0,0,0,0,0,0},
  {0,0,1,0,0,1,0,0},
  {0,0,0,1,1,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
};

ez.draw(smiley);

5. scrollText(const char* text, uint16_t speed)

Scrolls text pixel by pixel from right to left.

text: letters and numbers (A-Z, 0-9). Symbols like [heart] are optional.

speed: delay in milliseconds between frames (smaller = faster).

ez.scrollText("HELLO 123", 100);

6. print(const char* text, uint16_t letterDelay, uint16_t endDelay)

Prints letters one by one, centered on the 8x8 matrix.

letterDelay: time each letter is displayed (ms)

endDelay: pause after entire message

ez.print("HI", 400, 1000);

7. animate(byte* frames[], uint8_t frameCount, uint16_t frameDelay, uint16_t restartDelay, uint16_t finalPause)

Plays a series of 8x8 frames once.

frames: array of 8×8 byte arrays

frameCount: number of frames

frameDelay: delay between frames (ms)

restartDelay: pause before restarting (ms)

finalPause: pause after animation finishes (ms)

byte frame1[8][8] = { /* ... */ };
byte frame2[8][8] = { /* ... */ };
byte* anim[] = { (byte*)frame1, (byte*)frame2 };
ez.animate(anim, 2, 200, 500, 1000);

8. confetti(unsigned long durationMs, uint16_t speed)

Displays random blinking dots like confetti.

durationMs: total duration in milliseconds

speed: frame delay (ms)

ez.confetti(2000, 100); // 2 seconds of confetti

9. firework(unsigned long durationMs, uint16_t speed, uint8_t spread)

Creates expanding burst effects at random locations.

durationMs: total duration (ms)

speed: delay between burst frames (ms)

spread: radius of explosion (1–6)

ez.firework(3000, 70, 3); // 3 seconds, moderate spread

Custom Images

You can create your own 8×8 bitmaps using 0 for off and 1 for on:

byte heart[8][8] = {
  {0,1,0,0,0,0,1,0},
  {1,1,1,0,0,1,1,1},
  {1,1,1,1,1,1,1,1},
  {0,1,1,1,1,1,1,0},
  {0,0,1,1,1,1,0,0},
  {0,0,0,1,1,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
};

ez.draw(heart);

Example Sketch
#include <LedControl.h>
#include "EZMatrix.h"

LedControl lc(12,11,10,1);
EZMatrix ez(lc);

byte smile[8][8] = {
  {0,0,0,0,0,0,0,0},
  {0,1,0,0,0,0,1,0},
  {0,1,0,0,0,0,1,0},
  {0,0,0,0,0,0,0,0},
  {0,0,1,0,0,1,0,0},
  {0,0,0,1,1,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
};

void setup() {
  ez.begin(8);
}

void loop() {
  ez.draw(smile);            // custom image
  delay(1000);

  ez.confetti(2000, 100);    // confetti effect
  ez.scrollText("HELLO 123", 120); // smooth scrolling
  ez.firework(3000, 70, 3);  // fireworks
  ez.print("DONE", 400, 1000); // print letters one by one
  delay(2000);
}
