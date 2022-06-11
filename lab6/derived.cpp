#include <iostream>

using namespace std;

class Base {

    protected:
        int _x; 
    public: 
        virtual void print()
        {
            cout << "Base class called!" << endl; 
        }
};

class Derived : public Base
{

    public: 
        void print()
        {
            cout << "Derived class called!" << endl; 
        }
};

int main ()
{
    Base *ptr;
    Base a; 
    Derived d; 

    ptr = &d; 
    d.print(); 
    cout << "--------\n"; 

    ptr->print(); //if it is virtual, it calls "derived class." 
    //if it is not virtual, it calls "base class" << endl; 
    cout << "--------\n"; 
    // a.print(); 

    // cout << "\\\\fdsfsf--=-=f=-df=-f=\n"; 

    // d.print(); 

}