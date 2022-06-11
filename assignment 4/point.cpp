//
// point.cpp
//
// Keith Mehl
// 10/29/13
// Implementation of a simple Point class
//

#include <iostream>
#include <cmath>
#include "point.h"
#include "equals.h"

using namespace std;


// print in format ( x, y )
const long double Point::Vertical = 10e100;

ostream &operator << (ostream &out, Point &p )
{
    out << "( " << p._x << ", " << p._y << " )" << flush;
    return out;
}

double Point::getX(void) const 
{
    return _x; 
}

double Point::getY(void) const 
{
    return _y; 
}
// extract from format ( x, y )
istream &operator >> (istream &in, Point &p )
{
    char d;
    in >> d >> p._x >> d >> p._y >> d;
    return in;
}

Point::Point()
{
    _x = _y = 0.0;
}

Point::Point( double x, double y )
{
    setAll(x,y); 
}

void Point::setAll( double x, double y )
{
    _x = x;
    _y = y;
}

//double dis = a.Distance(b); 
double Point::distance( Point &b )
{
    return sqrt( ( ( _x - b._x ) * ( _x - b._x ) ) +
                 ( ( _y - b._y ) * ( _y - b._y ) ) );
}

//double slope = a.slope(b); //from a to b 
double Point::slope(Point &b)
{   
    if (equals(_x, b._x)) //if they are on the same x, infinite thingy
    {
        return Vertical;
    }
    return (b._y - _y / b._x - _x);
    //y2-y1/x2-x1
}