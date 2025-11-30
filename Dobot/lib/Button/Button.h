#ifndef BUTTON_H //Set header guard, only compile the data within the #if statement if the Button.h header has not be defined already by another part of the program.
#define BUTTON_H // has not be defined already by another part of the program.

#include <avr/io.h> /*Include the header file of the avr/io library this will allow the use of the variables PORTC, DDRC and PC5 etc.
                        This increases the readability of the code by removing register names like 0x28 which is PORTC on register map. Page 280 of the 328p datasheet */
                        
//Below are five function declarations, these are defined in the Button.cpp file. They allow the complier to understand the existance of the functions and their inputs and outputs.
void button_init();
uint8_t button_pressed(uint8_t pin);
uint8_t button_A3_pressed();
uint8_t button_A4_pressed();
uint8_t button_A5_pressed();

#endif