#include "square.h"
#include "equals.h"

using namespace std;

ostream &operator << (ostream &out, Square &s )
{
    out << "I am a quadrilateral" << flush;
    return out;
}
void Square::validate(void)
{
    //if lengths not equal
    if ( !equals(lengths[0], lengths[1]) && !(equals(lengths[0], lengths[2])) &&
         !(equals(lengths[0], lengths[3])) && !(equals(_a.getX(), _d.getX())) && 
         !(equals(_b.getX(), _c.getX())))
    {
        setDefault(); 
    }
}
istream &operator >> (istream &in, Square &s)
{
    s.read(in); 
    return in; 
}
Square::Square(Point &a1, Point &b1, Point &c1, Point &d1)
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

Square::Square(void)
{
    setDefault(); 
}

void Square::setDefault(void)
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