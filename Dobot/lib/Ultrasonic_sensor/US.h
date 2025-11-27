#ifndef US_H
#define US_H

#define TRIG_PIN PD5 // Define Trigger pin as Digital Pin 5
#define ECHO_PIN PD6 // Define Echo pin as Digital Pin 6

void uart_init(unsigned long baud);
void uart_transmit(char data);
void uart_print(const char *str);
void uart_print_float(float value); 
unsigned long pulseIn(uint8_t pin, uint8_t state); // Function declaration
bool Detect(); // Function declaration

#endif