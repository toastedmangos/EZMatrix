
```markdown
# EZMatrix Library for MAX7219 8x8 LED Matrix

EZMatrix is an Arduino library for controlling **single 8x8 MAX7219 LED matrices**, offering smooth text scrolling, animations, confetti and firework effects, and custom 8×8 image drawing.

It’s designed to be **simple**, with intuitive functions for both letters/numbers and pixel-level control.

---

## Table of Contents

1. [Installation](#installation)  
2. [Setup](#setup)  
3. [EZMatrix Commands](#ezmatrix-commands)  
4. [Custom Images](#custom-images)  
5. [Example Sketch](#example-sketch)  
6. [8×8 Coordinate Diagram](#8x8-coordinate-diagram)  

---

## Installation

1. Copy the `EZMatrix.h` and `EZMatrix.cpp` files into a folder named `EZMatrix` in your Arduino libraries folder:

```

Documents/Arduino/libraries/EZMatrix/

````

2. Install the [LedControl library](https://github.com/wayoda/LedControl), either via the Library Manager in Arduino IDE or manually.

---

## Setup

Include the library and create objects for LedControl and EZMatrix:

```cpp
#include <LedControl.h>
#include "EZMatrix.h"

// Pins: DIN, CLK, CS, number of devices
LedControl lc(12, 11, 10, 1); 
EZMatrix ez(lc);

void setup() {
  ez.begin(8); // Initialize with brightness 0-15
}
````

---

## EZMatrix Commands

| Command                                                          | Description                                 | Example                            |
| ---------------------------------------------------------------- | ------------------------------------------- | ---------------------------------- |
| `begin(intensity)`                                               | Initialize the display with brightness 0-15 | `ez.begin(8);`                     |
| `setBrightness(intensity)`                                       | Change brightness on the fly                | `ez.setBrightness(5);`             |
| `clear()`                                                        | Clear the display                           | `ez.clear();`                      |
| `draw(byte grid[8][8])`                                          | Draw a custom 8×8 image                     | `ez.draw(smiley);`                 |
| `scrollText(text, speed)`                                        | Scroll text pixel-by-pixel                  | `ez.scrollText("HELLO",100);`      |
| `print(text, letterDelay, endDelay)`                             | Show letters one-by-one, centered           | `ez.print("HI",400,1000);`         |
| `animate(frames[], count, frameDelay, restartDelay, finalPause)` | Play frames once                            | `ez.animate(anim,2,200,500,1000);` |
| `confetti(durationMs, speed)`                                    | Random confetti dots                        | `ez.confetti(2000,100);`           |
| `firework(durationMs, speed, spread)`                            | Expanding bursts                            | `ez.firework(3000,70,3);`          |

---

## Custom 8x8 Images 

If you want a really easy way to craate these patterns by just clicking, visit my other repo with a website in it to make this a million times easier: https://github.com/toastedmangos/EZMatrix-drawer

Design images using `0 = off`, `1 = on`:

```cpp
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
```

---

## Example Sketch

```cpp
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
  ez.confetti(2000, 100);
  ez.scrollText("HAPPY BIRTHDAY", 120);
  ez.firework(3000, 70, 3);
  ez.print("DONE", 400, 1000);
  delay(2000);
}
```

---

## 8×8 Coordinate Diagram (not very important just for the geeks)

```
[0,0] [0,1] [0,2] [0,3] [0,4] [0,5] [0,6] [0,7]
[1,0] [1,1] [1,2] [1,3] [1,4] [1,5] [1,6] [1,7]
[2,0] [2,1] [2,2] [2,3] [2,4] [2,5] [2,6] [2,7]
[3,0] [3,1] [3,2] [3,3] [3,4] [3,5] [3,6] [3,7]
[4,0] [4,1] [4,2] [4,3] [4,4] [4,5] [4,6] [4,7]
[5,0] [5,1] [5,2] [5,3] [5,4] [5,5] [5,6] [5,7]
[6,0] [6,1] [6,2] [6,3] [6,4] [6,5] [6,6] [6,7]
[7,0] [7,1] [7,2] [7,3] [7,4] [7,5] [7,6] [7,7]
```
