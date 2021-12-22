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

	int m_speed = rand() % 4 + 1;

	// set 1 or -1
	int m_motion = rand() % 2 > 0.5 ? -1 : 1;

	float m_rotation = rand() % 360;
	float m_rotationSpeed = 1;


	sf::Vector2f m_norm = {-2.0, 0.0};

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

#endif // #ifndef FIGURES_HPP
