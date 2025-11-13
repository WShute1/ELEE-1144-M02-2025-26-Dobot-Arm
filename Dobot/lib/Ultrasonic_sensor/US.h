#ifndef US_H
#define US_H

#define TRIG_PIN PD2 // Define Trigger pin as Digital Pin 2
#define ECHO_PIN PD3 // Define Echo pin as Digital Pin 2

void uart_init(unsigned int baud);
void uart_transmit(char data);
void uart_print(const char *str);
void uart_print_float(float value); 
unsigned long pulseIn(uint8_t pin, uint8_t state); // Function declaration
int Detect(); // Function declaration

#endif