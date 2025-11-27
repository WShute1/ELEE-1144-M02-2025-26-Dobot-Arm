#define SAMPLE_COUNT 100  // Number of colour readings taken

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <US.h>

// Enumeration of possible colour classifications returned by Detect_colour()
enum COLOUR {
    spare,                         // Future feature
    RED,                           // Detected red block
    GREEN,                         // Detected green block
    BLUE,                          // Detected blue block
    WOODEN,                        // Detected wooden block
    OUTOFRANGE                     // Unknown colour or too far from sensor
};

// Sensor pin mapping for TCS3200 Colour Sensor:
// s0 = PB0 -> Frequency scaling control
// s1 = PB1 -> Frequency scaling control
// s2 = PB2 -> Photodiode colour filter select (bit 1)
// s3 = PB3 -> Photodiode colour filter select (bit 0)
// OUT = PB4 -> Sensor output: square wave frequency proportional to light intensity

// Macros to easily set/clear control pins on the AVR
#define S0_HIGH (PORTB |= (1<<PB0)) // Set PD0 HIGH
#define S0_LOW  (PORTB &= ~(1<<PB0))// Set PD0 LOW

#define S1_HIGH (PORTB |= (1<<PB1)) // Set PD1 HIGH
#define S1_LOW  (PORTB &= ~(1<<PB1))// Set PD1 LOW

#define S2_HIGH (PORTB |= (1<<PB2)) // Set PB2 HIGH (select colour filter)
#define S2_LOW  (PORTB &= ~(1<<PB2))// Set PB2 LOW

#define S3_HIGH (PORTB |= (1<<PB3)) // Set PB3 HIGH
#define S3_LOW  (PORTB &= ~(1<<PB3))// Set PB3 LOW

#define OUT_PIN (PINB & (1<<PB4))   // Reads the actual HIGH/LOW state of sensor output pin PB4

// Global variables to store measured red, green, blue pulse durations
uint32_t Red, Green, Blue;

// Reads how long the OUT pin stays HIGH from the TCS3200 sensor
uint32_t pulseIn_high(void)
{
    TCNT1 = 0;                        // Reset Timer1 count register to start at 0

    while (OUT_PIN);                  // Wait until the pin goes LOW (ensures we start at a clean cycle)
    while (!OUT_PIN);                 // Wait until the pin goes HIGH (start of the pulse)

    TCNT1 = 0;                        // Reset timer again so pulse length begins here

    while (OUT_PIN) {                 // Count how long the signal stays HIGH
        if (TCNT1 > 60000)            // Prevent timer overflow and freezing if sensor stalls
            return 60000;             // Return maximum allowed measurement
    }

    return TCNT1;                     // Return number of clock cycles the pin stayed HIGH
}

// Reads RGB intensities by switching TCS3200 filter settings
void getColors(void)
{
    // RED filter setting: S2=LOW, S3=LOW
    S2_LOW;                           // Set PB2 = 0 → select red filter
    S3_LOW;                           // Set PB3 = 0
    _delay_ms(10);                    // Allow sensor output to stabilise
    Red = pulseIn_high();             // Measure red light frequency

    // BLUE filter: S2=LOW, S3=HIGH
    S3_HIGH;                          // Set PB3 = 1
    _delay_ms(10);
    Blue = pulseIn_high();            // Measure blue frequency

    // GREEN filter: S2=HIGH, S3=HIGH
    S2_HIGH;                          // Set PB2 = 1
    _delay_ms(10);
    Green = pulseIn_high();           // Measure green frequency
}

// Initializes GPIO pins and Timer1 for sensor measurement
void ColourSensor_Init(void){
    
    // Configure PB0 and PB1 as outputs for S0/S1 (frequency scaling)
    DDRB |= (1 << PB0) | (1 << PB1);

    // Configure PB2 and PB3 as outputs for S2/S3 (colour filter selection)
    DDRB |= (1 << PB2) | (1 << PB3);

    // Configure PB4 as input for OUT pin (SO output from TCS3200)
    DDRB &= ~(1 << PB4);

    // Timer1 configuration:
    TCCR1A = 0;                       // Normal mode (not PWM)
    TCCR1B = (1 << CS10);             // No prescaler → timer ticks at CPU frequency (max precision)

    // Set TCS3200 to 100% output frequency scaling:
    S0_HIGH;                          // S0=1
    S1_HIGH;                          // S1=1 → 100% scaling mode
}

// Main colour detection routine
int Detect_colour()
{
    enum COLOUR colourSamples[SAMPLE_COUNT]; // Stores 50 detected colours before averaging
    uint8_t i;
    uint16_t sum = 0;                          // Accumulates classification values
    uint8_t detectedColourAvg;                 // Final averaged colour classification

    uart_print("Averaging...\n\n");

    // Take SAMPLE_COUNT readings to smooth out noise
    for (i = 0; i < SAMPLE_COUNT; i++)
    {
        getColors();                           // Get the raw RGB pulse durations

        // Threshold-based colour classification:
        // These values come from tuning/experimentation

        if (Red < Blue && Red <= Green && Red < 120) {
            colourSamples[i] = RED;
        }
        else if (Red + Blue + Green <= 232) {
            colourSamples[i] = WOODEN;          // Low RGB sum means brownish/wood colour
        }
        else if (Blue < Green && Blue < Red && Blue < 130) {
            colourSamples[i] = BLUE;
        }
        else if (Green < Red && (Blue - Green) <= 50 && Green < 180) {
            colourSamples[i] = GREEN;
        }
        else {
            colourSamples[i] = OUTOFRANGE;      // No known colour fits thresholds
        }

        _delay_ms(10);                          // Small delay between samples
    }

    // Compute average of all 50 classifications
    sum = 0;
    for (i = 0; i < SAMPLE_COUNT; i++) {
        sum += colourSamples[i];                // Add enum values (0–5)
    }

    detectedColourAvg = sum / SAMPLE_COUNT;     // Integer average becomes final answer

    uart_print("Detected Colour (Avg of 50): \r\n\n");
    uart_print_float(detectedColourAvg);        // Print final colour index
    _delay_ms(500);

    return detectedColourAvg;                   // Return colour classification (0–5)
}