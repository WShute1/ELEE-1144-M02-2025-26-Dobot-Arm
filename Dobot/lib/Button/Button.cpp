#include "Button.h" //Reference to the Button.h header file. which contains
    // the function declarations and references to any required libraries

/*We have decided that we want to use three buttons, they are connected to 
    digital pin 17, 18 and 19 on the ardunino uno.
    They are part of PORTC, PORTC pins PC3, PC4 and PC5 on the 328p.
    The pins need to be configured as inputs.
    The buttons on our breadboard are configured to pull the pins to
    GND when pressed.
    Therefore, we have used the internal pull ups of PORTC to make the
    input VCC when the button isnt pressed.
    This gives us two distinic states that can be read at the 328p pins.
    */
void button_init() {
    /* Set the digital pins 17,18 and 19 as inputs using the direction
        register DDRC, this requires the bits to be set as "0" without
        editing the other bits in the register.
        Below three values are bit shifted to by their offset within
        the register byte and then OR'ed together to get:
        0b00111000
        This is then inverted to 0b11000111 and then AND'ed to the
        value of DDRC, with the result set to DDRC.
        */
    DDRC &= ~((1 << DDC3) | (1 << DDC4) | (1 << DDC5));

    /* set the internal pull-ups on PORTC to enabled for the pins
    used as button inputs. They need to be set to "1" to be enabled
    Below the statement OR's the three bit shifted values into
    0b00111000 like the setting of the direction register but this time.
    This value is OR'ed with the PORTC value and stored at PORTC register.
    This sets the three pins to "1" without affecting the other pins in
    the PORT.
    */
    PORTC |= (1 << PC3) | (1 << PC4) | (1 << PC5);
}

/* Detect if a button is pressed on the specified pin
    The PINC register, current state of the inputs of PORTC, is AND'ed
    with the pin that we want to check the state of. This results in
    a value greater than 1 if the pin is logic high (VCC) and a value of
    zero if the pin is at logic 0 (GND).
    This is then inverted using the logcial NOT "!" which then 
    Returns 1 if pressed - LOW, 0 if not pressed - HIGH
    */
uint8_t button_pressed(uint8_t pin) {
    return !(PINC & (1 << pin));
}

// Detect if button on PC3 - D17 is pressed
uint8_t button_A3_pressed() {
    return button_pressed(PC3);
}

// Detect if button on PC4 - D18 is pressed
uint8_t button_A4_pressed() {
    return button_pressed(PC4);
}

// Detect if button on PC5 - D19 is pressed
uint8_t button_A5_pressed() {
    return button_pressed(PC5);
}