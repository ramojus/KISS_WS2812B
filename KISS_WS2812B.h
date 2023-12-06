#ifndef KISS_WS2812B_H
#define KISS_WS2812B_H

#include "Arduino.h"

typedef uint8_t byte;

class KISS_WS2812B {
    public:
        struct Color {
            byte r, g, b;
        };

        KISS_WS2812B(byte pin, unsigned int num_leds);
        void send_colors(Color colors[]);

    private:
        byte port_id;
        byte pin_mask;
        unsigned int num_leds;
        Color *colors;
        void send_byte(byte byte);
        void send_one(volatile byte &port);
        void send_zero(volatile byte &port);
};

#endif // KISS_WS2812B_H
