#include <Dobot.h>
#include <string.h>
#include <Button.h>
#include <Frame_h.h>
#include <util/delay.h>
#include <stdlib.h>
#include <US.h>


Dobot myDobot;

void setup() {
  myDobot.begin();
  button_init();

}

int main() {
  // Example: Move arm to position (10, 10, 10) in MOVJ_XYZ mode
  setup();
  int mode = 1; // MOVJ_XYZ
  float x = 10.0; // in mm  
  float y = 10.0; // in mm
  float z = 10.0; // in mm
  float rHead = 0.0; // No rotation

  homing(); // Perform homing first

  _delay_ms(1000); // Wait for homing to complete

  setPTPCmd(mode, x, y, z, rHead); // Move to specified position

  _delay_ms(1000);

  while (1) {
    // Check if button A3 is pressed
    if (button_A3_pressed()) {
      // get and print the current pose of the Dobot
      myDobot.printPose();
      _delay_ms(500); // Debounce delay
    }
  }
  if (button_A4_pressed()) {
    while (1) {
    int block =  Detect(); // Call Detect function
    _delay_ms(500); // Debounce delay
    if (block) {
        // If an object is detected within 4 cm
        //myDobot.printPose(); // Print current pose
        //_delay_ms(500); // Debounce delay
      }

    }
  }
}
