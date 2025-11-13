#include "Frame_h.h"
#include <string.h>
#include <avr/io.h>
#include "../dobotLibrary/Dobot.h"
extern Dobot myDobot;



void homing() {
    uint8_t comFrame[10];
    int len = 6;
    int ID = 31;    // ID of the homing command
    int CRTL = 3; // 3 for quueued execution and 1 for not queued

    // Command structure for homing
    comFrame[0] = 0xAA;  // Command ID for homing
    comFrame[1] = 0xAA;
    comFrame[2] = len;  
    comFrame[3] = ID;
    comFrame[4] = CRTL;

    int checksum = calcChecksum(comFrame, 2, 4);
    comFrame[5] = checksum; // Payload checksum - 1 for end

    // Send command to Dobot
    myDobot.commandFrame(comFrame);
}


// Function to calculate checksum for the PaYload frame
uint8_t calcChecksum(uint8_t *frame, int start, int end) {
    uint16_t sum = 0;
    for (int i = start; i <= end; ++i) {
        sum += frame[i];
    }
    return (int)(sum & 0xFF);
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
    comFrame[3] = ID;
    comFrame[4] = CRTL;
    comFrame[5] = mode; // Motion mode: 0 = Joint, 1 = Linear

    // Pack coordinates (4 bytes each, little-endian)
    memcpy(&comFrame[6], &x, 4);      // X coordinate
    memcpy(&comFrame[10], &y, 4);      // Y coordinate
    memcpy(&comFrame[14], &z, 4);     // Z coordinate
    memcpy(&comFrame[18], &rHead, 4); // Rotation (4 bytes)
    int checksum = calcChecksum(comFrame, 2, 21);
    comFrame[22] = checksum; // Payload checksum - 1 for end
    
    // Send command to Dobot
    myDobot.commandFrame(comFrame);
}