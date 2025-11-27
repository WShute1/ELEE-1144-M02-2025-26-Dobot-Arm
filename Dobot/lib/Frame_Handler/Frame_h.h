#ifndef FRAME_H
#define FRAME_H

#include <avr/io.h>

uint8_t calcChecksum(uint8_t *frame, int start, int end);

//PTPMODE = 0 - 9
// JUMP_XYZ, // JUMP mode, (x,y,z,r) is the target point in Cartesian coordinate system
// MOVJ_XYZ, // MOVJ mode, (x,y,z,r) is the target point in Cartesian coordinate system
// MOVL_XYZ, //MOVL mode, (x,y,z,r) is the target point in Cartesian coordinate system
// JUMP_ANGLE, // JUMP mode, (x,y,z,r) is the target point in Joint coordinate system
// MOVJ_ANGLE, // MOVJ mode, (x,y,z,r) is the target point in Joint coordinate system
// MOVL_ANGLE, // MOVL mode, (x,y,z,r) is the target point in Joint coordinate system
// MOVJ_INC, // MOVJ mode, (x,y,z,r) is the angle increment in Joint coordinate system
// MOVL_INC, // MOVL mode, (x,y,z,r) is the Cartesian coordinate increment in Joint coordinate system
// MOVJ_XYZ_INC, // MOVJ mode, (x,y,z,r) is the Cartesian coordinate increment in Cartesian coordinate system
// JUMP_MOVL_XYZ, // JUMP mode, (x,y,z,r) is the Cartesian coordinate increment in Cartesian coordinate system

void setPTPCmd(int mode, float x, float y, float z, float rHead);
void homing();
void setEndEffectorSuctionCmd(uint8_t enable, uint8_t suctionCup);

#endif