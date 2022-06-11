#include "parallelogram.h"
#include "equals.h"

ostream &operator << (ostream &out, Parallelogram &p )
{
    out << "I am a Parallelogram" << flush;
    return out;
}

istream &operator >> (istream &in, Parallelogram &p)
{
    p.read(in); 
    return in; 
}

Parallelogram::Parallelogram(Point &a1, Point &b1, Point &c1, Point &d1)
{
    _a.setAll(a1.getX(), a1.getY()); 
    _b.setAll(b1.getX(), b1.getY()); 
    _c.setAll(c1.getX(), c1.getY()); 
    _d.setAll(d1.getX(), d1.getY()); 
    lengths[0] = _a.distance(_b); 
    lengths[1] = _b.distance(_c); 
    lengths[2] = _c.distance(_d); 
    lengths[3] = _d.distance(_a); 
}

void Parallelogram::setDefault(void) 
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

Parallelogram::Parallelogram(void)
{
    setDefault(); 
}

void Parallelogram::validate()
{   
    slopes[0] = _a.slope(_b); 
    slopes[1] = _b.slope(_c); 
    slopes[2] = _c.slope(_d); 
    slopes[3] = _d.slope(_a); 
    if (equals(slopes[0], slopes[2]) && equals(slopes[1], slopes[3]))
    {
        return; 
    }
    setDefault(); 
}
// A parallelogram is a quadrilateral with both pairs of sides parallel. Area is base * height.

double Parallelogram::perimeter()
{
    double sum = 0;
    for (int i = 0; i < 4; i++)
    {
        sum += lengths[i]; 
    }
    return sum; 
}

double Parallelogram::area()
{
    return _a.distance(_b) * _b.distance(_c);
}