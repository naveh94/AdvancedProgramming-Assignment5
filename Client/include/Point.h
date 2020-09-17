#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <map>

using namespace std;

class Point
{
    public:
		Point() : x(0), y(0) {}
        Point(int x, int y);
        ~Point();
        int getX() const { return x; }
        int getY() const { return y; }
        bool operator ==(const Point &p) const { return (p.x == x && p.y == y); }
        Point operator +(const Point &p) const { return Point(x + p.x, y + p.y); }
        Point goDirection(string dir);
        friend ostream& operator <<(ostream& out, const Point &b);

    private:
        int x;
        int y;
};

#endif // POINT_H
