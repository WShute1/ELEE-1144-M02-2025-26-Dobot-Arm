//List the required header files
#include "coordinates.h"
#include "../dobotLibrary/Dobot.h" 
#include <Frame_h.h>
#include <avr/io.h>
#include <Arduino.h>

//coordinates grid defined by visio drawings get pose measurements
//Z axis positions
float highZ = 80.00;
float lowZ1 = -60.00;
float lowZ2 = -30.00;
float lowZ3 = 0.00;

//x and y coordinates for the loading bay
float lx = 20.00;
float ly = -278.00;

//x and y coordiantes for the retrieval area
float rrx = 232.00;
float rry = -70.00;

//x and y coordinates for the red storage area
float rx = 76.00;
float ry = -226.00;

//x and y coordinates for the green storage area
float gx = 129.00;
float gy = -174.00;

//x and y coordinates for the blue storage area
float bx = 180.00;
float by = -122.00;

/*Definition of the Point Array declared in coordinates.h
    It defines a 16 element array of the Point structure. The Point Structure
    contains variables to store four floats, the x, y, z and r coordinates for
    a position that the Dobots end effector needs to move too.
    each element of the area can be accessed using the keywords define in the enum
    PointId, since they are defined as the number "0" to "15".
*/
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

/* Using the PointId and mode suppiled the function sends arguments to the
    setPTPCmd() function. Which then orders the Dobot to move from its current
    position to a new position.
*/
void moveToPose(uint8_t mode, PointId id)
{
    setPTPCmd(mode, points[id].x, points[id].y, points[id].z, points[id].r);
}  

/* This function will retrieve a block from a storage area.
    storageHigh defines tells the function which element in the Points array to find
    the point above the storage area to move to first before desending to the storageLow point
    which changes depeneding on how many blocks are stored in the storage area.*/
void Retrieve(uint8_t mode, PointId storageHigh, PointId storageLow, int delay) {
    moveToPose(mode, POINT_retrievalHigh); //Move the dobot end effector to the point high
    _delay_ms(delay); // above the retriveval point. and then wait for a set delay.
    
    /*Move the dobot to a point high above the requested colours block storage area.
        print this position to the uart serial monitor to inform the user of the dobots future
        location. Then wait for a defined delay for the dobot arm to move to the locaiton. */
    moveToPose(mode, storageHigh);
    Serial.print(points[storageHigh].x);
    Serial.print(points[storageHigh].y);
    Serial.print(points[storageHigh].z);
    Serial.print(points[storageHigh].r);
    _delay_ms(delay);

    /*Move the dobot to a point touching a block in the requested storage area.
        print this position to the uart serial monitor to inform the user of the dobots future
        location. Then wait for a defined delay for the dobot arm to move to the locaiton. */
    moveToPose(mode, storageLow);
    Serial.print(points[storageLow].x);
    Serial.print(points[storageLow].y);
    Serial.print(points[storageLow].z);
    Serial.print(points[storageLow].r);
    _delay_ms(delay);

    //Turn on the vacuum pump of the dobot suction end effector
    setEndEffectorSuctionCmd(1,1);
    _delay_ms(delay);

    //Move the dobot back to a position high above the storage area.
    moveToPose(mode, storageHigh);
    _delay_ms(delay);

    //move the dobot to a position high above the block retrieval area.
    moveToPose(mode, POINT_retrievalHigh);
    _delay_ms(delay);

    //move the dobot arm to the drop off height in the retrieval area
    moveToPose(mode, POINT_retrievalLow);
    _delay_ms(delay);

    //Turn off the dobots vacuum pump, releasing the block.
    setEndEffectorSuctionCmd(1,0);
    _delay_ms(delay);
    
    /*move the dobot back to the retrieval high area to allow for the block to
        be recovered by the user.*/
    moveToPose(mode, POINT_retrievalHigh);
    _delay_ms(delay);

}   


/* This function will store a block from the loading area to the correctly coloured storage area.
    storageHigh  tells the function which element in the Points array to find
    the point above the storage area to move to first before desending to the storageLow point.
    The loading area is hard coded as this does not change depending on the colour of the
    block to store.
    */
void Storage(uint8_t mode, PointId storageHigh, PointId storageLow, int delay) {
    //move the dobot to a point high above the loading area.
    moveToPose(mode, POINT_pickUpHigh);
    _delay_ms(delay);

    //move the dobot to a point which will touch the top of a block in the loading area.
    moveToPose(mode, POINT_pickUpLow);
    _delay_ms(delay);  

    //Turn on the vacuum pump of the dobot suction end effector
    setEndEffectorSuctionCmd(1,1);
    _delay_ms(500);

    //move the dobot arm to the point high above the loading area.
    moveToPose(mode, POINT_pickUpHigh);
    _delay_ms(delay);

    /*Move the dobot to a point high above the requested colours block storage area.
        print this position to the uart serial monitor to inform the user of the dobots future
        location. Then wait for a defined delay for the dobot arm to move to the locaiton. */
    moveToPose(mode, storageHigh);
    Serial.print(points[storageHigh].x);
    Serial.print(points[storageHigh].y);
    Serial.print(points[storageHigh].z);
    Serial.print(points[storageHigh].r);
    _delay_ms(delay);

    /*Move the dobot to a safe height in the requested storage area. This changes depending
        on the number of stored blocks.
        print this position to the uart serial monitor to inform the user of the dobots future
        location. Then wait for a defined delay for the dobot arm to move to the locaiton. */
    moveToPose(mode, storageLow);
    Serial.print(points[storageLow].x);
    Serial.print(points[storageLow].y);
    Serial.print(points[storageLow].z);
    Serial.print(points[storageLow].r);
    _delay_ms(delay);

    //Turn off the dobots vacuum pump, releasing the block.
    setEndEffectorSuctionCmd(1,0);
    _delay_ms(500);

    //move the dobot arm to a point high above the storage area.
    moveToPose(mode, storageHigh);
    _delay_ms(delay);
} 