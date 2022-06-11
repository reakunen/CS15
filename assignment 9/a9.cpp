//
// a9.cpp
//
// Brian Mai
// 5/1/2022
// CS15 Assignment 9
// Recursion with multiplication + Exponents
//

#include <iostream>

using namespace std; 

unsigned int multiplication(unsigned int a, unsigned int b)
{
    if (b == 0) return 0; // if x * 0 = 0 
    else if (b == 1) return a; 
    return a + multiplication(a, b - 1); 
}

unsigned int exponentiate(unsigned int a, unsigned int b) 
{
    if (b == 0) return 1; // if x^0 = 1
    return a * exponentiate(a, b - 1);
} 

int main ()
{
    cout << "Exponent Recursion Function \n" << flush; 
    cout << "5^0: " << exponentiate(0, 0) << endl; 
    cout << "5^5: " << exponentiate(5, 5) << endl; 
    cout << "5^2: " << exponentiate(5, 2) << endl; 
    cout << "5^3: " << exponentiate(5, 3) << endl; 
    cout << "9^2: " << exponentiate(9, 2) << endl; 
    cout << "1^1: " << exponentiate(1, 1) << endl; 
    cout << "3^2: " << exponentiate(3, 2) << endl; 
    cout << "2^2: " << exponentiate(2, 2) << endl; 
    cout << "1^2: " << exponentiate(1, 2) << endl; 

    cout << "Multiplication Recursion Function \n" << flush; 
    cout << "0*0: " << multiplication(0, 0) << endl; 
    cout << "5*5: " << multiplication(5, 5) << endl; 
    cout << "5*2: " << multiplication(5, 2) << endl; 
    cout << "5*3: " << multiplication(5, 3) << endl; 
    cout << "9*2: " << multiplication(9, 2) << endl; 
    cout << "1*1: " << multiplication(1, 1) << endl;
    cout << "5*1: " << multiplication(5, 1) << endl;
    cout << "3*2: " << multiplication(3, 2) << endl; 
    cout << "2*2: " << multiplication(2, 2) << endl; 
    cout << "1*2: " << multiplication(1, 2) << endl; 
    return 0; 
}