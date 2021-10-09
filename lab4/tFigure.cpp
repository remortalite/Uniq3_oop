#include "tFigure.hpp"

#include <iostream>
#include <cassert>

tFigure::tFigure()
	: m_x(0), m_y(0)
{
	setRandColor();
}

tFigure::tFigure(int x, int y)
	: m_x(x), m_y(y)
{
	setRandColor();
}

void tFigure::setCoord(int x, int y) {
	assert(x > 0 && y > 0);
	m_x = x;
	m_y = y;
}

int tFigure::getX() {
	return m_x;
}

int tFigure::getY() {
	return m_y;
}

void tFigure::move(int dx, int dy) {
	setCoord(m_x+dx, m_y+dy);
}

void tFigure::setRandColor() {
	m_colorR = rand()%255;
	m_colorG = rand()%255;
	m_colorB = rand()%255;
}

void tFigure::print() {
	printf("Figure(%d, %d); Color(%d,%d,%d)\n", 
					m_x, m_y,
					m_colorR, m_colorG, m_colorB
					);
}

