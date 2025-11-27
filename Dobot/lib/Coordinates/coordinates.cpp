#include "coordinates.h"
#include "../dobotLibrary/Dobot.h"
#include <Frame_h.h>
#include <avr/io.h>
#include <Arduino.h>

//coordinates grid defined by visio drawings and measurements
float highZ = 80.00;
float lowZ1 = -50.00;
float lowZ2 = -20.00;
float lowZ3 = 6.00;

float lx = 20.00;
float ly = -278.00;

float rrx = 232.00;
float rry = -70.00;

float rx = 76.00;
float ry = -226.00;

float gx = 129.00;
float gy = 174.00;

float bx = 180.00;
float by = -122.00;


const Point points[POINT_COUNT] = {
    [POINT_retrievalLow] = {rrx, rry, lowZ1, -44.88},
    [POINT_retrievalHigh] = {rrx, rry, highZ, -44.48},
    
    [POINT_blueStorageHigh] = {bx, by, highZ, -64.68},
    [POINT_blueStorageSpace1] = {bx, by, lowZ1, -62.96},
    [POINT_blueStorageSpace2] = {bx, by, lowZ2, -62.96},
    [POINT_blueStorageSpace3] = {bx, by, lowZ3, -64.68},

    [POINT_greenStorageHigh] = {gx, gy, highZ, -81.14},
    [POINT_greenStorageSpace1] = {gx, gy, lowZ1, -81.80},
    [POINT_greenStorageSpace2] = {gx, gy, lowZ2, -81.80},
    [POINT_greenStorageSpace3] = {gx, gy, lowZ3, -81.80},

    [POINT_redStorageHigh] = {rx, ry, highZ, -102.58},
    [POINT_redStorageSpace1] = {rx, ry, lowZ1, -99.67},
    [POINT_redStorageSpace2] = {rx, ry, lowZ2, -99.67},
    [POINT_redStorageSpace3] = {rx, ry, lowZ3, -99.67},

    [POINT_pickUpHigh] = {lx, ly, highZ, -115.56},
    [POINT_pickUpLow] = {lx, ly, lowZ1, -113.97},
};

void moveToPose(uint8_t mode, PointId id)
{
    //const Point *p = &points[id];
    setPTPCmd(mode, points[id].x, points[id].y, points[id].z, points[id].r);
}  

void Retrieve(uint8_t mode, PointId storageHigh, PointId storageLow, int delay) {
    moveToPose(mode, POINT_retrievalHigh);
    _delay_ms(delay);
    
    moveToPose(mode, storageHigh);
    Serial.print(points[storageHigh].x);
    Serial.print(points[storageHigh].y);
    Serial.print(points[storageHigh].z);
    Serial.print(points[storageHigh].r);
    _delay_ms(delay);

    moveToPose(mode, storageLow);
    Serial.print(points[storageLow].x);
    Serial.print(points[storageLow].y);
    Serial.print(points[storageLow].z);
    Serial.print(points[storageLow].r);
    _delay_ms(delay);

    setEndEffectorSuctionCmd(1,1);
    _delay_ms(500);

    moveToPose(mode, POINT_retrievalHigh);
    _delay_ms(delay);

    // Use parameter instead of hardcoded blue storage
    moveToPose(mode, POINT_retrievalLow);
    _delay_ms(delay);

    setEndEffectorSuctionCmd(1,0);
    _delay_ms(500);

    moveToPose(mode, POINT_retrievalHigh);
    _delay_ms(delay);

}   


void Storage(uint8_t mode, PointId storageHigh, PointId storageLow, int delay) {
    moveToPose(mode, POINT_pickUpHigh);
    _delay_ms(delay);

    moveToPose(mode, POINT_pickUpLow);
    _delay_ms(delay);  

    setEndEffectorSuctionCmd(1,1);
    _delay_ms(500);

    moveToPose(mode, POINT_pickUpHigh);
    _delay_ms(delay);

    moveToPose(mode, storageHigh);
    _delay_ms(delay);

    moveToPose(mode, storageLow);
    _delay_ms(delay);

    setEndEffectorSuctionCmd(1,0);
    _delay_ms(500);

    moveToPose(mode, storageHigh);
    _delay_ms(delay);
} 