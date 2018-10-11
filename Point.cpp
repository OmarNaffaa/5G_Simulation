#include "Point.h"

Point::Point()
{
	y = 0;
	x = 0;
}

Point::Point(int Y, int X)
{
	y = Y;
	x = X;
}

void Point::operator=(const Point& p)
{
	y = p.y;
	x = p.x;
}

Point Point::operator+(const Point& p)
{
	Point addp = { this->y + p.y,this->x + p.x };
	return addp;
}

bool Point::operator==(const Point& p)
{
	if (this->x == p.x && this->y == p.y)
		return true;
	else
		return false;
}

