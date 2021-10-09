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

unsigned short tFigure::getColorR() {
	return m_colorR;
}

unsigned short tFigure::getColorG() {
	return m_colorG;
}

unsigned short tFigure::getColorB() {
	return m_colorB;
}

void tFigure::print() {
	printf("Figure(%d, %d); Color(%d,%d,%d)\n", 
					m_x, m_y,
					m_colorR, m_colorG, m_colorB
					);
}

void tFigure::setSize(int width, int height) {
	m_height = height;
	m_width = width;
}

void tFigure::setW(int size) {
	m_width = size;
}

void tFigure::setH(int size) {
	m_height = size;
}

void tFigure::moveLinear() {
	if (m_x-m_width < 0 || m_x+m_width > MAXX)
		m_motion *= -1;
	move(m_motion, 0);
}

void tFigure::moveRandom() {
	int dx = rand() % 2 * 2 - 1;
	int dy = rand() % 2 * 2 - 1;
	int newX = m_x + dx;
	int newY = m_y + dy;
	if (newX < 0 || newX > MAXX-m_width)
		dx *= -1;
	if (newY < 0 || newY > MAXY-m_height)
		dy *= -1;
	move(dx, dy);
}

int tFigure::getW() {
	return m_width;
}

int tFigure::getH() {
	return m_height;
}

//------ tPoint ------

tPoint::tPoint()
	: tFigure()
{
}

tPoint::tPoint(int x, int y)
	: tFigure(x, y)
{
}

sf::CircleShape tPoint::getShape() {
		sf::CircleShape shape ((float) getW() );
		shape.setFillColor(sf::Color(getColorR(), getColorG(), getColorB()));
		shape.setPosition(getX(), getY());
		return shape;
}

//------ tCircle ------

tCircle::tCircle()
	: tPoint()
{
}

tCircle::tCircle(int x, int y, int radius)
	: tPoint(x, y)
{
	setRadius(radius);
}

void tCircle::setRadius(int radius) {
	setSize(radius*2, radius*2);
}

int tCircle::getRadius() {
	return getW() / 2;
}

//------ tEllipse ------
tEllipse::tEllipse()
	: tCircle()
{
}

tEllipse::tEllipse(int x, int y, int r, int r2)
	: tCircle(x, y, r)
{
	setW(r2);
}

void tEllipse::setRadius2(int r) {
	setW(r);
}

int tEllipse::getRadius2() {
	return getW();
}

sf::CircleShape tEllipse::getShape() {
	sf::CircleShape shape = tCircle::getShape();
	shape.scale(getW(), getH());
	return shape;
}
