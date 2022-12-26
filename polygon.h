#pragma once
#include "point.h"

#include <vector>

class Polygon
{
public:
	Polygon();
	Polygon(std::vector<Point> points);
	std::vector<Point> m_vertices;
	
	bool is_inside(Point point);
};
