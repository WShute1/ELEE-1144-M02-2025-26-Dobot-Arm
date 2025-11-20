#include <Dobot.h>
#include <string.h>
#include <Button.h>
#include <Frame_h.h>
#include <util/delay.h>
#include <stdlib.h>
#include <US.h>
#include<Arduino.h>


Dobot myDobot;

void setup() {
  myDobot.begin();
  button_init();
}
int mode = 1;
  int red(){
   _delay_ms(2000);
      setPTPCmd(mode, 13.63, -294.88, 46.83, -115.56); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode, 19.27, -270, -51.08, -113.97); // Go to pickUp LOW
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 1); //Turn suctionCup ON
        _delay_ms(500);
      
      setPTPCmd(mode,  13.63, -294.88, 46.83, -115.56); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode, 72.60, -259.71, 67.63, -102.58); // Go to redStorage HIGH
        _delay_ms(2000);
      setPTPCmd(mode, 76.73, -228.93, -54.06, -99.67); // Go to redStorage 'space 1'
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 0); //Turn suctionCup OFF
        _delay_ms(500);
      setPTPCmd(mode, 72.60, -259.71, 67.63, -102.58); // Go to redStorage HIGH
        _delay_ms(2000);
      
      setPTPCmd(mode, 13.63, -294.88, 46.83, -115.56); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode, 19.27, -270, -51.08, -113.97); // Go to pickUp LOW
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 1); //Turn suctionCup ON
        _delay_ms(500);

      setPTPCmd(mode,  13.63, -294.88, 46.83, -115.56); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode, 72.60, -259.71, 67.63, -102.58); // Go to redStorage HIGH
        _delay_ms(2000);
      setPTPCmd(mode, 82.73, -228.93, -22.06, -99.67); // Go to redStorage 'Space 2'
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 0); //Turn suctionCup OFF
        _delay_ms(500);
      setPTPCmd(mode, 72.60, -259.71, 67.63, -102.58); // Go to redStorage HIGH
        _delay_ms(2000);
      
      setPTPCmd(mode, 13.63, -294.88, 46.83, -115.56); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode, 19.27, -270, -51.08, -113.97); // Go to pickUp LOW
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 1); //Turn suctionCup ON
        _delay_ms(500);

      setPTPCmd(mode,  13.63, -294.88, 46.83, -115.56); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode, 72.60, -259.71, 67.63, -102.58); // Go to redStorage HIGH
        _delay_ms(2000);
      setPTPCmd(mode, 85.73, -228.93, 10, -99.67); // Go to redStorage 'Space 3'
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 0); //Turn suctionCup OFF
        _delay_ms(500);
      setPTPCmd(mode, 72.60, -259.71, 67.63, -102.58); // Go to redStorage HIGH
        _delay_ms(2000);
  
  }

  int green(){
   _delay_ms(2000);
      setPTPCmd(mode, 13.63, -294.88, 46.83, -115.56); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode, 19.27, -270, -51.08, -113.97); // Go to pickUp LOW
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 1); //Turn suctionCup ON
        _delay_ms(500);
      
      setPTPCmd(mode,  13.63, -294.88, 46.83, -115.56); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode, 130.25, -176.69, 81.42, -81.14); // Go to redStorage HIGH
        _delay_ms(2000);
      setPTPCmd(mode, 130.25, -176.69, -54.12, -81.80); // Go to redStorage 'space 1'
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 0); //Turn suctionCup OFF
        _delay_ms(500);
      setPTPCmd(mode, 130.25, -176.69, 81.42, -81.14);  // Go to redStorage HIGH
        _delay_ms(2000);
      
      setPTPCmd(mode, 13.63, -294.88, 46.83, -115.56); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode, 19.27, -270, -51.08, -113.97); // Go to pickUp LOW
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 1); //Turn suctionCup ON
        _delay_ms(500);

      setPTPCmd(mode,  13.63, -294.88, 46.83, -115.56); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode, 130.25, -176.69, 81.42, -81.14);  // Go to redStorage HIGH
        _delay_ms(2000);
      setPTPCmd(mode, 130.25, -176.69, -22.12, -81.80); // Go to redStorage 'Space 2'
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 0); //Turn suctionCup OFF
        _delay_ms(500);
      setPTPCmd(mode, 130.25, -176.69, 81.42, -81.14);  // Go to redStorage HIGH
        _delay_ms(2000);
      
      setPTPCmd(mode, 13.63, -294.88, 46.83, -115.56); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode, 19.27, -270, -51.08, -113.97); // Go to pickUp LOW
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 1); //Turn suctionCup ON
        _delay_ms(500);

      setPTPCmd(mode,  13.63, -294.88, 46.83, -115.56); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode, 130.25, -176.69, 81.42, -81.14);  // Go to redStorage HIGH
        _delay_ms(2000);
      setPTPCmd(mode, 130.25, -176.69, 10, -81.80); // Go to redStorage 'Space 3'
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 0); //Turn suctionCup OFF
        _delay_ms(500);
      setPTPCmd(mode, 130.25, -176.69, 81.42, -81.14);  // Go to redStorage HIGH
        _delay_ms(2000);
  
  }

  int blue(){
   _delay_ms(2000);
      setPTPCmd(mode, 13.63, -294.88, 46.83, -115.56); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode, 19.27, -270, -51.08, -113.97); // Go to pickUp LOW
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 1); //Turn suctionCup ON
        _delay_ms(500);
      
      setPTPCmd(mode,  13.63, -294.88, 46.83, -115.56); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode,  185.13, -136.87, 65.37, -64.68); // Go to redStorage HIGH
        _delay_ms(2000);
      setPTPCmd(mode, 180.82, -125.47, -53.28, -62.96); // Go to redStorage 'space 1'
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 0); //Turn suctionCup OFF
        _delay_ms(500);
      setPTPCmd(mode,  185.13, -136.87, 65.37, -64.68); // Go to redStorage HIGH
        _delay_ms(2000);
      
      setPTPCmd(mode, 13.63, -294.88, 46.83, -115.56); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode, 19.27, -270, -51.08, -113.97); // Go to pickUp LOW
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 1); //Turn suctionCup ON
        _delay_ms(500);

      setPTPCmd(mode,  13.63, -294.88, 46.83, -115.56); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode,  185.13, -136.87, 65.37, -64.68); // Go to redStorage HIGH
        _delay_ms(2000);
      setPTPCmd(mode, 180.82, -125.47, -22.28, -62.96); // Go to redStorage 'Space 2'
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 0); //Turn suctionCup OFF
        _delay_ms(500);
      setPTPCmd(mode,  185.13, -136.87, 65.37, -64.68); // Go to redStorage HIGH
        _delay_ms(2000);
      
      setPTPCmd(mode, 13.63, -294.88, 46.83, -115.56); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode, 19.27, -270, -51.08, -113.97); // Go to pickUp LOW
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 1); //Turn suctionCup ON
        _delay_ms(500);

      setPTPCmd(mode,  13.63, -294.88, 46.83, -115.56); // Go to pickUp HIGH
        _delay_ms(2000);
      setPTPCmd(mode,  185.13, -136.87, 65.37, -64.68); // Go to redStorage HIGH
        _delay_ms(2000);
      setPTPCmd(mode,  185.13, -136.87, 10.00, -64.68); // Go to redStorage 'Space 3'
        _delay_ms(2000);
      setEndEffectorSuctionCmd(1 , 0); //Turn suctionCup OFF
        _delay_ms(500);
      setPTPCmd(mode,  13.63, -294.88, 46.83, -115.56); // Go to redStorage HIGH
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
      red();
      green();
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
