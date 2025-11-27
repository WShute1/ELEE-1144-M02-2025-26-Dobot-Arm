#ifndef BUTTON_H
#define BUTTON_H

#include <avr/io.h>

void button_init();
uint8_t button_pressed(uint8_t pin);
uint8_t button_A3_pressed();
uint8_t button_A4_pressed();
uint8_t button_A5_pressed();

#endif