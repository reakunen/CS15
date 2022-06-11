//
// TwoDArray.h
//
// Brian Mai
// 4/21/2022
// CSCI-15 Assignment 8
// 2D Array Implementation file
//

#include "TwoDArray.h"

TwoDArray::TwoDArray()
{
    _2n = 10;
    _2a = new MyArray[_2n]; // pointer to the base of 10 MyArray objects
}

TwoDArray::TwoDArray(int rows2d, int rows)
{
    _2n = rows2d;
    _n = rows;
    if (_n <= 0 || _2n <= 0)
    {
        _2n = 10;
        _n = 10;
    }
    _2a = new MyArray[_2n];
    for (int i = 0; i < rows2d; i++)
    {
        _2a[i] = MyArray(_n);
    }
}

int &TwoDArray::At( int rows2d, int rows )
{
    if (rows < 0 || rows >= _2n)
    {
        cout << "Illegal rows, pos = " << rows << endl;
        exit( -1 );
    }
    if( rows2d < 0 || rows2d >= _n )
    {
        cout << "Illegal rows2d, pos = " << rows2d << endl;
        exit( -1 );
    }
    return _2a[rows2d][rows];
}

//virtual destructor
TwoDArray::~TwoDArray()
{
    if( _2a )
    {
        delete[] _2a;
    }
    _2a = nullptr; 
}
MyArray &TwoDArray::operator [](int num)
{
    //TwoDArray[5][1];
    return _2a[num];
}


