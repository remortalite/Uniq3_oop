#include "tPoint.hpp"

#include <iostream>

#ifndef MAXX
#define MAXX 600
#define MAXY 600
#endif // #ifndef MAXX

tPoint::tPoint() 
	: m_x(0), m_y(0)
{
	setRandColor();
}

tPoint::tPoint (int x, int y)
	: m_x(x), m_y(y)
{
	setRandColor();
}

void tPoint::print() {
	printf("Point (%d, %d)\n", m_x, m_y);
}

void tPoint::move(int dx, int dy) {
	m_x += dx;
	m_y += dy;
}

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

void tPoint::setRandColor() {
	m_colorR = rand() % 255;
	m_colorG = rand() % 255;
	m_colorB = rand() % 255;
}

void tPoint::setCoord(int x, int y) {
	m_x = x;
	m_y = y;
}

int tPoint::getX() {
	return m_x;
}

int tPoint::getY() {
	return m_y;
}

int tPoint::getColorR() {
	return m_colorR;
}

int tPoint::getColorG() {
	return m_colorG;
}

int tPoint::getColorB() {
	return m_colorB;
}
