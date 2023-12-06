#include "KISS_WS2812B.h"

// Optimize on time, parts of this code are very time sensitive.
#pragma GCC optimize ("-O2")

// To keep the compiler from complaining about undefined ports.
// PORTB should be defined on every avr microcontroller.
#ifndef PORTA
#define PORTA PORTB
#endif
#ifndef PORTC
#define PORTC PORTB
#endif
#ifndef PORTD
#define PORTD PORTB
#endif
#ifndef PORTE
#define PORTE PORTB
#endif
#ifndef PORTF
#define PORTF PORTB
#endif

// macros taken from https://github.com/sonyhome/FAB_LED/blob/master/FAB_LED.h
#define DELAY_CYCLES(count) if (count > 0) __builtin_avr_delay_cycles(count);
#define NS_PER_SEC          1000000000ULL
#define CYCLES_PER_SEC      ((uint64_t) (F_CPU))
#define CYCLES(time_ns)     (((CYCLES_PER_SEC * (time_ns)) + NS_PER_SEC - 1ULL) / NS_PER_SEC)

// timings taken from https://github.com/sonyhome/FAB_LED/blob/master/FAB_LED.h
#define CLEAR_BIT_CYCLES 2
#define SET_BIT_CYCLES 2
#define DELAY_CYCLES_HIGH_1 CYCLES(500)
#define DELAY_CYCLES_LOW_1 CYCLES(125)
#define DELAY_CYCLES_HIGH_0 CYCLES(125)
#define DELAY_CYCLES_LOW_0 CYCLES(188)

inline volatile byte *get_port(byte port_id) {
    byte *ports[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE, &PORTF};
    return ports[port_id - 1];
}

KISS_WS2812B::KISS_WS2812B(byte pin, unsigned int num_leds) {
    num_leds = num_leds;
    pin_mask = digitalPinToBitMask(pin);
    port_id = digitalPinToPort(pin);

    pinMode(pin, OUTPUT);
}

void KISS_WS2812B::send_colors(Color colors[]) {
    noInterrupts();
    for (int i = 0; i < num_leds; ++i) {
        send_byte(colors[i].g);
        send_byte(colors[i].r);
        send_byte(colors[i].b);
    }
    interrupts();
}

void KISS_WS2812B::send_byte(byte byte) {
    for (int i = 7; i >= 0; --i) {
        if (byte & (1 << i)) {
            send_one(*get_port(port_id));
        } else {
            send_zero(*get_port(port_id));
        }
    }
}

void KISS_WS2812B::send_one(volatile byte &port) {
    port |= pin_mask;
    DELAY_CYCLES(DELAY_CYCLES_HIGH_1 - SET_BIT_CYCLES);
    port &= ~pin_mask;
    DELAY_CYCLES(DELAY_CYCLES_LOW_1 - CLEAR_BIT_CYCLES);
}

void KISS_WS2812B::send_zero(volatile byte &port) {
    port |= pin_mask;
    DELAY_CYCLES(DELAY_CYCLES_HIGH_0 - SET_BIT_CYCLES);
    port &= ~pin_mask;
    DELAY_CYCLES(DELAY_CYCLES_LOW_0 - CLEAR_BIT_CYCLES);
}
