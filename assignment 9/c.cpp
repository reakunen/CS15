//
// struct-ex.cpp
//
// Keith Mehl 11/21/05
// CSCI-14 example program
// Illustrate structs (C++ records)
// Introduce the address-of operator & and pointers
//

#include <iostream>
#include <iomanip>
using namespace std;

// Declare the schema or layout for a DATA struct (does not allocate RAM!)
// This declares a new data type called "DATA", which may be used as you would
// other types to declare variables/parameters or to return from a function
struct DATA
{
   char lastName[25]; // room for a 24-character name, plus one for the '\0'
   char midInitial;
   char firstName[25];
   int age;
   // other fields could be here for address, city/state/zip, other info...
}; // notice the ';' - this is REQUIRED here for the struct declaration.

// illustrate returning a struct from a function
DATA readData( void )
{
   DATA d;
   cout << "Enter name as \"last first mi\" : " << flush;
   // The . operator ("dot" or member-of) says the thing on the left is a
   // struct and the thing on the right is the field of the struct. It
   // evaluates to the field as either an L-value or an R-value.
   cin  >> d.lastName >> d.firstName >> d.midInitial;
   cout << "enter age : " << flush;
   cin  >> d.age;
   return d;
}

// illustrate passing a struct by reference (implicitely by address). The .
// operator works if the left operand is a reference to a struct too.
void updateData( DATA &d )
{
   cout << "Enter name as \"first mi last\" : " << flush;
   cin  >> d.firstName >> d.midInitial >> d.lastName;
   cout << "enter age : " << flush;
   cin  >> d.age;
   return;
}

// illustrate passing a struct by value
void printDataFML( DATA d )
{
   cout << d.firstName << ' ' << d.midInitial << ". " << d.lastName
        << " is " << d.age << " years old.\n" << flush;
   return;
}

// illustrate passing a struct by pointer (explicitly by address)
// in a declaration * "binds left" so the parameter is a "pointer to a DATA"
void printDataLFM( DATA *d )
{
   // the operands of the arrow operator -> are, on the left, a pointer
   // to a struct and, on the right, a fieldname in the struct. It evaluates
   // to the field in the struct which is the 'referent' of the pointer.
   cout << d->lastName << ", " << d->firstName << ' ' << d->midInitial;
   // the operator to get to the struct itself from a pointer to a struct
   // is *, so *d means "the thing pointed to by d".  Then we can use the .
   // operator to get to a field of the struct, like when using a reference.
   // The () are required because the . operator has higher precedence than
   // the * operator.  In an expression, unary * "binds right".
   cout << ". is " << (*d).age << " years old.\n" << flush;
   return;
}

// and some code to drive it all...
int main()
{
   DATA data;
   // Illustrate a 'hole' in the struct.  Note the sizes...
   cout << "Sizes of the:\nstruct         " << sizeof(data)
        << "\nFirst name     " << sizeof(data.firstName)
        << "\nMiddle Initial " << setw(2) << right << sizeof(data.midInitial)
        << "\nLast Name      " << sizeof(data.lastName)
        << "\nAge            " << setw(2) << right << sizeof(data.age) << endl;

   // Return a struct from the function and assign it to local variable data.
   // Assigning a struct to a struct does a byte-by-byte copy of memory
   // for the size of the struct.
   // You may only assign structs of the same type using =
   data = readData();
   // pass variable data to the function by value
   printDataFML( data );
   // pass variable data to the function by reference
   updateData( data );
   // pass address of variable data into the pointer parameter
   printDataLFM( &data );
   return 0;
}
