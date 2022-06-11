//
// polymorph.cpp
//
// Keith Mehl
// 11/4/08
// CSCI-15 example program
// Illustrate polymorphism with a simple example
// this shows RTTI - run-time type identification
// to get type from pointer or reference to object
//

#include <iostream>
using namespace std;

#define POLYMORPH
#undef POLYMORPH   // comment this for polymorphism
// uncomment to stop polymorphism

// base class for inheritance chain
class CPolygon
{
protected:
    int width, height;
public:
    void set_values (int a, int b)
    {
        width = a;
        height = b;
    }
#ifdef POLYMORPH
    virtual     // on a line by itself ONLY to let conditional compilation work
#endif
    int area()  // normally you just write "virtual int area()" on one line
    {
        return width * height;
    }
};

// first derived class, override area()
class CRectangle : public CPolygon
{
public:
#ifdef POLYMORPH
    virtual     // on a line by itself only to let conditional compilation work
#endif
    int area ()
    {
        return CPolygon::area();
        // or, just return (width * height);
    }
};

// second derived class, override area() again
class CTriangle : public CPolygon
{
public:
#ifdef POLYMORPH
    virtual
#endif
    int area()
    {
        return CPolygon::area() / 2;
        // or, just return (width * height / 2);
    }
};

int main ()
{
    // three objects, one of each type
    CPolygon poly;
    CRectangle rect;
    CTriangle trgl;
    // now three base class pointers, one pointing to each type object
    CPolygon *ppoly0 = &poly;
    CPolygon *ppoly1 = &rect;
    CPolygon *ppoly2 = &trgl;
    // now three base class references, one referring to each type object
    CPolygon &rpoly0 = poly;
    CPolygon &rpoly1 = rect;
    CPolygon &rpoly2 = trgl;
    // set the values of each
    ppoly0->set_values( 4, 5 );
    ppoly1->set_values( 4, 5 );
    ppoly2->set_values( 4, 5 );
    cout << "Accessing area() by object name\n";
    cout << "poly " << poly.area() << endl;
    cout << "rect " << rect.area() << endl;
    cout << "trg1 " << trgl.area() << endl;
    cout << "Accessing area() by object pointer\n";
    cout << "poly " << ppoly0->area() << endl;
    cout << "rect " << ppoly1->area() << endl;
    cout << "trg1 " << ppoly2->area() << endl;
    cout << "Accessing area() by object reference\n";
    cout << "poly " << rpoly0.area() << endl;
    cout << "rect " << rpoly1.area() << endl;
    cout << "trg1 " << rpoly2.area() << endl;
    return 0;
}
