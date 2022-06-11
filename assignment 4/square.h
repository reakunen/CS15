#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>
using namespace std; 

#include "quadrilateral.h"

class Square : public Quadrilateral 
{
    friend ostream &operator << (ostream &out, Square &s); 
    friend istream &operator >> (istream &in, Square &s); 

    protected:
        void validate(); 
        void setDefault(); 
    public:  
        Square(); 
        Square(Point &a1, Point &b1, Point &c1, Point &d1); 
        
        double area(); 
        double perimeter(); 
};
#endif // SQUARE_H