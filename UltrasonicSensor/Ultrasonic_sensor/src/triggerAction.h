#ifndef TRIGGER_ACTION_H // Header Guard
#define TRIGGER_ACTION_H // Header Guard

#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN PD4   // LED connected to digital pin 4

// Initialize the LED pin
static inline void triggerAction_init(void) {
    DDRD |= (1 << LED_PIN);  // Set pin as OUTPUT
}

// Control the LED based on the signal
// state = 1 → turn LED ON
// state = 0 → turn LED OFF
static inline void triggerAction(uint8_t state) {
    if (state) {
        PORTD |= (1 << LED_PIN);   // Turn LED ON
    } else {
        PORTD &= ~(1 << LED_PIN);  // Turn LED OFF
    }
}

#endif