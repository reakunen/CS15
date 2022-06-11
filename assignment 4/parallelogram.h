#ifndef PARALLELOGRAM_H
#define PARALLELOGRAM_H
#include <iostream>
#include "trapezoid.h"

using namespace std;

class Parallelogram : public Trapezoid
{
    friend istream &operator >> (istream &in, Parallelogram &p);
    friend ostream &operator << (ostream &out, Parallelogram &p);

    protected:
        void validate(); 
        void setDefault(); 
    public:
        Parallelogram(); 
        Parallelogram(Point &a1, Point &b1, Point &c1, Point &d1); 

        double area(); 
        double perimeter(); 

};
#endif 