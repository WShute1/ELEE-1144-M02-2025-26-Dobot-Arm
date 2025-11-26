#include <Store_Retrieve.h>
#include <Frame_h.h>
#include <util/delay.h>

void green(unsigned int space, int mode){
  _delay_ms(2000);
  setPTPCmd(mode, 13.63, -294.88, 46.83, 0); // Go to pickUp HIGH
  _delay_ms(2000);
  setPTPCmd(mode, 19.27, -270, -51.08, 0); // Go to pickUp LOW
  _delay_ms(2000);
  setEndEffectorSuctionCmd(1 , 1); //Turn suctionCup ON
  _delay_ms(500);      
  setPTPCmd(mode,  13.63, -294.88, 46.83, 0); // Go to pickUp HIGH
  _delay_ms(2000);
  setPTPCmd(mode, 130.25, -176.69, 81.42, 0); // Go to greenStorage HIGH
  _delay_ms(2000);
  setPTPCmd(mode, 130.25, -176.69, (-54.12 + (space*32)), 0); // Go to greenStorage number 'space'
  _delay_ms(2000);
  setEndEffectorSuctionCmd(1 , 0); //Turn suctionCup OFF
  _delay_ms(500);
  setPTPCmd(mode, 130.25, -176.69, 81.42, 0);  // Go to greenStorage HIGH
  _delay_ms(2000);
  }

void retrieve_green(unsigned int space, int mode){  
  _delay_ms(2000);
  setPTPCmd(mode, 130.25, -176.69, 81.42, 0);  // Go to greenStorage HIGH
  _delay_ms(2000);
  setPTPCmd(mode, 130.25, -176.69, (-54.12 + ((space-1)*32)), 0); // Go to greenStorage number 'space'
  _delay_ms(2000);
  setEndEffectorSuctionCmd(1 , 1); //Turn suctionCup ON
  _delay_ms(500);
  setPTPCmd(mode, 130.25, -176.69, 81.42, 0);  // Go to greenStorage HIGH
  _delay_ms(2000);
  setPTPCmd(mode,  13.63, -294.88, 46.83, 0); // Go to pickUp HIGH
  _delay_ms(2000);
  setPTPCmd(mode, 19.27, -270, -51.08, 0); // Go to pickUp LOW
  _delay_ms(2000);
  setEndEffectorSuctionCmd(1 , 0); //Turn suctionCup OFF
  _delay_ms(500);
  setPTPCmd(mode, 13.63, -294.88, 46.83, 0); // Go to pickUp HIGH
  _delay_ms(2000);
}

void red(unsigned int space, int mode){
  _delay_ms(2000);
  setPTPCmd(mode, 13.63, -294.88, 46.83, 0); // Go to pickUp HIGH
  _delay_ms(2000);
  setPTPCmd(mode, 19.27, -270, -51.08, 0); // Go to pickUp LOW
  _delay_ms(2000);
  setEndEffectorSuctionCmd(1 , 1); //Turn suctionCup ON
  _delay_ms(500);   
  setPTPCmd(mode,  13.63, -294.88, 46.83, 0); // Go to pickUp HIGH
  _delay_ms(2000);
  setPTPCmd(mode, 72.60, -259.71, 67.63, 0); // Go to redStorage HIGH
  _delay_ms(2000);
  setPTPCmd(mode, 76.73, -228.93, (-54.06 + (space*32)), 0); // Go to redStorage 'space 1'
  _delay_ms(2000);
  setEndEffectorSuctionCmd(1 , 0); //Turn suctionCup OFF
  _delay_ms(500);
  setPTPCmd(mode, 72.60, -259.71, 67.63, 0); // Go to redStorage HIGH
  _delay_ms(2000);
  }

void retrieve_red(unsigned int space, int mode){
  _delay_ms(2000);
  setPTPCmd(mode, 72.60, -259.71, 67.63, 0); // Go to redStorage HIGH
  _delay_ms(2000);
  setPTPCmd(mode, 76.73, -228.93, (-54.06 + ((space-1)*32)), 0); // Go to redStorage 'space 1'
  _delay_ms(2000);
  setEndEffectorSuctionCmd(1 , 1); //Turn suctionCup ON
  _delay_ms(500);  
  setPTPCmd(mode, 72.60, -259.71, 67.63, 0); // Go to redStorage HIGH
  _delay_ms(2000);
  setPTPCmd(mode,  13.63, -294.88, 46.83, 0); // Go to pickUp HIGH
  _delay_ms(2000);
  setPTPCmd(mode, 19.27, -270, -51.08, 0); // Go to pickUp LOW
  _delay_ms(2000);
  setEndEffectorSuctionCmd(1 , 0); //Turn suctionCup OFF
  _delay_ms(500);
  setPTPCmd(mode, 13.63, -294.88, 46.83, 0); // Go to pickUp HIGH
  _delay_ms(2000);
}

void blue(unsigned int space, int mode){
  _delay_ms(2000);
  setPTPCmd(mode, 13.63, -294.88, 46.83, 0); // Go to pickUp HIGH
  _delay_ms(2000);
  setPTPCmd(mode, 19.27, -270, -51.08, 0); // Go to pickUp LOW
  _delay_ms(2000);
  setEndEffectorSuctionCmd(1 , 1); //Turn suctionCup ON
  _delay_ms(500);
  setPTPCmd(mode,  13.63, -294.88, 46.83, 0); // Go to pickUp HIGH
  _delay_ms(2000);
  setPTPCmd(mode,  185.13, -136.87, 65.37, 0); // Go to blueStorage HIGH
  _delay_ms(2000);
  setPTPCmd(mode, 180.82, -125.47, (-53.28 + (space*32)), 0); // Go to blueStorage 'space 1'
  _delay_ms(2000);
  setEndEffectorSuctionCmd(1 , 0); //Turn suctionCup OFF
  _delay_ms(500);
  setPTPCmd(mode,  185.13, -136.87, 65.37, 0); // Go to blueStorage HIGH
  _delay_ms(2000);  
}


void retrieve_blue(unsigned int space, int mode){
  _delay_ms(2000);  
  setPTPCmd(mode,  185.13, -136.87, 65.37, 0); // Go to blueStorage HIGH
  _delay_ms(2000);  
  setPTPCmd(mode, 180.82, -125.47, (-54 + ((space-1)*32)), 0); // Go to blueStorage 'space 1'
  _delay_ms(2000);
  setEndEffectorSuctionCmd(1 , 1); //Turn suctionCup ON
  _delay_ms(500);
  setPTPCmd(mode,  185.13, -136.87, 65.37, 0); // Go to blueStorage HIGH
  _delay_ms(2000); 
  setPTPCmd(mode,  13.63, -294.88, 46.83, 0); // Go to pickUp HIGH
  _delay_ms(2000);
  setPTPCmd(mode, 19.27, -270, -51.08, 0); // Go to pickUp LOW
  _delay_ms(2000);
  setEndEffectorSuctionCmd(1 , 0); //Turn suctionCup OFF
  _delay_ms(500);
  setPTPCmd(mode,  13.63, -294.88, 46.83, 0); // Go to pickUp HIGH
  _delay_ms(2000);
}
