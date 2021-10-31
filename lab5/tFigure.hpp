#ifndef FIGURES_HPP
#define FIGURES_HPP

#include <SFML/Graphics.hpp>

#include <cmath>

#define MAXX 600
#define MAXY 600

#define PI 3.14159265358979

class tFigure {
	int m_x;
	int m_y;

	unsigned short m_colorR;
	unsigned short m_colorG;
	unsigned short m_colorB;

	int m_width = 2;
	int m_height = 2;

	// set 1 or -1
	int m_motion = rand() % 2 > 0.5 ? -1 : 1;

	float m_rotation = rand() % 360;

public:

	tFigure();
	tFigure(int x, int y);

	void setRandColor();
	unsigned short getColorR();
	unsigned short getColorG();
	unsigned short getColorB();

	void setCoord(int x, int y);
	int getX();
	int getY();

	void setSize(int width, int height);
	void setW(int);
	void setH(int);
	int getW();
	int getH();

	void move(int dx, int dy);

	void moveLinear();
	void moveRandom();

	virtual sf::VertexArray getShape();

	void makeRotation();
	void setRotation(int rotation);

	void print();

	sf::Vector2f rotate(sf::Vector2f);
};

class tPoint : public tFigure
{
public:
	tPoint();
	tPoint(int x, int y);
};

class tCircle : public tPoint
{
public:
	tCircle();
	tCircle(int x, int y, int radius=8);

	void setRadius(int radius);
	int getRadius();

	virtual sf::VertexArray getShape();
};

class tEllipse : public tCircle
{
public:
	tEllipse();
	tEllipse(int x, int y, int radius=4, int radius2=8);

	void setRadius2(int radius);
	int getRadius2();
};

class tTriangle : public tFigure
{
public:
	tTriangle();
	tTriangle(int x, int y, int size=7);

	virtual sf::VertexArray getShape();
};
// rectangles
class tRectangle : public tFigure
{
public:
	tRectangle();
	tRectangle(int x, int y);
	tRectangle(int x, int y, int a, int b);

	void setSize(int a=6, int b=16);

	virtual sf::VertexArray getShape();
};

class tRombus : public tRectangle
{
public:
	tRombus();
	tRombus(int x, int y, int size=7, int size2=15);

	virtual sf::VertexArray getShape();
};


class tSquare : public tRectangle
{
public:
	tSquare();
	tSquare(int x, int y);
	tSquare(int x, int y, int size);
};

class tLine : public tRectangle
{
public:
	tLine();
	tLine(int x, int y, int size=7);
};

#endif // #ifndef FIGURES_HPP
