//
// main.cpp
//
// Brian Mai 
// 4/17/2022
// CSCI-15 Lab 5 
// illustrate template functions and classes
//

#include <iostream>
#include <cmath> 
#include <string> 

using namespace std;

template < typename T > T absVal( const T &a); 
template < class T > T findMin(const T &a, const T &b);
template < class T > T findMax(const T &a, const T &b);
template < class T > T findMin3(const T &a, const T &b, const T &c);
template < class T > T findMax3(const T &a, const T &b, const T &c);

class Compare 
{
    friend ostream &operator << (ostream &out, Compare &t);
    
    private: 
        double _a; 
    public: 
        Compare();          
        Compare(double a); 
        double operator <(Compare &t); // less than 
        double operator >(Compare &t); // greater than
        double lessThan(Compare &t);
        double greaterThan(Compare &t);
        void change(double a); 
};

ostream &operator << (ostream &out, Compare &p )
{
    out << p._a << flush; 
    return out;
}

void Compare::change(double a) 
{
    this->_a = a; 
}

double Compare::lessThan(Compare &t)
{
    return (*this < t); 
}

double Compare::greaterThan(Compare &t)
{
    return (*this > t); 
}

double Compare::operator <(Compare &t) // less than 
{
    return findMin(this->_a, t._a);
}

double Compare::operator >(Compare &t) // greater than 
{
    return findMax(this->_a, t._a); 
}   

/* Constructor */
Compare::Compare(void) 
{
    _a = 0; 
}

Compare::Compare(double a)
{
    _a = a; 
}

int main (int argc, char *argv[])
{
    /* Template functions */ 
    double a = 5, b = 1, c = 15.32, d = -12.39; 
    cout << "Absolute value of d: " << absVal(d) << endl;
    cout << "Absolute value of a: " << absVal(a) << endl;
    cout << "Min between a & b: " << findMin(a, b) << endl;
    cout << "Max between a & b: " << findMax(a, b) << endl;
    cout << "Min between a & b & c: " << findMin3(a,b,c) << endl;
    cout << "Max between a & b & c: " << findMax3(a,b,c) << endl;

    /* Using Compare Methods */ 
    Compare val1(5), val2(10), val3(-5), val4(-23.2), val5(12.12);
    cout << "lessThan method using val1 & val2: " << val1.lessThan(val2) << endl;
    cout << "lessThan method using val3 & val2: " << val3.lessThan(val2) << endl;
    cout << "lessThan method using val4 & val5: " << val4.lessThan(val5) << endl;

    cout << "greaterThan method using val1 & val2: " << val1.greaterThan(val2) << endl;
    cout << "greaterThan method using val3 & val2: " << val3.greaterThan(val2) << endl;
    cout << "greaterThan method using val4 & val5: " << val4.greaterThan(val5) << endl;
    return 0; 
}

/* Template function to return absolute value of any numeric type. */
template < typename T > T absVal( const T &a) 
{
    return a < 0 ? -a : a;
}

/* Template function to find the minimum of 2 numbers */ 
template < class T > T findMin(const T &a, const T &b)
{
    return a < b ? a : b; 
}

/* Template function to find the maximum of 2 numbers */ 
template < class T > T findMax(const T &a, const T &b)
{
    return a > b ? a : b; 
}

/* Template function to find the minimum of 3 numbers */ 
template < class T > T findMin3(const T &a, const T &b, const T &c)
{
    return findMin(findMin(a, b), c);
}

/* Template function to find the maximum of 3 numbers */ 
template < class T > T findMax3(const T &a, const T &b, const T &c)
{
    return findMax(findMax(a, b), c); 
}