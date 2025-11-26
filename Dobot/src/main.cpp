#include <Dobot.h>
#include <string.h>
#include <Button.h>
#include <Frame_h.h>
#include <util/delay.h>
#include <stdlib.h>
#include <US.h>
#include <Arduino.h>
#include <Store_Retrieve.h>
#include <avr/io.h>
#include <RGB_sensor.h>

#define mode 1 // MOVJ_XYZ


Dobot myDobot;

struct block_positions{
  unsigned int stacked_red;
  unsigned int stacked_blue;
  unsigned int stacked_green;
}block_counts;

enum STATES{
  INIT,
  LOADING,
  WAITING,
  RETRIEVE
};


volatile enum STATES STATE = INIT;
volatile enum COLOUR detected_colour = OUTOFRANGE;
volatile enum COLOUR colour_To_retrieve = OUTOFRANGE;
volatile int complete = 0;

void setup() {
  myDobot.begin();
  button_init();
}

void loop() {
  // Example: Move arm to position (10, 10, 10) in MOVJ_XYZ mode
  while (1) {
    complete = 0;
    // Check if button A3 is pressed
    if (button_A3_pressed()){
      while(complete != 1){
        switch(STATE){
          case INIT:
          //clear dobot queue  
          homing(); // Perform homing first
          block_counts.stacked_red = 0;
          block_counts.stacked_green = 0;
          block_counts.stacked_blue = 0;
          STATE = WAITING;
          break;
          case LOADING:
            if(Detect() == 1){
              detected_colour = Detect_colour();
              if(block_counts.stacked_red >= 3 || block_counts.stacked_green >= 3 || block_counts.stacked_blue >= 3){
                Serial.println("Requested storage area is full, try again with another block.");
                break;
              }
              switch (detected_colour){
                case RED:
                  red(block_counts.stacked_red, mode);
                  block_counts.stacked_red++;
                  break;
                case BLUE:
                  blue(block_counts.stacked_blue, mode);
                  block_counts.stacked_blue++;
                  break;
                case GREEN:
                  green(block_counts.stacked_green, mode);
                  block_counts.stacked_green++;
                  break;
                case WOODEN:
                  Serial.println("Block is not coloured");
                  break;
                case OUTOFRANGE:
                  Serial.println("Block too far from sensor");
                  Serial.println("Please move block closer to Colour Sensor");
                  break;
              }
              STATE = WAITING;
            }
            break;
          case WAITING:
            if(Detect() == 1){
              STATE = LOADING;
            }
            else{
              if(button_A3_pressed() && button_A4_pressed() && button_A5_pressed()){
                Serial.println("Exiting to main menu");
                complete = 1;
                break;
              }
              if(button_A3_pressed()){
                if(block_counts.stacked_red > 0){
                  colour_To_retrieve = RED;
                  STATE = RETRIEVE;
                }
                else{
                  Serial.println("No more red blocks in storage area.");
                  Serial.println("Please select another colour to retrieve.");
                }
              }
              if(button_A4_pressed()){
                if(block_counts.stacked_green > 0){
                  colour_To_retrieve = GREEN;
                  STATE = RETRIEVE;
                }
                else{
                  Serial.println("No more green blocks in storage area.");
                  Serial.println("Please select another colour to retrieve.");
                }
              }
              if(button_A5_pressed()){
                if(block_counts.stacked_blue > 0){
                  colour_To_retrieve = BLUE;
                  STATE = RETRIEVE;
                }
                else{
                  Serial.println("No more blue blocks in storage area.");
                  Serial.println("Please select another colour to retrieve.");
                }
              }
            }
            break;
          case RETRIEVE:
            switch (colour_To_retrieve){
                case RED:
                  retrieve_red(block_counts.stacked_red, mode);
                  block_counts.stacked_red--;
                  break;
                case BLUE:
                  retrieve_blue(block_counts.stacked_blue, mode);
                  block_counts.stacked_blue--;
                  break;
                case GREEN:
                  retrieve_green(block_counts.stacked_green, mode);
                  block_counts.stacked_green--;
                  break;
                case WOODEN:
                  Serial.println("Wooden blocks are not stored, can not retrieve.");
                  break;
                case OUTOFRANGE:
                  Serial.println("ERROR - colour_To_retrieve remained or was set to its default value.");
                  break;
            }
            STATE = WAITING;
            break;
        }
      }
    }
    if (button_A4_pressed()){
      int block =  Detect(); // Call Detect function
      _delay_ms(500); // Debounce delay
      setEndEffectorSuctionCmd(0 , 0); // Disable suction on suction cup
      char buf[12];
      itoa(block, buf, 10);
      uart_print(buf); // Print detected block value over UART
    }
    if (button_A5_pressed()){
      //setEndEffectorSuctionCmd(1 , 0); // Enable suction on suction cup
       myDobot.printPose();
      _delay_ms(500); // Debounce delay
    }
  }
}

