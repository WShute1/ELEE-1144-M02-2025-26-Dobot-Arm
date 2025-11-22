#include "coordinates.h"
#include "../dobotLibrary/Dobot.h"
#include <Frame_h.h>
#include <avr/io.h>

//coordinates grid defined by visio drawings and measurements
float highZ = 80.00f;
float lowZ1 = -50.00f;
float lowZ2 = -20.00f;
float lowZ3 = 10.00f;

float lx = 20.00f;
float ly = -278.00f;

float rrx = 232.00f;
float rry = -70.00f;

float rx = 76.00f;
float ry = -226.00f;

float gx = 129.00f;
float gy = 174.00f;

float bx = 180.00f;
float by = -122.00f;


const Point points[POINT_COUNT] = {
    [POINT_retrievalLow] = {rrx, rry, lowZ1, -44.88f},
    [POINT_retrievalHigh] = {rrx, rry, highZ, -44.48f},
    
    [POINT_blueStorageHigh] = {bx, by, highZ, -64.68f},
    [POINT_blueStorageSpace1] = {bx, by, lowZ1, -62.96f},
    [POINT_blueStorageSpace2] = {bx, by, lowZ2, -62.96f},
    [POINT_blueStorageSpace3] = {bx, by, lowZ3, -64.68f},

    [POINT_greenStorageHigh] = {gx, gy, highZ, -81.14f},
    [POINT_greenStorageSpace1] = {gx, gy, lowZ1, -81.80f},
    [POINT_greenStorageSpace2] = {gx, gy, lowZ2, -81.80f},
    [POINT_greenStorageSpace3] = {gx, gy, lowZ3, -81.80f},

    [POINT_redStorageHigh] = {rx, ry, highZ, -102.58f},
    [POINT_redStorageSpace1] = {rx, ry, lowZ1, -99.67f},
    [POINT_redStorageSpace2] = {rx, ry, lowZ2, -99.67f},
    [POINT_redStorageSpace3] = {rx, ry, lowZ3, -99.67f},

    [POINT_pickUpHigh] = {lx, ly, highZ, -115.56f},
    [POINT_pickUpLow] = {lx, ly, lowZ1, -113.97f},
};

void moveToPose(uint8_t mode, PointId id)
{
    const Point *p = &points[id];
    setPTPCmd(mode, p->x, p->y, p->z, p->r);
}  

void Retrieve(uint8_t mode, PointId storageHigh, PointId storageLow, int delay) {
    moveToPose(mode, POINT_retrievalHigh);
    _delay_ms(delay);
    
    moveToPose(mode, storageHigh);
    _delay_ms(delay);

    moveToPose(mode, storageLow);
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