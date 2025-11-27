#include "Button.h"
#include <avr/io.h>

void button_init() {
    // Set analog pins A3 - PC3 A4 - PC4 and A5 - PC5 as inputs
    DDRC &= ~((1 << DDC3) | (1 << DDC4) | (1 << DDC5));
    // Enable internal pull-up resistors for A4 - PC4 and A5 - PC5
    PORTC |= (1 << PC3) | (1 << PC4) | (1 << PC5);
}

// Detect if a button is pressed on the specified pin for the P
// Returns 1 if pressed - LOW, 0 if not pressed - HIGH
uint8_t button_pressed(uint8_t pin) {
    return !(PINC & (1 << pin));
}

// Detect if button on PC3 - A3 is pressed
uint8_t button_A3_pressed() {
    return button_pressed(PC3);
}

// Detect if button on PC4 - A4 is pressed
uint8_t button_A4_pressed() {
    return button_pressed(PC4);
}

// Detect if button on PC5 - A5 is pressed
uint8_t button_A5_pressed() {
    return button_pressed(PC5);
}