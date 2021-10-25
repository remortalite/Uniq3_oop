#include "tPoint.hpp"

#include <iostream>

#ifndef MAXX
#define MAXX 600
#define MAXY 600
#endif // #ifndef MAXX

tPoint::tPoint() 
	: tFigure()
{
}

tPoint::tPoint (int x, int y)
	: tFigure(x, y)
{
}
/*
void tPoint::moveLinear() {
	if (m_x-1 < 0 || m_x+1 > MAXY)
		motion *= -1;
	move(motion, 0);
}

void tPoint::moveRandom() {
	int dx = rand() % 2 * 2 - 1;
	int dy = rand() % 2 * 2 - 1;
	int newX = m_x + dx;
	int newY = m_y + dy;
	if (newX < 0 || newX > MAXX)
		dx *= -1;
	if (newY < 0 || newY > MAXY)
		dy *= -1;
	move(dx, dy);
}
*/
