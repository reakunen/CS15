#include "trapezoid.h"
#include "equals.h"

ostream &operator << (ostream &out, Trapezoid &t)
{
    out << "I am a trapezoid" << flush;
    return out;
}

istream &operator >> (istream &in, Trapezoid &t)
{
    t.read(in); 
    return in; 
}

void Trapezoid::validate(void) 
{
    lengths[0] = _a.distance(_b); 
    lengths[1] = _b.distance(_c); 
    lengths[2] = _c.distance(_d); 
    lengths[3] = _d.distance(_a); 
    //if they are not equal slopes
    if (!(equals(lengths[0], lengths[2])))
    {
        setDefault(); 
    }
}

double Trapezoid::perimeter(void)
{   
    double sum = 0;
    for (int i = 0; i < 4; i++)
    {
        sum += lengths[i]; 
    }
    return sum; 
}

/*A trapezoid is a quadrilateral with exactly ONE pair of parallel sides (either pair of opposite
sides). For this program, you may assume the base and the top are the parallel sides. An easy
way to get its area is ((base + top) / 2) * height. */
double Trapezoid::area(void)
{
    lengths[0] = _a.distance(_b); 
    lengths[1] = _b.distance(_c); 
    lengths[2] = _c.distance(_d); 
    lengths[3] = _d.distance(_a); 
    double sum = this->perimeter();
    double height = _c.getY() - _b.getY(); 
    return (((lengths[0] + lengths[2]) / 2) * height); 
}

void Trapezoid::setDefault(void) 
{
    
    _a.setAll(0, 0); 
    _b.setAll(0, 5); 
    _c.setAll(4,5); 
    _d.setAll(1, 5); 
    lengths[0] = _a.distance(_b); 
    lengths[1] = _b.distance(_c); 
    lengths[2] = _c.distance(_d); 
    lengths[3] = _d.distance(_a); 
}

Trapezoid::Trapezoid()
{
    setDefault(); 
}

Trapezoid::Trapezoid (Point &a1, Point &b1, Point &c1, Point &d1)
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

