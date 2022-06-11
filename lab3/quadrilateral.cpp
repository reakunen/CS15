#include "quadrilateral.h"
#include <cmath>
#include <iostream>

using namespace std;

void Quadrilateral::validate()
{
    bool error = false;
    if (_a.getX() > _b.getX()) error = true;
    if (_b.getY() > _c.getY()) error = true;
    if (_c.getX() < _d.getX()) error = true;
    if (_d.getY() < _a.getY()) error = true;
    //
    //
    //
    // d(0,1)        c (1,1)
    // a(0,0)        b (1,0)
    // in main, if (error), setDefault, print new default values
    if (error) setDefault();
    return;
}
Quadrilateral::Quadrilateral()
{
    this->setDefault();
}
// 1x1 box, default
void Quadrilateral::setDefault()
{
    _a.setAll(0,0);
    _b.setAll(1,0);
    _c.setAll(1,1);
    _d.setAll(0,1);
    lengths[0] = _a.distance(_b);
    lengths[1] = _b.distance(_c);
    lengths[2] = _c.distance(_d);
    lengths[3] = _d.distance(_a);
}

//constructor
Quadrilateral::Quadrilateral(Point &a1, Point &b1, Point &c1, Point &d1)
{
    lengths[0] = _a.distance(_b);
    lengths[1] = _b.distance(_c);
    lengths[2] = _c.distance(_d);
    lengths[3] = _d.distance(_a);
    _a.setAll(a1.getX(), a1.getY());
    _b.setAll(b1.getX(), b1.getY());
    _c.setAll(c1.getX(), c1.getY());
    _d.setAll(d1.getX(), d1.getY());
}
void Quadrilateral::setPoints(Point &a1, Point &b1, Point &c1, Point &d1)
{
    _a = a1;
    _b = b1;
    _c = c1;
    _d = d1;
    this->validate();
}


void Quadrilateral::read(istream &in)
{
    //S (0, 0 ) (1, 0) (1, 1) (0,1)
    char trash;
    double a1,b1,c1,d1,e1,f1,g1,h1;
    in >> trash >> a1 >> trash >> b1 >> trash
       >> trash >> c1 >> trash >> d1 >> trash
       >> trash >> e1 >> trash >> f1 >> trash
       >> trash >> g1 >> trash >> h1 >> trash;
    Point a(a1,b1), b(c1,d1), c(e1,f1), d(g1,h1); // trash
    this->setPoints(a, b, c, d);

//    this->_a.setAll(a1, b1);
//    this->_b.setAll(c1, d1);
//    this->_c.setAll(e1, f1);
//    this->_d.setAll(g1, h1);
    return;
}
Point Quadrilateral::getA()
{
    return _a;
}
Point Quadrilateral::getB()
{
    return _b;
}
Point Quadrilateral::getC()
{
    return _c;
}
Point Quadrilateral::getD()
{
    return _d;
}
ostream &operator << (ostream &out, Quadrilateral &q )
{
    q.print(out);
    return out;
}

istream &operator >> (istream &in, Quadrilateral &q)
{
    q.read(in);
    return in;
}

void Quadrilateral::print(ostream &out)
{
    out << "I am a Quadrilateral\n" << flush;

    out << "( " << _a.getX() << ", " << _a.getY() << " )"
        << "( " << _b.getX() << ", " << _b.getY() << " )"
        << "( " << _c.getX() << ", " << _c.getY() << " )"
        << "( " << _d.getX() << ", " << _d.getY() << " )" << flush;
    return;
}

double Quadrilateral::perimeter(void)
{
    double sum = 0;
    for (int i = 0; i < 4; i++)
    {
        sum += lengths[i];
    }
    return sum;
}

double Quadrilateral::area(void)
{
    double mid = _a.distance(_c);
    //using heron's formula
    double s = (lengths[0] + lengths[1] + mid) / 2;
    double s2 = (lengths[3] + lengths[2] + mid) / 2;

    double area1 = sqrtf(s * (s-lengths[0]) * (s-lengths[1]) * (s-mid));
    double area2 = sqrtf(s2 * (s2-lengths[3]) * (s2-lengths[2]) * (s2-mid));

    return area1 + area2;
}
