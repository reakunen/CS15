//
// MyArray.cpp
//
// Keith Mehl
// 10/18/09
// CSCI-15 Example program
// MyArray implementation file - a simple 1-d array class
// modified 4/6/16 to add C++ '11 move constructor and move assignment
//
#include <iostream>
#include <cstdlib>
#include <exception>
#include "myarray.h" // "" on header means "look in current directory first"

// default to an array of 10 integers, fill with 0
MyArray::MyArray()
{
    cout << "In default constructor" << endl;
    int i;
        // new allocates RAM from system heap, [] says allocate an array
    _a = new int[10];
    _n = 10;
    for( i = 0; i < 10; i++ )
    {
        _a[i] = 0;       // initialize array to all 0
    }
}

// allocate array of a size requested by the client if legal, fill with 0
MyArray::MyArray( int num )
{
    cout << "In normal constructor" << endl;
    int i;
    if( num <= 0 ) // if illegal, set to default
    {
        num = 10;
    }
    _a = new int[num];
    _n = num;
    for( i = 0; i < num; i++ )
    {
        _a[i] = 0;       // initialize array to all 0
    }
}

// copy constructor - deep copy
MyArray::MyArray( const MyArray &m ) // MUST be a reference parameter. Why?
{
    cout << "In copy constructor" << endl;
    _a = new int[m._n];
    _n = m._n;
    for( int i = 0; i <m._n; i++ )  // copy all elements
    {
        _a[i] = m._a[i];
    }
}

// move constructor - move data from parameter, don't copy it
// && on parameter means R-value reference, and referent can be changed
MyArray::MyArray( MyArray &&m )
{
    cout << "In move constructor" << endl;
    _a = m._a;
    _n = m._n;
    m._a = NULL;  // NULL pointer in source, it's about to be destructed
}

// destructor - needed to deallocate RAM allocated in constructors
// test vs. NULL is unless array is moved in move constructor or move assignment
MyArray::~MyArray()
{
    cout << "In destructor" << endl;
    if( _a )
    {
        delete[] _a;
    }
}

// get value at position pos
int &MyArray::At( int pos )
{
    try
    {
        if( pos < 0 || pos >= _n )
        {
            throw "index out of bounds"; 
        }
        return _a[pos];
    }
    catch (const char *error)
    {
        cout << error << endl; 
        return _a[pos];

    }
}

// get value at position pos using [] indexing operator
int &MyArray::operator []( int pos )
{
    return At( pos ); // implement as a wrapper around At()
#if 0
    if( pos < 0 || pos >= _n ) // or I could have written it again, but why?
    {
        cout << "Illegal index, pos = " << pos << endl;
        exit( -1 );
    }
    return _a[pos];
#endif // 0
}

// return size, const here means it cannot change self
int MyArray::getSize( void ) const
{
    return _n;
}

// move assignment (R-value reference parameter)
MyArray &MyArray::operator =( MyArray &&rhs )
{
    cout << "In move assignment" << endl;
    if( &rhs == this ) // check for self-assignment!
    {
        return *this;
    }
    if( _a != NULL )
    {
        delete[] _a;   // clear out my data, if any
    }
    _a = rhs._a;    // move rhs's data to me
    _n = rhs._n;    // size is rhs's size
    rhs._a = NULL;  // stop rhs's destructor from destroying me
    return *this;   // allow a = b = c; assignment
}

// deep copy - REQUIRED if allocated RAM is used by object!
// copy assignment
MyArray &MyArray::operator =( MyArray &rhs )
{
    cout << "In copy assignment" << endl;
    int i;
    if( &rhs == this ) // self-assignment?
    {
        return *this;  // if so, don't assign, just return self
    }
    if( rhs._n != _n )   // rhs not the same size as myself?
    {
        delete[] _a;    // clear out my data and reallocate to match
        _a = new int[rhs._n];
        _n = rhs._n;
    }
    for( i = 0; i < rhs._n; i++ )  // copy all elements
    {
        _a[i] = rhs._a[i];
    }
    return *this;      // allow a = b = c; assignment
}