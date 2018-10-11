#pragma once
#include <vector>

class Point
{
public:
	int y, x;

	Point();

	Point(int Y, int X);

	void operator=(const Point& p);

	Point operator+(const Point& p);

	bool operator==(const Point& p);
};

typedef std::vector<Point> Area;