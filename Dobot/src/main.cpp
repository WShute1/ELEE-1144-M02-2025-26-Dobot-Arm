#include <Dobot.h>
#include <string.h>
#include <Button.h>
#include <Frame_h.h>
#include <util/delay.h>
#include <stdlib.h>
#include <US.h>
#include <coordinates.h>
#include <RGB.h>
#include<Arduino.h>


Dobot myDobot;

enum States { INITIALISE, READY, IDENTIFY_BLOCK_COLOUR, MOVE_TO_RED, MOVE_TO_GREEN, MOVE_TO_BLUE, RETRIEVE_RED_BLOCK, RETRIEVE_GREEN_BLOCK, RETRIEVE_BLUE_BLOCK };
States state = INITIALISE;



void setup() {
  myDobot.begin();
  button_init();
  ColourSensor_Init();
  homing();
  Serial.print("Homing started...\r\n");
  _delay_ms(10000);
  Serial.print("wait 10 sec...\r\n");
  setEndEffectorSuctionCmd(1,0);

}

void loop() {
  static int redCount = 0;
  static int greenCount = 0;
  static int blueCount = 0;

  int mode = 1; // MOVJ_XYZ mode
  int object;
  int colour;

  switch (state) {
    case INITIALISE: // Initialise
      //setup();
      state = READY;
      Serial.print("Initialisation complete. System is READY.\r\n");
    break;

    case READY: // detect block
       object = Detect(); // Call Detect function
       if(object == true){
          state = IDENTIFY_BLOCK_COLOUR;
          _delay_ms(50); 
          Serial.print("Object Detected\r\n");
          break;
        }
        if (button_A3_pressed()){
          state = RETRIEVE_BLUE_BLOCK; 
          _delay_ms(50); // Debounce delay
          Serial.print("Blue Button Pressed\r\n");
          break;
        }

        if (button_A4_pressed()){
          state = RETRIEVE_GREEN_BLOCK;
          _delay_ms(50); // Debounce delay
          Serial.print("Green Button Pressed\r\n");
          break;
        }

        if (button_A5_pressed()){
          state = RETRIEVE_RED_BLOCK;
          _delay_ms(50); // Debounce delay
          Serial.print("Red Button Pressed\r\n");
          break;
        }
      break;

    case IDENTIFY_BLOCK_COLOUR: // detect block colour
      colour = Detect_colour(); // Call colour detection function

      if (colour == 5){
        Serial.print("Red Block Detected\r\n");
        state = MOVE_TO_RED;
      }

      else if (colour == 2){
        Serial.print("Green Block Detected\r\n");
        state = MOVE_TO_GREEN;
      }

      else if (colour == 3){
        Serial.print("Blue Block Detected\r\n");
        state = MOVE_TO_BLUE;
      }
    break;
    case MOVE_TO_BLUE: // move to red
      if (blueCount == 0){
        Storage(mode, POINT_blueStorageHigh, POINT_blueStorageSpace1, 2000);
        blueCount++;
        Serial.print("Moving to Blue Storage\r\n");
        state = READY;
        break;
      }

      if (blueCount == 1){
        Storage(mode, POINT_blueStorageHigh, POINT_blueStorageSpace2, 2000);
        blueCount++;
        Serial.print("Blue Block Stored\r\n");
        state = READY;
        break;
      }

      if (blueCount == 2){
        Storage(mode, POINT_blueStorageHigh, POINT_blueStorageSpace3, 2000);
        blueCount++;
        Serial.print("Blue Block Stored\r\n");
        state = READY;
        break;
      }

      if (blueCount >= 3){
        Serial.print("Blue Storage Full\r\n");
        state = READY;
      }

    break;

    case MOVE_TO_GREEN: // move to green
      if (greenCount == 0){
        Storage(mode, POINT_greenStorageHigh, POINT_greenStorageSpace1, 2000);
        greenCount++;
        Serial.print("Moving to Green Storage\r\n");
        state = READY;
        break;
      }

      if (greenCount == 1){
        Storage(mode, POINT_greenStorageHigh, POINT_greenStorageSpace2, 2000);
        greenCount++;
        Serial.print("Green Block Stored\r\n");
        state = READY;
        break;
      }

      if (greenCount == 2){
        Storage(mode, POINT_greenStorageHigh, POINT_greenStorageSpace3, 2000);
        greenCount++;
        Serial.print("Green Block Stored\r\n");
        state = READY;
        break;
      }

      if (greenCount >= 3){
        Serial.print("Green Storage Full\r\n");
        state = READY;
      }  
    break;
     
    case MOVE_TO_RED: // move to blue
      if (redCount == 0){
        Storage(mode, POINT_redStorageHigh, POINT_redStorageSpace1, 2000);
        redCount++;
        Serial.print("Moving to Red Storage\r\n");
        state = READY;
        break;
      } 

      if (redCount == 1){
        Storage(mode, POINT_redStorageHigh, POINT_redStorageSpace2, 2000);
        redCount++;
        Serial.print("Red Block Stored\r\n");
        state = READY;
        break;
      } 

      if (redCount == 2){
        Storage(mode, POINT_redStorageHigh, POINT_redStorageSpace3, 2000);
        redCount++;
        Serial.print("Red Block Stored\r\n");
        state = READY;
        break;
      }

      if (redCount >= 3){
        Serial.print("Red Storage Full\r\n");
        state = READY;
      }

    break;

    case RETRIEVE_BLUE_BLOCK: // retrieve block

      if (blueCount == 3) {
        Retrieve(mode, POINT_blueStorageHigh, POINT_blueStorageSpace3, 2000);
        blueCount = 2;
        Serial.print("Blue Block Retrieved from pos 3\r\n");
        state = READY;
        break;
      }
    
      if (blueCount == 2){
        Retrieve(mode, POINT_blueStorageHigh, POINT_blueStorageSpace2, 2000);
        Serial.print("Blue Block Retrieved from pos 2\r\n");
        blueCount = 1;
        state = READY;
        break;
      }

      if (blueCount == 1){
        Retrieve(mode, POINT_blueStorageHigh, POINT_blueStorageSpace1, 2000);  
        blueCount = 0;
        Serial.print("Blue Block Retrieved from pos 1\r\n");
        state = READY;
        break;
      }

      if (blueCount == 0){
        Serial.print("No more Blue Blocks to retrieve\r\n");
        state = READY;
      }
  
    break;

    case RETRIEVE_GREEN_BLOCK: // retrieve block
    
      if (greenCount == 3) {
        Retrieve(mode, POINT_greenStorageHigh, POINT_greenStorageSpace3, 2000);
        greenCount = 2;
        Serial.print("Green Block Retrieved from pos 3\r\n");
        state = READY;
        break;
      }

      if (greenCount == 2){
        Retrieve(mode, POINT_greenStorageHigh, POINT_greenStorageSpace2, 2000);
        Serial.print("Green Block Retrieved from pos 2\r\n");
        greenCount = 1;
        state = READY;
        break;
      }

      if (greenCount == 1){
        Retrieve(mode, POINT_greenStorageHigh, POINT_greenStorageSpace1, 2000);  
        greenCount = 0;
        Serial.print("Green Block Retrieved from pos 1\r\n");
        state = READY;
        break;
      }

      if (greenCount == 0){
        Serial.print("No more Green Blocks to retrieve\r\n");
        state = READY;
      }

    break;

    case RETRIEVE_RED_BLOCK: // retrieve block
      if (redCount == 3) {
        Retrieve(mode, POINT_redStorageHigh, POINT_redStorageSpace3, 2000);
        redCount = 2;
        Serial.print("Red Block Retrieved from pos 3\r\n");
        state = READY;
        break;
      }

      if (redCount == 2){
        Retrieve(mode, POINT_redStorageHigh, POINT_redStorageSpace2, 2000);
        Serial.print("Red Block Retrieved from pos 2\r\n");
        redCount = 1;
        state = READY;
        break;
      }

      if (redCount == 1){
        Retrieve(mode, POINT_redStorageHigh, POINT_redStorageSpace1, 2000);  
        redCount = 0;
        Serial.print("Red Block Retrieved from pos 1\r\n");
        state = READY;
        break;
      }

      if (redCount == 0){
        Serial.print("No more Red Blocks to retrieve\r\n");
        state = READY;
      }
      
    break;

    default:
      Serial.print("Error: Unknown state\r\n");
      state = READY;
    break;
    }

}
