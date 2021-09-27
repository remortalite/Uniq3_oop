#ifndef TPOINT_HPP
#define TPOINT_HPP

class tPoint
{
public:
    tPoint();
	tPoint(int x, int y);

	void print();

	void move(int dx, int dy);

	void moveLinear();

	void moveRandom();

	void setCoord(int, int);
	int getX();
	int getY();

	int getColorR();
	int getColorG();
	int getColorB();

private:
    int m_x;
	int m_y;

    int m_colorR;
    int m_colorG;
    int m_colorB;

	int motion = 1;

	void setRandColor();
};

#endif // #ifndef TPOINT_HPP
