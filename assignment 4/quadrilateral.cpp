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
    // in main, if (error), setDefault, print new default values
    if (error) setDefault(); 
    return;
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

Quadrilateral::Quadrilateral()
{
    setDefault(); 
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

void Quadrilateral::read(istream &in)
{
    //S (0, 0 ) (1, 0) (1, 1) (0,1)
    char trash; 
    int a1,b1,c1,d1,e1,f1,g1,h1; 
    in >> trash >> a1 >> trash >> b1 >> trash
       >> trash >> c1 >> trash >> d1 >> trash
       >> trash >> e1 >> trash >> f1 >> trash
       >> trash >> g1 >> trash >> h1 >> trash;
    _a.setAll(a1,b1), _b.setAll(c1,d1), _c.setAll(e1,f1), _d.setAll(g1,h1); 
    validate(); 
    return; 
}

ostream &operator << (ostream &out, Quadrilateral &q )
{
    out << "I am a quadrilateral." << flush;
    return out;
}

istream &operator >> (istream &in, Quadrilateral &q)
{
    q.read(in); 
    return in; 
}

void Quadrilateral::print(ostream &out)
{
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
    double area = 0, mid = _a.distance(_c); 
    //using heron's formula
    double s = (lengths[0] + lengths[1] + mid) / 2;
    double s2 = (lengths[3] + lengths[2] + mid) / 2; 

    double area1 = sqrtf(s * (s-lengths[0]) * (s-lengths[1]) * (s-mid)); 
    double area2 = sqrtf(s2 * (s2-lengths[3]) * (s2-lengths[2]) * (s2-mid)); 

    return area1 + area2; 
}