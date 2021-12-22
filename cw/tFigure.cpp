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

sf::VertexArray tFigure::getShape() {
		//sf::CircleShape shape ((float) getH()/2 );
		sf::VertexArray shape (sf::Points, 1);
		//shape.setFillColor(sf::Color(getColorR(), getColorG(), getColorB()));
		shape[0].color = sf::Color(getColorR() ,getColorG(), getColorB());
		//shape.setPosition(getX(), getY());
		shape[0].position = sf::Vector2f(getX(), getY());
		//shape.setRotation(rotate());
		return shape;
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
	if (m_x-1 < 0 || m_x+m_width >= MAXX)
		m_motion *= -1;
	move(m_motion, 0);
}

void tFigure::moveRandom() {
	int dx = rand() % 2 * 2;
	int dy = rand() % 2 * 2;
	//dx *= m_speed;
	//dy *= m_speed;
	//dx *= rand() % 5;
	//dy *= rand() % 5;
	int newX = m_x + dx;
	int newY = m_y + dy;
	if (newX-m_width/2 < 20 || newX+m_width/2 > MAXX-20) {
		dx *= -1;
		m_rotationSpeed = 3;
	} else {
		if (newY-m_width/2 < 20 || newY+m_height/2 > MAXY-20) {
			dy *= -1;
			m_rotationSpeed = 3;
		}
		else
			m_rotationSpeed = 1;
	}

	int addX = (newX < 60) ? (60-newX)/2 : 0;
	addX = (newX > MAXX-60) ? -(60-newX+MAXX)/2 : 0;

	int addY = (newY < 60) ? (60-newY)/2 : 0;
	addY = (newY > MAXY-60) ? -(60-newY+MAXX)/2 : 0;

	int radians = m_rotation*2*PI/360;
	move(-dx*std::cos(radians)+addX, -dy*std::sin(radians)+addY);
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

void tFigure::makeRotation() {
	m_rotation += m_rotationSpeed * (rand() % 3 - 1);
	if (m_rotation > 360) m_rotation = 0;
	if (m_rotation < 0) m_rotation = 360;
}

sf::Vector2f tFigure::rotate(sf::Vector2f vector) {

	double radians = m_rotation*2*PI/360;

	vector.x = vector.x - getX();// - getW()/2;
	vector.y = vector.y - getY();// - getH()/2;

	int prevX = vector.x;
	int prevY = vector.y;

	float prevNormX = m_norm.x;
	float prevNormY = m_norm.y;
	//m_norm.x = prevX*std::cos(radians) - prevY*std::sin(radians);
	//m_norm.y = prevX*std::sin(radians) + prevY*std::cos(radians);

	vector.x = prevX*std::cos(radians) - prevY*std::sin(radians);
	vector.y = prevX*std::sin(radians) + prevY*std::cos(radians);

	vector.x = vector.x + getX();// + getW()/2;
	vector.y = vector.y + getY();// + getH()/2;

	return vector;
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
	setSize(radius, radius);
}

int tCircle::getRadius() {
	return getH() / 2;
}

sf::VertexArray tCircle::getShape() {

	int k = 128;
	int t = k + k/4;
	sf::VertexArray shape (sf::TriangleFan, k);
	for (int i = 0; i < k/2; ++i) {
		shape[i].color = sf::Color(getColorR() ,getColorG(), getColorB());
		shape[i].position = sf::Vector2f(getX() + getW()/2*std::cos(i*2*PI/t), 
										getY() + getH()/2*std::sin(i*2*PI/t));
		shape[i].position = rotate(shape[i].position);

		shape[k-1-i].color = sf::Color(getColorR() ,getColorG(), getColorB());
		shape[k-1-i].position = sf::Vector2f(getX() + getW()/2*std::cos(i*2*PI/t), 
										getY() - getH()/2*std::sin(i*2*PI/t));
		shape[k-1-i].position = rotate(shape[k-1-i].position);
	}
	shape[k/2].position = sf::Vector2f(getX(), getY());
	makeRotation();
	//shape.setPosition(getX(), getY());
	//shape.setRotation(rotate());
	return shape;
}

