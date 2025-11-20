#include <Dobot.h>
#include <string.h>
#include <Button.h>
#include <Frame_h.h>
#include <util/delay.h>
#include <stdlib.h>
#include <US.h>
#include<Arduino.h>
#include <coordinates.h>

Dobot myDobot;

void setup() {
  myDobot.begin();
  button_init();
}
int mode = 1;
  int red(){
   _delay_ms(2000);
      setPTPCmd(mode, POINT_pickUpHigh); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode, POINT_pickUpLow); // Go to pickUp LOW
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 1); //Turn suctionCup ON
        _delay_ms(500);
      
      setPTPCmd(mode, POINT_pickUpHigh); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode, POINT_redStorageHigh); // Go to redStorage HIGH
        _delay_ms(2000);
      setPTPCmd(mode, POINT_redStorageSpace1); // Go to redStorage 'space 1'
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 0); //Turn suctionCup OFF
        _delay_ms(500);
      setPTPCmd(mode, POINT_redStorageHigh); // Go to redStorage HIGH
        _delay_ms(2000);
      
      setPTPCmd(mode, POINT_pickUpHigh); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode, POINT_pickUpLow); // Go to pickUp LOW
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 1); //Turn suctionCup ON
        _delay_ms(500);

      setPTPCmd(mode, POINT_pickUpHigh); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode, POINT_redStorageHigh); // Go to redStorage HIGH
        _delay_ms(2000);
      setPTPCmd(mode, POINT_redStorageSpace2); // Go to redStorage 'Space 2'
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 0); //Turn suctionCup OFF
        _delay_ms(500);
      setPTPCmd(mode, POINT_redStorageHigh); // Go to redStorage HIGH
        _delay_ms(2000);
      
      setPTPCmd(mode, POINT_pickUpHigh); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode, POINT_pickUpLow); // Go to pickUp LOW
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 1); //Turn suctionCup ON
        _delay_ms(500);

      setPTPCmd(mode,  POINT_pickUpHigh); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode, POINT_redStorageHigh); // Go to redStorage HIGH
        _delay_ms(2000);
      setPTPCmd(mode, POINT_redStorageSpace3); // Go to redStorage 'Space 3'
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 0); //Turn suctionCup OFF
        _delay_ms(500);
      setPTPCmd(mode, POINT_redStorageHigh); // Go to redStorage HIGH
        _delay_ms(2000);
  
  }

  int green(){
   _delay_ms(2000);
      setPTPCmd(mode, POINT_pickUpHigh); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode, POINT_pickUpLow); // Go to pickUp LOW
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 1); // Turn suctionCup ON
        _delay_ms(500);
      
      setPTPCmd(mode, POINT_pickUpHigh); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode, POINT_greenStorageHigh); // Go to greenStorage HIGH
        _delay_ms(2000);
      setPTPCmd(mode, POINT_greenStorageSpace1); // Go to greenStorage 'space 1'
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 0); //Turn suctionCup OFF
        _delay_ms(500);
      setPTPCmd(mode, POINT_greenStorageHigh);  // Go to greenStorage HIGH
        _delay_ms(2000);
      
      setPTPCmd(mode, POINT_pickUpHigh); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode, POINT_pickUpLow); // Go to pickUp LOW
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 1); //Turn suctionCup ON
        _delay_ms(500);

      setPTPCmd(mode, POINT_pickUpHigh); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode, POINT_greenStorageHigh);  // Go to greenStorage HIGH
        _delay_ms(2000);
      setPTPCmd(mode, POINT_greenStorageSpace2); // Go to greenStorage 'space 2'
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 0); //Turn suctionCup OFF
        _delay_ms(500);
      setPTPCmd(mode, POINT_greenStorageHigh);  // Go to greenStorage HIGH
        _delay_ms(2000);
      
      setPTPCmd(mode, POINT_pickUpHigh); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode, POINT_pickUpLow); // Go to pickUp LOW
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 1); //Turn suctionCup ON
        _delay_ms(500);

      setPTPCmd(mode, POINT_pickUpHigh); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode, POINT_greenStorageHigh);  // Go to greenStorage HIGH
        _delay_ms(2000);
      setPTPCmd(mode, POINT_greenStorageSpace3); // Go to greenStorage 'space 3'
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 0); //Turn suctionCup OFF
        _delay_ms(500);
      setPTPCmd(mode, POINT_greenStorageHigh);  // Go to greenStorage HIGH
        _delay_ms(2000);
  
  }

  int blue(){
   _delay_ms(2000);
      setPTPCmd(mode, POINT_pickUpHigh); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode, POINT_pickUpLow7); // Go to pickUp LOW
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 1); //Turn suctionCup ON
        _delay_ms(500);
      
      setPTPCmd(mode, POINT_pickUpHigh); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode,  POINT_blueStorageHigh); // Go to blueStorage HIGH
        _delay_ms(2000);
      setPTPCmd(mode, POINT_blueStorageSpace1); // Go to blueStorage 'space 1'
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 0); //Turn suctionCup OFF
        _delay_ms(500);
      setPTPCmd(mode, POINT_blueStorageHigh); // Go to blueStorage HIGH
        _delay_ms(2000);
      
      setPTPCmd(mode, POINT_pickUpHigh); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode, POINT_pickUpLow); // Go to pickUp LOW
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 1); //Turn suctionCup ON
        _delay_ms(500);

      setPTPCmd(mode, POINT_pickUpHigh); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode,  POINT_blueStorageHigh); // Go to blueStorage HIGH
        _delay_ms(2000);
      setPTPCmd(mode, POINT_blueStorageSpace2); // Go to blueStorage 'space 2'
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 0); //Turn suctionCup OFF
        _delay_ms(500);
      setPTPCmd(mode,  POINT_blueStorageHigh); // Go to blueStorage HIGH
        _delay_ms(2000);
      
      setPTPCmd(mode, POINT_pickUpHigh); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode, POINT_pickUpLow); // Go to pickUp LOW
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 1); //Turn suctionCup ON
        _delay_ms(500);

      setPTPCmd(mode, POINT_pickUpHigh); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode,  POINT_blueStorageHigh); // Go to blueStorage HIGH
        _delay_ms(2000);
      setPTPCmd(mode, POINT_blueStorageSpace3); // Go to bluestorage 'Space 3'
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 0); //Turn suctionCup OFF
        _delay_ms(500);
      setPTPCmd(mode,  POINT_blueStorageHigh); // Go to blueStorage HIGH
        _delay_ms(2000);
  }

void loop() {
  // Example: Move arm to position (10, 10, 10) in MOVJ_XYZ mode
 setup();
 int mode = 1; // MOVJ_XYZ
 float x = 111.04; // in mm  
 float y = -233.17; // in mm
 float z = 25.55; // in mm
 float rHead = -64.54; // No rotation

//homing(); // Perform homing first
//_delay_ms(10000);
//setPTPCmd(mode, 201.78, -147.60, 53.77, -36.19);

//_delay_ms(3000); // Wait for homing to complete

// Identifying the block colour
// blockColour=Red?
// if Red, turn move to "pick up position, turn suction cup on and move to redStorage"


//setPTPCmd(mode, x, y, z, rHead); // Move to specified position

  //_delay_ms(5000);

  //setEndEffectorSuctionCmd(1 , 1); // Enable suction on suction cup 
  //_delay_ms(2000);
  //setEndEffectorSuctionCmd(0 , 0); // Disable suction on suction cup 
  while (1) {
    // Check if button A3 is pressed
    if (button_A3_pressed()){
      //red();
      //green();
      blue();
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
