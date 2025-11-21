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
  uart_init(115200); // Initialise serial monitor at 115200 baud
  homing();
  uart_print("Homing started...\r\n");
  _delay_ms(10000);
  uart_print("wait 10 sec...\r\n");
}

int main(void) {
  // Example: Move arm to position (10, 10, 10) in MOVJ_XYZ mode
  int redCount = 0;
  int greenCount = 0;
  int blueCount = 0;
  int mode = 1; // MOVJ_XYZ mode
  int object;
  int colour;

  switch (state) {
    case INITIALISE: // Initialise
      setup();
      state = READY;
      uart_print("Initialisation complete. System is READY.\r\n");
    break;

    case READY: // detect block
      object =  Detect(); // Call Detect function

      if (button_A3_pressed()){
        state = RETRIEVE_BLUE_BLOCK; 
        _delay_ms(50); // Debounce delay
        uart_print("Blue Button Pressed\r\n");
        break;
      }

      if (button_A4_pressed()){
        state = RETRIEVE_GREEN_BLOCK;
        _delay_ms(50); // Debounce delay
        uart_print("Green Button Pressed\r\n");
        break;
      }

      if (button_A5_pressed()){
        state = RETRIEVE_RED_BLOCK;
        _delay_ms(50); // Debounce delay
        uart_print("Red Button Pressed\r\n");
        break;
      }

      if (object == 1){
        state = IDENTIFY_BLOCK_COLOUR;
        uart_print("Object Detected\r\n");
        break;
      }

    case IDENTIFY_BLOCK_COLOUR: // detect block colour
      colour = Detect_colour(); // Call colour detection function

      if (colour == 1){
        uart_print("Red Block Detected\r\n");
        state = MOVE_TO_RED;
      }

      if (colour == 2){
        uart_print("Green Block Detected\r\n");
        state = MOVE_TO_GREEN;
      }

      if (colour == 3){
        uart_print("Blue Block Detected\r\n");
        state = MOVE_TO_BLUE;
      }
     
    break;
    case MOVE_TO_BLUE: // move to red
      if (blueCount == 0){
        Storage(mode, POINT_blueStorageHigh, POINT_blueStorageSpace1, 500);
        blueCount++;
        uart_print("Moving to Blue Storage\r\n");
        state = READY;
        break;
      }

      if (blueCount == 1){
        Storage(mode, POINT_blueStorageHigh, POINT_blueStorageSpace2, 500);
        blueCount++;
        uart_print("Blue Block Stored\r\n");
        state = READY;
        break;
      }

      if (blueCount == 2){
        Storage(mode, POINT_blueStorageHigh, POINT_blueStorageSpace3, 500);
        blueCount++;
        uart_print("Blue Block Stored\r\n");
        state = READY;
        break;
      }

      if (blueCount > 3){
        uart_print("Blue Storage Full\r\n");
        state = READY;
      }

    break;

    case MOVE_TO_GREEN: // move to green
      if (greenCount == 0){
        Storage(mode, POINT_greenStorageHigh, POINT_greenStorageSpace1, 500);
        greenCount++;
        uart_print("Moving to Green Storage\r\n");
        state = READY;
        break;
      }

      if (greenCount == 1){
        Storage(mode, POINT_greenStorageHigh, POINT_greenStorageSpace2, 500);
        greenCount++;
        uart_print("Green Block Stored\r\n");
        state = READY;
        break;
      }

      if (greenCount == 2){
        Storage(mode, POINT_greenStorageHigh, POINT_greenStorageSpace3, 500);
        greenCount++;
        uart_print("Green Block Stored\r\n");
        state = READY;
        break;
      }

      if (greenCount > 3){
        uart_print("Green Storage Full\r\n");
        state = READY;
      }  
    break;
     
    case MOVE_TO_RED: // move to blue
      if (redCount == 0){
        Storage(mode, POINT_redStorageHigh, POINT_redStorageSpace1, 500);
        redCount++;
        uart_print("Moving to Red Storage\r\n");
        state = READY;
        break;
      } 

      if (redCount == 1){
        Storage(mode, POINT_redStorageHigh, POINT_redStorageSpace2, 500);
        redCount++;
        uart_print("Red Block Stored\r\n");
        state = READY;
        break;
      } 

      if (redCount == 2){
        Storage(mode, POINT_redStorageHigh, POINT_redStorageSpace3, 500);
        redCount++;
        uart_print("Red Block Stored\r\n");
        state = READY;
        break;
      }

      if (redCount > 3){
        uart_print("Red Storage Full\r\n");
        state = READY;
      }

    break;

    case RETRIEVE_BLUE_BLOCK: // retrieve block

      if (blueCount == 3) {
        Retrieve(mode, POINT_blueStorageHigh, POINT_blueStorageSpace3, 500);
        blueCount--;
        uart_print("Blue Block Retrieved from pos 3\r\n");
        state = READY;
      }
    
      if (blueCount == 2){
        Retrieve(mode, POINT_blueStorageHigh, POINT_blueStorageSpace2, 500);
        uart_print("Blue Block Retrieved from pos 2\r\n");
        state = READY;
      }

      if (blueCount == 1){
        Retrieve(mode, POINT_blueStorageHigh, POINT_blueStorageSpace1, 500);  
        blueCount--;
        uart_print("Blue Block Retrieved from pos 1\r\n");
        state = READY;
      }

      if (blueCount == 0){
        uart_print("No more Blue Blocks to retrieve\r\n");
        state = READY;
      }
  
    break;

    case RETRIEVE_GREEN_BLOCK: // retrieve block
    
      if (greenCount == 3) {
        Retrieve(mode, POINT_greenStorageHigh, POINT_greenStorageSpace3, 500);
        greenCount--;
        uart_print("Green Block Retrieved from pos 3\r\n");
        state = READY;
      }

      if (greenCount == 2){
        Retrieve(mode, POINT_greenStorageHigh, POINT_greenStorageSpace2, 500);
        uart_print("Green Block Retrieved from pos 2\r\n");
        state = READY;
      }

      if (greenCount == 1){
        Retrieve(mode, POINT_greenStorageHigh, POINT_greenStorageSpace1, 500);  
        greenCount--;
        uart_print("Green Block Retrieved from pos 1\r\n");
        state = READY;
      }

      if (greenCount == 0){
        uart_print("No more Green Blocks to retrieve\r\n");
        state = READY;
      }

    break;

    case RETRIEVE_RED_BLOCK: // retrieve block
      if (redCount == 3) {
        Retrieve(mode, POINT_redStorageHigh, POINT_redStorageSpace3, 500);
        redCount--;
        uart_print("Red Block Retrieved from pos 3\r\n");
        state = READY;
      }

      if (redCount == 2){
        Retrieve(mode, POINT_redStorageHigh, POINT_redStorageSpace2, 500);
        uart_print("Red Block Retrieved from pos 2\r\n");
        state = READY;
      }

      if (redCount == 1){
        Retrieve(mode, POINT_redStorageHigh, POINT_redStorageSpace1, 500);  
        redCount--;
        uart_print("Red Block Retrieved from pos 1\r\n");
        state = READY;
      }

      if (redCount == 0){
        uart_print("No more Red Blocks to retrieve\r\n");
        state = READY;
      }
      
    break;

    default:
      uart_print("Error: Unknown state\r\n");
      state = READY;
    break;
    }

}
