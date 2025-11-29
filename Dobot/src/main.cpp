// Reference to the libraries the program requires to function.
// including the project libraries, arduino library and std c libraries
#include <Dobot.h>
#include <string.h>
#include <Button.h>
#include <Frame_h.h>
#include <util/delay.h>
#include <stdlib.h>
#include <US.h>
#include <coordinates.h>
#include <RGB.h>
#include <Arduino.h>


Dobot myDobot; //Create an object of the class Dobot and name it myDobot

/*Define the a enum variable type with 9 different keywords, each 
  will be used to determine the state of the finite state machine used
  in the main control loop of the code*/
enum States { INITIALISE, READY, IDENTIFY_BLOCK_COLOUR, MOVE_TO_RED,
              MOVE_TO_GREEN, MOVE_TO_BLUE, RETRIEVE_RED_BLOCK,
              RETRIEVE_GREEN_BLOCK, RETRIEVE_BLUE_BLOCK 
            };
States state = INITIALISE; //create a variable of the States datatype


/*This function is called when the ardunio resets or at initial power on
  It calls a few functions designed to start the dobot in a known state,
  initate the sensor modules and inform the user of this process*/
void setup() {
  myDobot.begin(); //start the uart and software serial modules at 115200 baud
  button_init(); //configure the pins connected to the buttons as inputs
  ColourSensor_Init(); //set pins on the uno as inputs and outputs for the RGB sensor
  homing(); //send a command to the dobot to start the homing function.
  Serial.print("Homing started...\r\n"); //Inform the user that homing has begun
  _delay_ms(10000); //delay the program by 10 seconds to allow the homing to complete
  Serial.print("wait 10 sec...\r\n");
  setEndEffectorSuctionCmd(1,0); //turn the vacuum pump off, just in case it was on
}

/*Main program loop, the finite state machine for the program exists within
  this loop. It controls the flow of the program reacting to sensor and
  user input*/
void loop() {
  static int redCount = 0;//declare three counts to track blocks in storage
  static int greenCount = 0; //storage is assumed to be empty initially.
  static int blueCount = 0;

  int mode = 1; // MOVJ_XYZ mode
  int object; //create a variable to store the detection of a block
  int colour; //create a variable to store the colour of a block

  switch (state) {
    case INITIALISE: // Initialise - state at program start
      state = READY;
      Serial.print("Initialisation complete. System is READY.\r\n");
    break; //shows the user a reset was success and the dobot is ready

    case READY: // Neutral state, waiting for a block or retrieval request
       Serial.print("Ready \r\n");
       _delay_ms(75);
       object = Detect();//check if a block has been detected by the ultrasonic sensor
       if(object == true){//if it has change the state to identify_block_colour
          state = IDENTIFY_BLOCK_COLOUR;
          _delay_ms(50); // Debounce delay
          Serial.print("Object Detected\r\n");//tell the user a block was detected
          break;
        }
        if (button_A3_pressed()){//check to see if a the button retrieve blue was pressed
          state = RETRIEVE_BLUE_BLOCK; //change state if the button was pressed
          _delay_ms(50); // Debounce delay
          Serial.print("Blue Button Pressed\r\n");//tell the user the retrieve blue button
          break;                                  //was pressed.
        }

        if (button_A4_pressed()){//check to see if a the button retrieve green was pressed
          state = RETRIEVE_GREEN_BLOCK;//change state if the button was pressed
          _delay_ms(50); // Debounce delay
          Serial.print("Green Button Pressed\r\n");//tell the user the retrieve green button
          break;                                    //was pressed.
        }

        if (button_A5_pressed()){//check to see if a the button retrieve red was pressed
          state = RETRIEVE_RED_BLOCK;//change state if the button was pressed
          _delay_ms(50); // Debounce delay
          Serial.print("Red Button Pressed\r\n");//tell the user the retrieve red button
          break;                                  //was pressed.
        }
      break;

    case IDENTIFY_BLOCK_COLOUR: // detect block colour
      colour = Detect_colour(); // Call colour detection function

      if (colour == 1){ //check to see if the detected colour was red
        Serial.print("Red Block Detected\r\n");
        state = MOVE_TO_RED; //change to the move_to_red state
      }

      else if (colour == 2){//check to see if the detected colour was green
        Serial.print("Green Block Detected\r\n");
        state = MOVE_TO_GREEN;//change to the move_to_green state
      }

      else if (colour == 3){//check to see if the detected colour was blue
        Serial.print("Blue Block Detected\r\n");
        state = MOVE_TO_BLUE;//change to the move_to_blue state
      }
    break;
    case MOVE_TO_BLUE: // move to blue
        /*use the Storage() to move a block from the loading bay to the blue
          storage area. Add one to the count for blue blocks stored. change
          state to ready. As count increases move z axis of drop off storage
          location higher.
          If the count is greater than or equal to three
          tell user storage is full.
        */
      if (blueCount == 0){//check the blue storage area for existing blocks
        Storage(mode, POINT_blueStorageHigh, POINT_blueStorageSpace1, 2000);
        blueCount++;
        Serial.print("Moving to Blue Storage\r\n");
        state = READY;
        break;
      }

      if (blueCount == 1){//check the blue storage area for existing blocks
        Storage(mode, POINT_blueStorageHigh, POINT_blueStorageSpace2, 2000);
        blueCount++;
        Serial.print("Blue Block Stored\r\n");
        state = READY;
        break;
      }

      if (blueCount == 2){//check the blue storage area for existing blocks
        Storage(mode, POINT_blueStorageHigh, POINT_blueStorageSpace3, 2000);
        blueCount++;
        Serial.print("Blue Block Stored\r\n");
        state = READY;
        break;
      }

      if (blueCount >= 3){//check the blue storage area for existing blocks
        Serial.print("Blue Storage Full\r\n");
        state = READY;
      }

    break;

    case MOVE_TO_GREEN: // move to green
      /*use the Storage() to move a block from the loading bay to the green
        storage area. Add one to the count for green blocks stored. change
        state to ready. As count increases move z axis of drop off storage
        location higher.
        If the count is greater than or equal to three
        tell user storage is full.
      */
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
     
    case MOVE_TO_RED: // move to red
      /*use the Storage() to move a block from the loading bay to the red
        storage area. Add one to the count for red blocks stored. change
        state to ready. As count increases move z axis of drop off storage
        location higher.
        If the count is greater than or equal to three
        tell user storage is full.
      */
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

    case RETRIEVE_BLUE_BLOCK: // retrieve blue block
      /*use the Retrieve() to move a block from the blue storage bay to the
        retrieval area. Subtract one from the count for blue blocks stored. change
        state to ready. As count decreases, move z axis of pick up storage
        location lower.
        If the count is zero, tell user storage is empty.
      */
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

    case RETRIEVE_GREEN_BLOCK: // retrieve green block
      /*use the Retrieve() to move a block from the green storage bay to the
        retrieval area. Subtract one from the count for green blocks stored. change
        state to ready. As count decreases, move z axis of pick up storage
        location lower.
        If the count is zero, tell user storage is empty.
      */
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

    case RETRIEVE_RED_BLOCK: // retrieve red block
      /*use the Retrieve() to move a block from the red storage bay to the
        retrieval area. Subtract one from the count for red blocks stored. change
        state to ready. As count decreases, move z axis of pick up storage
        location lower.
        If the count is zero, tell user storage is empty.
      */
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

    //if state becomes a number greater than 8, the default case will inform the user of a FSM error.
    default: 
      Serial.print("Error: Unknown state\r\n");
      state = READY;
    break;
    }

}
