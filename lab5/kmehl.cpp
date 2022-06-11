//
// template.cpp
//
// Keith Mehl
// 4/23/03
// CSCI-15 Example program
// illustrate template functions
//
#include <iostream>
using namespace std;
#define fmax2(a,b) ((a > b) ? a : b)
// a simple struct to illustrate struct copy using =
struct S1
{
   int a;
   char s[10];
   double d;
};
// Use a template function for a type-independent swap() called exchange()
// This does not actually generate any code now!  All code
// is generated when a type to be exchange()ed is actually supplied
// to an exchange() function invocation. Thus this should be in a header if
// used in multiple files.
// You may replace "typename" inside the <> with "class" -- they are equivalent
template < typename T > void exchange( T &a, T &b )
{
   T t = a;
   a = b;
   b = t;
   return;
}

int main()
{
   char ch1 = 'A', ch2 = 'B';
   int i1 = 5, i2 = 8;
    cout << fmax2(i1, i2) << endl; 
   double d1 = 3.14, d2 = 1.414;
   // struct initializer example: values must match field type and sequence
   S1 s1 = { 5, "Hello!", 5.5 }, s2 = { 8, "Goodbye", 2.345 };

   cout << "Before exchanges,\nch1 is " << ch1 << ", ch2 is " << ch2
        << "\ni1 = " << i1 << ", i2 = " << i2
        << "\nd1 = " << d1 << ", d2 = " << d2
        << "\ns1 is " << s1.a << '\t' << s1.s << '\t' << s1.d
        << "\ns2 is " << s2.a << '\t' << s2.s << '\t' << s2.d << endl;

   exchange( ch1, ch2 ); // or like this: exchange<char>( ch1, ch2 );
   exchange( i1, i2 );   // with the argument type in the <>
   exchange( d1, d2 );
   exchange( s1, s2 );

   cout << "\nAfter exchanges,\nch1 is " << ch1 << ", ch2 is " << ch2
        << "\ni1 = " << i1 << ", i2 = " << i2
        << "\nd1 = " << d1 << ", d2 = " << d2
        << "\ns1 is " << s1.a << '\t' << s1.s << '\t' << s1.d
        << "\ns2 is " << s2.a << '\t' << s2.s << '\t' << s2.d << endl;
   return 0;
}
