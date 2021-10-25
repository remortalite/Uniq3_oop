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

void tFigure::makeRotation() {
	if (m_rotation >= 360) m_rotation = 0;
	else m_rotation += 0.06;
}

sf::Vector2f tFigure::rotate(sf::Vector2f vector) {

	double radians = m_rotation*2*PI/360;

	vector.x = vector.x - getX();// - getW()/2;
	vector.y = vector.y - getY();// - getH()/2;

	int prevX = vector.x;
	int prevY = vector.y;
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
	setSize(radius*2, radius*2);
}

int tCircle::getRadius() {
	return getH() / 2;
}

sf::VertexArray tCircle::getShape() {

		sf::Transform rotation;
		rotation.rotate(10.0f);

		sf::Transform transform = rotation.rotate(0.1f);
	
	int k = 128;
	sf::VertexArray shape (sf::TriangleFan, k);
	for (int i = 0; i < k/2; ++i) {
		shape[i].color = sf::Color(getColorR() ,getColorG(), getColorB());
		shape[i].position = sf::Vector2f(getX() + getW()/2*std::cos(i*2*PI/k), 
										getY() + getH()/2*std::sin(i*2*PI/k));
		shape[i].position = rotate(shape[i].position);

		shape[k-1-i].color = sf::Color(getColorR() ,getColorG(), getColorB());
		shape[k-1-i].position = sf::Vector2f(getX() + getW()/2*std::cos(i*2*PI/k), 
										getY() - getH()/2*std::sin(i*2*PI/k));
		shape[k-1-i].position = rotate(shape[i].position);
	}
	//makeRotation();
	//shape.setPosition(getX(), getY());
	//shape.setRotation(rotate());
	return shape;
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

//------ tTriangle ------

tTriangle::tTriangle()
	: tFigure()
{
}

tTriangle::tTriangle(int x, int y, int size)
	: tFigure(x, y)
{
	setW(size);
	setH(size);
}

sf::VertexArray tTriangle::getShape() {
		makeRotation();

		sf::VertexArray shape (sf::Triangles, 3);
		shape[0].color = sf::Color(getColorR()/3, getColorG(), getColorB());
		shape[0].position = rotate(sf::Vector2f(getX()-getW()/2, getY()));

		shape[1].color = sf::Color(getColorR(), getColorG()/3, getColorB());
		shape[1].position = rotate(sf::Vector2f(getX()+getW()/2, getY()));

		shape[2].color = sf::Color(getColorR(), getColorG(), getColorB()/3);
		shape[2].position = rotate(sf::Vector2f(getX(), getY()+getH()));

		//shape.setRotation(rotate());
		return shape;
}


/*
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
*/
/*
//------ tRombus ------

tRombus::tRombus()
	: tEllipse()
{
}

tRombus::tRombus(int x, int y, int size, int size2)
	: tEllipse(x, y, size, size2)
{
}

sf::CircleShape tRombus::getShape() {
		sf::CircleShape shape (2.f, 4);
		shape.scale(getRadius()/getRadius(), getRadius2()*1.0/getRadius());

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
*/
