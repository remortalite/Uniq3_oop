#ifndef TPOINT_HPP
#define TPOINT_HPP

#include "tFigure.hpp"

class tPoint : public tFigure
{
public:
    tPoint();
	tPoint(int x, int y);

private:
	int motion = 1;
};

class tLine : public tFigure
{
public:
	tLine();
	tLine(int x, int y);

private:
};

#endif // #ifndef TPOINT_HPP
