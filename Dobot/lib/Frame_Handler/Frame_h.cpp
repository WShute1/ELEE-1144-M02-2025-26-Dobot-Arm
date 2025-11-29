#include "Frame_h.h"
#include <string.h>
#include <avr/io.h>
#include "../dobotLibrary/Dobot.h"
extern Dobot myDobot;

// Function to perform homing of the Dobot arm
void homing() {
    uint8_t comFrame[10];
    int len = 6;
    int ID = 31;    // ID of the homing command
    int CRTL = 1; // 3 for quueued execution and 1 for not queued

    // Command structure for homing
    comFrame[0] = 0xAA;  // Command ID for homing
    comFrame[1] = 0xAA;
    comFrame[2] = len;  
    comFrame[3] = ID;
    comFrame[4] = CRTL;
    comFrame[5] = 0; // No additional parameters
    comFrame[6] = 0;
    comFrame[7] = 0;
    comFrame[8] = 0;
    int checksum = calcChecksum(comFrame, 3, 4);
    comFrame[9] = checksum; // Payload checksum - 1 for end

    // Send command to Dobot
    myDobot.commandFrame(comFrame);
}


// Function to calculate checksum for the PaYload frame
uint8_t calcChecksum(uint8_t *frame, int start, int end) {
    uint16_t sum = 0;
    for (int i = start; i <= end; ++i) {
        sum += frame[i];
    }
    return (int)(256 - sum);
}

// Function to handle PTP (Point-to-Point) movement in bare C
// mode: 0 = Joint motion, 1 = Linear motion
// x, y, z: target coordinates in mm
// rHead: rotation of the end effector in degrees
void setPTPCmd(int mode, float x, float y, float z, float rHead) {
    uint8_t comFrame[20];
    int len = 19;
    int ID = 84;    // ID of the command
    int CRTL = 3; // 3 for quueued execution and 1 for not queued
    
    // Command structure for setPTPcmd
    comFrame[0] = 0xAA;  // Command ID for setPTPcmd
    comFrame[1] = 0xAA;
    comFrame[2] = len;  // Motion mode: 0 = Joint, 1 = Linear - Payload Start
    comFrame[3] = ID; //start of payload
    comFrame[4] = CRTL;
    comFrame[5] = mode; // Motion mode: 0 = Joint, 1 = Linear

    // Pack coordinates (4 bytes each, little-endian)
    memcpy(&comFrame[6], &x, 4);      // X coordinate
    memcpy(&comFrame[10], &y, 4);      // Y coordinate
    memcpy(&comFrame[14], &z, 4);     // Z coordinate
    memcpy(&comFrame[18], &rHead, 4); // Rotation (4 bytes)
    int checksum = calcChecksum(comFrame, 3, 21);
    comFrame[22] = checksum; // Payload checksum - 1 for end
    
    // Send command to Dobot
    myDobot.commandFrame(comFrame);
}
// Function to control the suction cup of the Dobot arm - 1 to enable, 0 to disable for both parameters 
void setEndEffectorSuctionCmd(uint8_t enable, uint8_t suctionCup) {
    uint8_t comFrame[10];
    int len = 4;
    int ID = 62;    // ID of the command
    int CRTL = 3; // 3 for quueued execution and 1 for not queued

    // Command structure for setEndEffectorSuctionCmd
    comFrame[0] = 0xAA;  // Command ID for setEndEffectorSuctionCmd
    comFrame[1] = 0xAA;
    comFrame[2] = len;  
    comFrame[3] = ID;
    comFrame[4] = CRTL;
    comFrame[5] = enable; // Enable or disable suction
    comFrame[6] = suctionCup; // Suction cup ID

    int checksum = calcChecksum(comFrame, 3, 6);
    comFrame[7] = checksum; // Payload checksum - 1 for end

    // Send command to Dobot
    myDobot.commandFrame(comFrame);
}