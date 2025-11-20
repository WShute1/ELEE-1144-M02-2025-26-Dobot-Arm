#ifndef COORDINATES_H
#define COORDINATES_H

#include <stdint.h>

typedef struct {
    float x;
    float y;
    float z;
    float r;
} Point;

typedef enum {
    POINT_retrievalLow,
    POINT_retrievalHigh,
    
    POINT_blueStorageHigh,
    POINT_blueStorageSpace1,
    POINT_blueStorageSpace2,
    POINT_blueStorageSpace3,

    POINT_greenStorageHigh,
    POINT_greenStorageSpace1,
    POINT_greenStorageSpace2,
    POINT_greenStorageSpace3,

    POINT_redStorageHigh,
    POINT_redStorageSpace1,
    POINT_redStorageSpace2,
    POINT_redStorageSpace3,

    POINT_pickUpHigh,
    POINT_pickUpLow,

    POINT_COUNT   // keep this last
} PointId;

// Global lookup table (read-only)
extern const Point points[POINT_COUNT];

// Convenience wrapper
void moveTo(uint8_t mode, PointId id);

#endif