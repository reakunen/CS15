#ifndef TRAPEZOID_H
#define TRAPEZOID_H
#include "quadrilateral.h"

class Trapezoid : public Quadrilateral
{
    friend ostream &operator << (ostream &out, Trapezoid &t); 
    friend istream &operator >> (istream &in, Trapezoid &t); 
    protected: 
        void validate(); 
        void setDefault();

    public: 
        Trapezoid(); 
        Trapezoid(Point &a1, Point &b1, Point &c1, Point &d1); 
        double area(); 
        double perimeter(); 

};

#endif // TRAPEZOID_H