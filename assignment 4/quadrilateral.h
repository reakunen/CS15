#ifndef QUADRILATERAL 
#define QUADRILATERAL

#include <iostream>
#include "point.h"

class Quadrilateral
{
    //you do not get friends in inheritance,
    friend istream &operator >> (istream &in, Quadrilateral &q);
    friend ostream &operator << (ostream &out, Quadrilateral &q);

    protected: 
        Point _a, _b, _c, _d; 
        double slopes[4], lengths[4]; 
        void validate(); 
        void setDefault(); 
    public: 
        //constructors
        Quadrilateral(); 
        Quadrilateral(Point &a1, Point &b1, Point &c1, Point &d1); 

        Point getA(); 
        Point getB(); 
        Point getC(); 
        Point getD(); 

        double perimeter(); //for lengths[]
        double area();

        void read(istream &in); //reading from file
        void print(ostream &out); // has access to protected, for ostream
};


#endif //QUADRILATERAL