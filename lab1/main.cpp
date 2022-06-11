// 
// main.cpp
// 
// Brian Mai
// 1/27/2022
// CS15 Lab
// Answer to the lab 
// 

#include <iostream>

using namespace std;

int mystery1( int a, int b );
int mystery2( int &a, int b );
int mystery3( int a, int &b );
int mystery4( int &a, int &b );
int main1();
int main2();
int main3();
int main4();

int main ()
{
    int a; 
    cout << "- Mystery 1 -" << endl; 
    a = main1(); 
    cout << endl; 
    cout << "- Mystery 2 -" << endl; 
    a = main2(); 
    cout << endl; 
    cout << "- Mystery 3 -" << endl; 
    a = main3(); 
    cout << endl; 
    cout << "- Mystery 4 -" << endl; 
    a =  main4(); 
    cout << endl; 
}
int mystery1( int a, int b )
{
 int c = a + b;
 b = a + c;
 a += c + b;
 cout << "a = " << a << " b = " << b << " c = " << c << endl;
 return a + b + c;
}
int main1()
{
 int a = 2, b = 5, c;
 c = mystery1( b, a );
 cout << "a = " << a << " b = " << b << " c = " << c << endl;
 b = mystery1( a, c );
 cout << "a = " << a << " b = " << b << " c = " << c << endl;
 return 0;
}
int mystery2( int &a, int b )
{
 int c = a + b;
 b = a + c;
 a += c + b;
 cout << "a = " << a << " b = " << b << " c = " << c << endl;
 return a + b + c;
}
int main2()
{
 int a = 2, b = 5, c;
 c = mystery2( b, a );
 cout << "a = " << a << " b = " << b << " c = " << c << endl;
 b = mystery2( a, c );
 cout << "a = " << a << " b = " << b << " c = " << c << endl;
 return 0;
}
int mystery3( int a, int &b )
{
 int c = a + b;
 b = a + c;
 a += c + b;
 cout << "a = " << a << " b = " << b << " c = " << c << endl;
 return a + b + c;
}

int main3()
{
 int a = 2, b = 5, c;
 c = mystery3( b, a );
 cout << "a = " << a << " b = " << b << " c = " << c << endl;
 b = mystery3( a, c );
 cout << "a = " << a << " b = " << b << " c = " << c << endl;
 return 0;
}

int main4()
{
 int a = 2, b = 5, c;
 c = mystery4( b, a );
 cout << "a = " << a << " b = " << b << " c = " << c << endl;
 b = mystery4( a, c );
 cout << "a = " << a << " b = " << b << " c = " << c << endl;
 return 0;
}
int mystery4( int &a, int &b )
{
 int c = a + b;
 b = a + c;
 a += c + b;
 cout << "a = " << a << " b = " << b << " c = " << c << endl;
 return a + b + c;
}

