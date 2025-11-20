#include "coordinates.h"
#include "../dobotLibrary/Dobot.h"
#include <avr/io.h>

const Point points[POINT_COUNT] = {
    [POINT_retrievalLow] = {233.16f, -69.85f, -54.63f, -44.88f},
    [POINT_retrievalHigh] = {234.18f, -68.39f, 27.84f, -44.48f},
    
    [POINT_blueStorageHigh] = {185.13f, -136.87f, 65.37f, -64.68f},
    [POINT_blueStorageSpace1] = {180.82f, -125.47f, -53.28f, -62.96f},
    [POINT_blueStorageSpace2] = {180.82f, -125.47f, -22.28f, -62.96f},
    [POINT_blueStorageSpace3] = {180.82f, -125.47f, 10.00f, -64.68f},

    [POINT_greenStorageHigh] = {130.25f, -176.69f, 81.42f, -81.14f},
    [POINT_greenStorageSpace1] = {130.25f, -176.69f, -54.12f, -81.80f},
    [POINT_greenStorageSpace2] = {130.25f, -176.69f, -22.12f, -81.80f},
    [POINT_greenStorageSpace3] = {130.25f, -176.69f, 10.00f, -81.80f},

    [POINT_redStorageHigh] = {72.60f, -259.71f, 67.63f, -102.58f},
    [POINT_redStorageSpace1] = {76.73f, -228.93f, -54.06f, -99.67f},
    [POINT_redStorageSpace2] = {82.73f, -228.93f, -22.06f, -99.67f},
    [POINT_redStorageSpace3] = {85.73f, -228.93f, 10.00f, -99.67f},

    [POINT_pickUpHigh] = {13.63f, -294.88f, 46.83f, -115.56f},
    [POINT_pickUpLow] = {20.65f, -278.84f, -51.08f, -113.97f},
};

void moveToPose(uint8_t mode, PoseId id)
{
    const Pose *p = &poses[id];
    setPTPCmd(mode, p->x, p->y, p->z, p->r);
}   