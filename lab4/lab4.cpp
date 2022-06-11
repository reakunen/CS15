// 
// lab4.cpp
// 
// Brian Mai
// 4/10/2022
// CS15 Lab 4
// Client for arrays
// 
//

#include <iostream>
#include <cstdlib>
#include "myarray.h"
using namespace std;

void printArray( MyArray &a )
{
    //g++ -o lab4 lab4.cpp myarray.cpp && ./lab4
    int i, ct = 0;
    for( i = 0; i < a.getSize(); i++ )
    {
        cout << a[i];
        if( ++ct == 10 )
        {
            ct = 0;
            cout << endl;
        }
        else
        {
            cout << '\t' << flush;
        }
    }
    if( ct != 0 )
    {
        cout << endl;
    }
    return;
}

// provoke move constructor or assignment
MyArray createByArray( MyArray &ma )
{
    cout << "In createByArray()" << endl;
    MyArray a( ma ); // copy constructor
    a[0] = 2;   // prevent optimizer from optimizing out the local variable
    cout << "End of createByArray(), returning" << endl;
    return a;
}
MyArray createOne( int n )
{
    cout << "In createOne()" << endl;
    MyArray a( n );
    a[0] = 0;
    cout << "Past creating automatic local MyArray in createOne(), returning"
         << endl;
    return a;
}

int main()
{
    MyArray array(30); 
    
    MyArray a1;       // invokes default constructor
    MyArray a2( 30 ); // invokes normal constructor
    MyArray a3 = 50;  // also invokes normal constructor
    MyArray a4(a3);   // invokes copy constructor

    cout << "Creating from return value of function" << endl;
    MyArray a5( createByArray( a2 ) );
    cout << "Printing after createByArray()" << endl;
    printArray( a5 );
    cout << "Assigning from return value of function" << endl;
    MyArray a6;       // invokes default constructor
    a6 = createOne( 6 ); // move assignment
    cout << "Printing after createOne()" << endl;
    printArray( a6 );
    MyArray a7 = MyArray(5);
    system( "pause" );
    a2.At( 5 ) = 10;
    a2.At( 15 ) = 20;
    a2.At( 25 ) = 30;
    a2[12] = 35;
    a2[17] = a2[12] + 5;

    printArray( a1 );
    cout << "\n--------------------" << endl;
    printArray( a2 );
    cout << "\n--------------------" << endl;
    printArray( a3 );
    cout << "\n-------------------- print 3 chosen values" << endl;
    cout << a2.At( 5 ) << ' ' << a2.At( 15 )
         << ' ' << a2.At( 25 ) << endl;
    a2.At(8) = a2.At(5) + a2[25];
    a2.At(18) = a2.At(15);
    a2[28] = a2.At(25);
    cout << "\n-------------------- now assigning a2 = a3" << endl;
    a3 = a2;
    system( "pause" );
    printArray( a2 );
    cout << "\n--------------------" << endl;
    printArray( a3 );
    cout << "\n--------------------" << endl;
    a2 = a1;
    printArray( a2 );
    cout << "\n--------------------" << endl;
    printArray( a1 );
    return 0;
}


// CSCI-15 Lab 4, due 4/12/22
// Take my MyArray class and modify it so that on an invalid index, instead of printing an
// error message and terminating the program, it throws an "index out of bounds" exception
// derived from the base exception class. Create a client that creates a MyArray of at least
// 30 elements, populates it with random integers (remember to seed the random number
// generator appropriately), prints each element in the array, performs a simple sort on the
// elements (using a sort function in the client, not a method) and then prints the elements in
// the array again. Print the elements 10 to a line separated by tabs. Then add a try block,
// and access an element out of the bounds of the array, catching the exception and printing
// its message.