#ifndef _CALCULATIONS_H
#define _CALCULATIONS_H
#include <stdint.h>
#include <arm_math.h>
#include "lcd.h"

int32_t FastSin(uint16_t); // 2^10 = 360 degrees 
int32_t FastCos(uint16_t); // 2^10 = 360 degrees 
Point RotatePoint(Point Coord, Point Coord0, float32_t angle); //angle in degrees
void RotatePoly(Point* pToPoints, const pPoint Origin, uint8_t NumbOfPoints, float32_t angle_deg);
#endif
