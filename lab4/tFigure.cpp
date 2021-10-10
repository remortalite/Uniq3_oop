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
	if (m_x-1 < 0 || m_x+m_width+1 >= MAXX)
		m_motion *= -1;
	move(m_motion, 0);
}

void tFigure::moveRandom() {
	int dx = rand() % 2 * 2 - 1;
	int dy = rand() % 2 * 2 - 1;
	int newX = m_x + dx;
	int newY = m_y + dy;
	if (newX < 0 || newX+m_width > MAXX) {
		dx *= -1;
	}
	if (newY < 0 || newY+m_height > MAXY)
		dy *= -1;
	move(dx, dy);
}

int tFigure::getW() {
	return m_width;
}

int tFigure::getH() {
	return m_height;
}

void tFigure::setRotation(int rotation) {
	m_rotation = rotation;
}

float tFigure::rotate() {
	if (m_rotation >= 360) m_rotation = 0;
	else m_rotation += 0.1;
	return m_rotation;
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
		sf::CircleShape shape ((float) getH()/2 );
		shape.setFillColor(sf::Color(getColorR(), getColorG(), getColorB()));
		shape.setPosition(getX(), getY());
		shape.setRotation(rotate());
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
	return getH() / 2;
}

//------ tEllipse ------
tEllipse::tEllipse()
	: tCircle()
{
}

tEllipse::tEllipse(int x, int y, int r, int r2)
	: tCircle(x, y, r)
{
	setW(r2*2);
}

void tEllipse::setRadius2(int r) {
	setW(r*2);
}

int tEllipse::getRadius2() {
	return getW()/2;
}

sf::CircleShape tEllipse::getShape() {
	sf::CircleShape shape = tCircle::getShape();
	shape.scale(getRadius()/getRadius(), getRadius2()*1.0/getRadius());
		shape.setRotation(rotate());
	return shape;
}

//------ tRectangle ------

tRectangle::tRectangle()
	: tFigure()
{
}

tRectangle::tRectangle(int x, int y)
	: tFigure(x, y)
{
}

tRectangle::tRectangle(int x, int y, int a, int b)
	: tFigure(x, y)
{
	setSize(a, b);
}

void tRectangle::setSize(int a, int b)
{
	setH(a);
	setW(b);
}

sf::RectangleShape tRectangle::getShape() {
	sf::RectangleShape shape (sf::Vector2f((float)getW(), (float)getH()));
	shape.setFillColor(sf::Color(getColorR(), getColorG(), getColorB()));
	shape.setPosition(getX(), getY());
		shape.setRotation(rotate());
	return shape;
}

//------ tTriangle ------

tTriangle::tTriangle()
	: tCircle()
{
}

tTriangle::tTriangle(int x, int y, int size)
	: tCircle(x, y, size)
{
}

sf::CircleShape tTriangle::getShape() {
		sf::CircleShape shape ((float) getH()/2, 3 );
		shape.setFillColor(sf::Color(getColorR(), getColorG(), getColorB()));
		shape.setPosition(getX(), getY());
		shape.setRotation(rotate());
		return shape;
}


//------ tRombus ------

tRombus::tRombus()
	: tEllipse()
{
}

tRombus::tRombus(int x, int y, int size, int size2)
	: tEllipse(x, y, size, size2)
{
}

sf::ConvexShape tRombus::getShape() {
		sf::ConvexShape shape;
		shape.setPointCount(4);
		shape.setPoint(0, sf::Vector2f(getW()*1.0/2, 0.f));
		shape.setPoint(1, sf::Vector2f(0, getH()*1.0/2));
		shape.setPoint(2, sf::Vector2f(getW()*1.0/2, getH()*1.0));
		shape.setPoint(3, sf::Vector2f(getW()*1.0, getH()*1.0/2));

		shape.setFillColor(sf::Color(getColorR(), getColorG(), getColorB()));
		shape.setPosition(getX(), getY());
		shape.setRotation(rotate());
		return shape;
}





//------ tSquare ------

tSquare::tSquare()
	: tRectangle()
{
}

tSquare::tSquare(int x, int y)
	: tRectangle(x, y)
{
}

tSquare::tSquare(int x, int y, int size)
	: tRectangle(x, y)
{
	setSize(size, size);
}

//------ tLine ------
tLine::tLine()
	: tRectangle()
{
}

tLine::tLine(int x, int y, int size)
	: tRectangle(x, y)
{
	setH(size);
	setW(2);
}
