#include "../include/Point.h"

Point::Point(int x, int y) : x(x), y(y)
{}

Point::~Point()
{}


ostream &operator <<(ostream &out, const Point &b)
{
    out << "(" << b.getX() << "," << b.getY() << ")";
    return out;
}

Point Point::goDirection(string dir) {
	map<string, Point> direction;
	direction["n"] = Point(0, -1);
	direction["ne"] = Point(1, -1);
	direction["e"] = Point(1, 0);
	direction["se"] = Point(1, 1);
	direction["s"] = Point(0, 1);
	direction["sw"] = Point(-1, 1);
	direction["w"] = Point(-1, 0);
	direction["nw"] = Point(-1, -1);
	return Point(x, y) + direction[dir];
}
