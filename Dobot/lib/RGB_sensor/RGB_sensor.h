#ifndef RGB_SENSOR_H
#define RGB_SENSOR_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define SAMPLE_COUNT 50  


enum COLOUR {
    RED,
    GREEN,
    BLUE,
    WOODEN,
    OUTOFRANGE
};

void uart_init(void);
void uart_tx(char c);
void uart_print(const char *str);
void uart_print_num(const char *label, uint32_t num);
uint32_t pulseIn_high(void);
void getColors(void);
COLOUR Detect_colour(void);

#endif