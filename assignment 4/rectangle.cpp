#include "rectangle.h"
#include "equals.h"

Rectangle::Rectangle(Point &a1, Point &b1, Point &c1, Point &d1)
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

double Rectangle::perimeter(void)
{   
    double sum = 0;
    for (int i = 0; i < 4; i++)
    {
        sum += lengths[i]; 
    }
    return sum; 
}

void Rectangle::setDefault()
{
    _a.setAll(0, 0); 
    _b.setAll(4, 0); 
    _c.setAll(4, 2); 
    _d.setAll(0, 2); 
    lengths[0] = _a.distance(_b); 
    lengths[1] = _b.distance(_c); 
    lengths[2] = _c.distance(_d); 
    lengths[3] = _d.distance(_a); 
}

double Rectangle::area()
{
    lengths[0] = _a.distance(_b); 
    lengths[1] = _b.distance(_c); 
    lengths[2] = _c.distance(_d); 
    lengths[3] = _d.distance(_a); 

    return (lengths[0] * lengths[1]);
}
//A rectangle is a parallelogram with right angles at all vertices. Area is still base * height.
void Rectangle::validate(void)
{   
    slopes[0] = _a.slope(_b); 
    slopes[1] = _b.slope(_c); 
    slopes[2] = _c.slope(_d); 
    slopes[3] = _d.slope(_a); 

    if (!equals(slopes[1], slopes[3]) || !equals(lengths[1], lengths[3]))
    {
        setDefault(); 
    }
}

Rectangle::Rectangle(void)
{
    setDefault(); 
}