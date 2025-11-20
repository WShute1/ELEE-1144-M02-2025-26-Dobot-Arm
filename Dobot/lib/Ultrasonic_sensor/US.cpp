//#define F_CPU 16000000UL   // 16 MHz
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "triggerAction.h"   // include our external header
#include "US.h"            // include our ultrasonic sensor header
  

//uart_init(9600); // Initialise serial monitor at 115200 baud

int Detect(){ // Infinite loop
    // Send ultrasonic pulse
    triggerAction_init(); // Initialize LED pin (defined in triggerAction.h)

    DDRD |= (1 << TRIG_PIN);   // TRIG = output
    DDRD &= ~(1 << ECHO_PIN);  // ECHO = input

    PORTD &= ~(1 << TRIG_PIN); // Turn Trig pin off
    _delay_us(2); // Wait 2 uS
    PORTD |= (1 << TRIG_PIN); // Turn Trig pin on (Start pulse)
    _delay_us(10); // Wait 10 uS (Pulse width)
    PORTD &= ~(1 << TRIG_PIN); // Turn Trig pin off (End pulse)

    // Measure echo pulse
    float duration = (float)pulseIn(ECHO_PIN, 1); // Measure how long echo pin stays high
    float distance = (duration * 0.0343f) / 2.0f; // Distance = duration of pulse * 
    // Speed of sound (cm/uS), divide by 2 for travel to and from times.

    // If distance < 5 cm, turn LED ON via triggerAction
    if (distance > 0 && distance < 2.0f) { // If distance greater than 0 and less than 4 cm...
        triggerAction(1);   // Turn LED ON
        return true;
    } else { // In any other condition
        triggerAction(0);   // Turn LED OFF
        return false;
    }

    // Print distance
    //uart_print("Distance: "); // Print over serail monitor
    //uart_print_float(distance); // Followed by distance value
    //uart_print(" cm\r\n"); // Followed by cm and line break

    // _delay_ms(100); // Delay 100ms
    return 1;
} 


// --- UART setup ---
void uart_init(unsigned int baud) { // Initialises hardware UART
    unsigned int ubrr = F_CPU / 16 / baud - 1; // Sets baud rate
    UBRR0H = (unsigned char)(ubrr >> 8); // Sets baud rate
    UBRR0L = (unsigned char)ubrr; // Sets baud rate
    UCSR0B = (1 << TXEN0); // Enable transmit
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Sets 8-bit data frame
}

void uart_transmit(char data) {
    while (!(UCSR0A & (1 << UDRE0))); // Wait until transmit buffer is empty
    UDR0 = data; // Send byte
}

void uart_print(const char *str) {
    while (*str) uart_transmit(*str++); // Transmit a string, character by character
}

void uart_print_float(float value) { // Converts float to string with 2 decimal places
    char buffer[16];
    dtostrf(value, 6, 2, buffer);
    uart_print(buffer);
}

// --- pulseIn equivalent ---
unsigned long pulseIn(uint8_t pin, uint8_t state) {
    unsigned long width = 0; // Set width to 0

    while (((PIND >> pin) & 1) == state); // Wait for previous pulse to end
    while (((PIND >> pin) & 1) != state); // Wait for pulse to start
    while (((PIND >> pin) & 1) == state) { // Count duration of pulse
        width++; // Add 1 to width
        _delay_us(1); // delay 1 uS
        if (width > 100000UL) break; // timeout if width is over 100ms
    }

    return width; // Return pulse width in mS
}