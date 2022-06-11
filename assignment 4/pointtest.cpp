#include <iostream>
#include "point.cpp"

using namespace std;

int main ()
{
    Point p(1,15);  
    Point a(5,0); 
    Point one(1,2); 
    Point c; 
    double slop1e = p.slope(one); 
    cout << slop1e << endl; 
    double slopey = p.distance(one); 
    cout << slopey << endl; 
    slopey = p.distance(a); 
    cout << slopey << endl; 
    slopey = c.distance(one); 
    cout << slopey << endl; 
}