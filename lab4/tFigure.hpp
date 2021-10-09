#ifndef FIGURES_HPP
#define FIGURES_HPP

#include <SFML/Graphics.hpp>

class tFigure {
	int m_x;
	int m_y;

	unsigned short m_colorR;
	unsigned short m_colorG;
	unsigned short m_colorB;

protected:
	void setRandColor();

public:

	tFigure();
	tFigure(int x, int y);

	void setCoord(int x, int y);
	int getX();
	int getY();

	void move(int dx, int dy);

	void moveLinear();
	void moveRandom();

	void print();
};

#endif // #ifndef FIGURES_HPP
