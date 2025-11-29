#ifndef COORDINATES_H /*Set header guard, only compile the data within the #if statement if the coordinates.h header 
                            has not be defined already by another part of the program.*/
#define COORDINATES_H

//Add a refernce to other libraries used in the coordinate.cpp file
#include <stdint.h> 
#include <avr/io.h>

/*Define a structure that consists of four floats, each represents an axis the dobot can move.
    x, y, z are the end effectors positon in 3D space and r is the rotation of the end effector.
    r is not controllable for the suction cup however the dobot communication protocol
    so it is defined here.
    The typedef keyword is used to assign the new data structure to a datatype name, in this
    instance it is Point.
*/
typedef struct {
    float x;
    float y;
    float z;
    float r;
} Point;

/*Define a enumerated group of keywords
    The group consists of 17 keywords which are mapped to number values
    POINT_retrievalLow = 0, POINT_redStorageHigh = 10 for example.
    This group of keywords become a type of variable that can be used. 
    The typedef statement is used to name this new variable type PointId.
    PointId can be used to declare variables of the enum type using the 
    17 keywords used below.
    */

typedef enum {
    POINT_retrievalLow,         //0
    POINT_retrievalHigh,        //1
    
    POINT_blueStorageHigh,      //2
    POINT_blueStorageSpace1,    //3
    POINT_blueStorageSpace2,    //4
    POINT_blueStorageSpace3,    //5

    POINT_greenStorageHigh,     //6
    POINT_greenStorageSpace1,   //7
    POINT_greenStorageSpace2,   //8
    POINT_greenStorageSpace3,   //9

    POINT_redStorageHigh,       //10
    POINT_redStorageSpace1,     //11
    POINT_redStorageSpace2,     //12
    POINT_redStorageSpace3,     //13

    POINT_pickUpHigh,           //14
    POINT_pickUpLow,            //15

    POINT_COUNT                 //16
} PointId;

/* Create an array of the Point structure, name the array Points, the array contains 
    16 slots one for each of the keywords defined in the enum PointId excluding POINT_COUNT.
    The extern keyword allows the array to be assessed by functions outside of the current file
    It therefore extends the scope of the variable to be global across all files in the program.
    The const keyword tells the complier that the array once defined will not change its values.
*/
extern const Point points[POINT_COUNT];

// Function declarations for functions defined in coordinates.cpp
void moveToPose(uint8_t mode, PointId id);

void Retrieve(uint8_t mode, PointId storageHigh, PointId storageLow, int delay);

void Storage(uint8_t mode, PointId storageHigh, PointId storageLow, int delay);

#endif