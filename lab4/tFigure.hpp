#ifndef FIGURES_HPP
#define FIGURES_HPP

#include <SFML/Graphics.hpp>

#define MAXX 600
#define MAXY 600

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

	void setRotation(int rotation);

	void print();

	float rotate();
};

class tPoint : public tFigure
{
public:
	tPoint();
	tPoint(int x, int y);

	sf::CircleShape getShape();
};

class tCircle : public tPoint
{
public:
	tCircle();
	tCircle(int x, int y, int radius=8);

	void setRadius(int radius);
	int getRadius();
};

class tEllipse : public tCircle
{
public:
	tEllipse();
	tEllipse(int x, int y, int radius=4, int radius2=8);

	void setRadius2(int radius);
	int getRadius2();

	sf::CircleShape getShape();
};

class tTriangle : public tCircle
{
public:
	tTriangle();
	tTriangle(int x, int y, int size=7);

	sf::CircleShape getShape();
};

class tRombus : public tEllipse
{
public:
	tRombus();
	tRombus(int x, int y, int size=7, int size2=15);

	sf::ConvexShape getShape();
};


// rectangles

class tRectangle : public tFigure
{
public:
	tRectangle();
	tRectangle(int x, int y);
	tRectangle(int x, int y, int a, int b);

	void setSize(int a=3, int b=6);

	sf::RectangleShape getShape();
};

class tSquare : public tRectangle
{
public:
	tSquare();
	tSquare(int x, int y);
	tSquare(int x, int y, int size=7);
};

class tLine : public tRectangle
{
public:
	tLine();
	tLine(int x, int y, int size=7);
};


#endif // #ifndef FIGURES_HPP
