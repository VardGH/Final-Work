#include "point.h"
#include "polygon.h"

#include <iostream>

Polygon::Polygon() : m_vertices() {}
Polygon::Polygon(std::vector<Point> points) : m_vertices (points) {}

/*	Uses ray casting to determine whether a point is inside the polygon.
	If a ray cast from the point directly to the right until infinity intersects with the polygon's
	sides an odd number of times, the point is inside, otherwise outside
*/
bool Polygon::is_inside(Point point) {

	// counter to keep track of the number of intersects
	int intersects = 0;

	// loop through all vertices pairs defining the sides of the polygon
	for (unsigned int i = 0, j = m_vertices.size() - 1; i < m_vertices.size(); j = i++) {
		double p1x = m_vertices[i].get_x();
		double p1y = m_vertices[i].get_y();
		double p2x = m_vertices[j].get_x();
		double p2y = m_vertices[j].get_y();
		// If the point is to the right or on top of both vertices, cannot intersect
		if (p1x <= point.get_x() && p2x <= point.get_x()) {
			continue;
		}
		/*	One vertex should be higher, one lower than the point for an intersection to be possible
		 
			Considering edge cases:
			If the y coordinate of the point is the same as vertex with the highest y coordinate,
			an intersection is possible. If same with the lower, not possible.
		*/
		if ((p1y >= point.get_y() && p2y < point.get_y()) || (p2y >= point.get_y() && p1y < point.get_y())) {
			// If both vertices x coordinates are higher than the point's, there will be intersection.
			if (p1x > point.get_x() && p2x > point.get_x()) {
				intersects++;
				continue;
			}
			/*  One vertex is to the left, one to the right of the point.
				Calculate the line going through the vertices and determine if the 
				x coordinate of the line is higher than the point's x at the point's y coordinate,
				there will be intersection.
				Cannot end up here if p1y == p2y so no division with 0.
			*/
			double slope_of_line = (p1x - p2x) / (p1y - p2y);
			double x_of_line_connecting_vertices = slope_of_line * (point.get_y() - p1y) + p1x;
			if (x_of_line_connecting_vertices > point.get_x()) {
				intersects++;
			}
		}
	}
	// Return true (point inside) if odd intersections, false (point outside) if even.
	return (intersects % 2 == 1);
}
