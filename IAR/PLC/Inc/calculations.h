#ifndef _CALCULATIONS_H
#define _CALCULATIONS_H
#include <stdint.h>
#include <arm_math.h>
#include "lcd.h"

#define MAX_POLY_POINTS 24

int32_t FastSin(uint16_t); // 2^10 = 360 degrees 
int32_t FastCos(uint16_t); // 2^10 = 360 degrees 
Point RotatePoint(Point Coord, Point Coord0, float32_t angle); //angle in degrees
void RotatePoly(Point* pToPoints, uint8_t NumbOfPoints, const pPoint Origin, uint32_t angle_deg);
void StorePoly(const Point* pToPoints, uint8_t NumbOfPoints); //we can store our poly before rotation 
void RestorePoly(Point* pToPoints, uint8_t NumbOfPoints); //and restore it after to iliminate degradation 
uint8_t * Itoa(uint16_t Number);
#endif
