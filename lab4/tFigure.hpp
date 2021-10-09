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
	int getW();
	int getH();

	void move(int dx, int dy);

	void moveLinear();
	void moveRandom();

	void print();
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
	tCircle(int x, int y, int radius=2);

	void setRadius(int radius);
	int getRadius();
};


#endif // #ifndef FIGURES_HPP
