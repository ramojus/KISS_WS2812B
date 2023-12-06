# [KISS](https://en.wikipedia.org/wiki/KISS_principle) library for WS2812B
Arduino library for WS2812B – and potentially similar single-wire-based LED pixels – that is:
- Small
- Simple to use
- Easy to read and understand, thus fix and extend

Only tested with Arduino Uno, but should work with other AVR Arduino boards.

## Motivation
There are a lot of Arduino libraries that allow to control single-wire-based LED pixels with Arduino, some of which include:
- [FastLED](https://github.com/FastLED/FastLED)
- [FAB_LED](https://github.com/sonyhome/FAB_LED)
- [light_ws2812](https://github.com/cpldcpu/light_ws2812)
- [Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
- [TinyWS2812B](https://github.com/derAndroidPro/TinyWS2812B) (this one being the most simple and readable I could find)

Most of these libraries, to me, seem a bit overcomplicated and are hard to read. That and a desire to understand Arduino better have led me to create my own library that hopefully doesn't suffer from these issues.
All this said, having the libraries mentioned above as a reference helped me a lot when creating this library.

## Installation
Probably the simplest way is to import the library using Arduino IDE by following [this](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries#importing-a-zip-library) tutorial.

For terminal users:
- Run `arduino-cli config dump` and find user directory.
- Copy `.cpp` and `.h` files from this library to `<user_directory>/libraries/KISS_WS2812B` folder.

## Usage
Start by including the library:
```cpp
#include <KISS_WS2812B.h>
```
Use `KISS_WS2812B` type to control the LED, it consists of:
- Constructor:
    ```cpp
    KISS_WS2812B(byte pin, unsigned int num_leds);
    ```
    The port will be derived from `pin` automatically.
- `Colors` structure:
    ```cpp
    struct Color {
        byte r, g, b;
    };
    ```
    This structure can be used to create a color with where:
    - `r` member stands for the amount of red in the color.
    - `g` member stands for the amount of green in the color.
    - `b` member stands for the amount of blue in the color.

    Any of these members can have values in the range from 0 to 255. The higher the values, the brighter the color, thus `Color {0, 0, 0}` stands for black and is identical to turning the specific LED off.

    More about the RGB color model [here](https://en.wikipedia.org/wiki/RGB_color_model).
- `send_colors` function:
    ```cpp
    void send_colors(Color colors[]);
    ```
    Expects the length of `colors` array to be `num_leds`.

### TLDR
Here is a simple example:
```cpp
#include <KISS_WS2812B.h>

#define NUM_LEDS 64

typedef KISS_WS2812B::Color Color;

KISS_WS2812B leds(4, NUM_LEDS);
Color colors[NUM_LEDS];

void setup() {
}

void loop() {
    for (int pos = 0; pos < NUM_LEDS; ++pos) {
        colors[pos - 1] = Color {0, 0, 0};
        colors[pos] = Color {6, 5, 2};
        leds.send_colors(colors);
        delay(100);
    }
    colors[NUM_LEDS - 1] = Color {0, 0, 0};
    leds.send_colors(colors);
}
```

## Contributing and the future of this project
I will abandon this project as it was made with Arduino that I have borrowed from university and I probably don't have a deep enough passion for Arduino to ever buy one for myself. I do, however, plan to accept PRs if there will ever be any. PRs that follow the existing code style and don't use unnecessary macros should be accepted.

## Licence
[MIT](./LICENSE)

