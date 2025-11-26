#include <RGB_sensor.h>     // <--- ADDED HERE



// ---------------------------------------------------------
// UART FUNCTIONS (9600 baud)
// ---------------------------------------------------------
void uart_init(void) {
    uint16_t ubrr = 103; // 9600 baud @16MHz

    UBRR0H = (uint8_t)(ubrr >> 8);
    UBRR0L = (uint8_t)ubrr;

    UCSR0B = (1 << TXEN0);                 // Enable TX
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);// 8N1
}

void uart_tx(char c) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = c;
}

void uart_print(const char *str) {
    while (*str) uart_tx(*str++);
}

char buffer[64];
void uart_print_num(const char *label, uint32_t num) {
    sprintf(buffer, "%s %lu ", label, num);
    uart_print(buffer);
}

// ---------------------------------------------------------
// pin mapping (ATmega328P physical ports)
// ---------------------------------------------------------
// s0 = PD0
// s1 = PD1
// s2 = PB2
// s3 = PB3
// OUT = PB4

// Write pin macros
#define S0_HIGH (PORTD |= (1<<PD0))
#define S0_LOW  (PORTD &= ~(1<<PD0))

#define S1_HIGH (PORTD |= (1<<PD1))
#define S1_LOW  (PORTD &= ~(1<<PD1))

#define S2_HIGH (PORTB |= (1<<PB2))
#define S2_LOW  (PORTB &= ~(1<<PB2))

#define S3_HIGH (PORTB |= (1<<PB3))
#define S3_LOW  (PORTB &= ~(1<<PB3))

#define OUT_PIN (PINB & (1<<PB4))

// ---------------------------------------------------------
// pulseIn replacement using Timer1
// ---------------------------------------------------------
uint32_t pulseIn_high(void)
{
    TCNT1 = 0;

    while (OUT_PIN);       // wait for LOW
    while (!OUT_PIN);      // wait for HIGH

    TCNT1 = 0;
    while (OUT_PIN)
        if (TCNT1 > 60000) return 60000;

    return TCNT1;
}

// ---------------------------------------------------------
// Read colors
// ---------------------------------------------------------
uint32_t Red, Green, Blue;

void getColors(void)
{
    // RED (S2=0, S3=0)
    S2_LOW;
    S3_LOW;
    _delay_ms(10);
    Red = pulseIn_high();

    // BLUE (S2=0, S3=1)
    S3_HIGH;
    _delay_ms(10);
    Blue = pulseIn_high();

    // GREEN (S2=1, S3=1)
    S2_HIGH;
    _delay_ms(10);
    Green = pulseIn_high();
}

// ---------------------------------------------------------
// MAIN
// ---------------------------------------------------------
COLOUR Detect_colour(void)
{
    enum COLOUR colourSamples[SAMPLE_COUNT];
    uint8_t i;
    uint16_t sum = 0;
    uint8_t detectedColourAvg;

    // Setup pins
    DDRD |= (1 << PD0) | (1 << PD1);
    DDRB |= (1 << PB2) | (1 << PB3);
    DDRB &= ~(1 << PB4);

    // UART
    uart_init();

    // Timer setup
    TCCR1A = 0;
    TCCR1B = (1 << CS10);

    // TCS3200 100% scaling
    S0_HIGH;
    S1_HIGH;

        uart_print("Averaging...\n\n");
        // Take 50 samples
        for (i = 0; i < SAMPLE_COUNT; i++)
        {
            getColors();

            // Print raw sensor values (optional)
           // uart_print_num("R:", Red);
            //uart_print_num("G:", Green);
            //uart_print_num("B:", Blue);
            //uart_print("\r\n");

            // --- Colour detection ---
            if (Red < Blue && Red <= Green && Red < 100 && Green > 200 && Blue > 200) {
                colourSamples[i] = RED;
            }
            else if (Red + Blue + Green <= 232) {
                colourSamples[i] = WOODEN;
            }
            else if (Blue < Green && Blue < Red && Blue < 130) {
                colourSamples[i] = BLUE;
            }
            else if (Green < Red && (Blue - Green) <= 50 && Green < 180) {
                colourSamples[i] = GREEN;
            }
            else {
                colourSamples[i] = OUTOFRANGE;
            }

            _delay_ms(10);
        }

        // ---- Compute the average colour ----
        sum = 0;
        for (i = 0; i < SAMPLE_COUNT; i++) {
            sum += colourSamples[i];
        }

        detectedColourAvg = sum / SAMPLE_COUNT;

        return (COLOUR)detectedColourAvg;
}
