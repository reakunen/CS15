//
// MyArray.h
//
// Keith Mehl
// 10/18/09
// CSCI-15 Example program
// a simple int 1-d array class
// modified 4/6/16 to add C++ '11 move constructor and move assignment
//

#ifndef MYARRAY_H  // header sandwich - prevent multiple inclusion
#define MYARRAY_H

#include <iostream>
using namespace std;

class MyArray
{
private:
    int *_a;     // holds the base of the array of ints
    int _n;      // the number of elements in the array
public:
    MyArray();                      // default constructor
    MyArray( int num );             // normal constructor
    MyArray( const MyArray &m );    // copy constructor
    MyArray( MyArray &&m );         // move constructor, R-Value Reference
    ~MyArray();                     // destructor
    int &At( int pos );             // get value at position pos
    int &operator []( int pos );    // operator [], equivalent to At()
    int getSize( void ) const;      // return number of elements in the array
    MyArray &operator =( MyArray &&rhs ); // move assignment
    MyArray &operator =( MyArray &rhs );  // copy assignment (deep copy)
};

#endif