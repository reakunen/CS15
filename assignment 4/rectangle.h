#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "parallelogram.h"

class Rectangle : public Parallelogram
{
    friend ostream &operator << (ostream &out, Rectangle &r); 
    friend istream &operator >> (istream &in, Rectangle &r); 

    protected:
        void validate(); 
        void setDefault(); 

    public: 
        Rectangle(); 
        Rectangle(Point &a1, Point &b1, Point &c1, Point &d1); 
        double perimeter(); 
        double area(); 

};

#endif // RECTANGLE_H