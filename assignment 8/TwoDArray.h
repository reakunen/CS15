//
// TwoDArray.h
//
// Brian Mai
// 4/21/2022
// CSCI-15 Assignment 8
// 2D Array Header
//

#ifndef TWODARRAY_H
#define TWODARRAY_H

#include <iostream>
#include "MyArray.h"
using namespace std;

class TwoDArray : public MyArray
{
    private:
        int _2n;
        MyArray* _2a; //array of pointers to MyArray base.
    public:
        TwoDArray();
        TwoDArray(int, int);
        virtual ~TwoDArray(); //destructor
        MyArray &operator []( int );    // operator [][], equivalent to At( , )
        int &At( int, int );
    
};

#endif // TWODARRAY_H
