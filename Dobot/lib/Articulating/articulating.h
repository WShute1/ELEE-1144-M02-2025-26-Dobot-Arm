#ifndef ARTICULATING_H
#define ARTICULATING_H

#incude<stdint.h>
#include <avr/io.h>

void articulate(uint8_t mode, int storagePoint);
{
    _delay_ms(2000);
    setPTPCmd(mode, POINT_pickUpHigh);
    _delay_ms(2000);
    setPTPCmd(mode, POINT_pickUpLow);
    _delay_ms(2000);
    setEndEffectorSuctionCmd(1, 1);
    _delay_ms(500);

    setPTPCmd(mode, POINT_pickUpHigh);
    _delay_ms(2000);
    setPTPCmd(mode, POINT_redStorageHigh);
    _delay_ms(2000);
    setPTPCmd(mode, storagePoint);
    _delay_ms(2000);

    setEndEffectorSuctionCmd(1, 0);
    _delay_ms(500);

    setPTPCmd(mode, POINT_redStorageHigh);
    _delay_ms(2000);
}
#endif