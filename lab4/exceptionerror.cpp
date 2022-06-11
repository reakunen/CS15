#include <exception>
#include <iostream>

using namespace std;

int main ()
{
    int a = 5, b = 0; 

    try 
    {
        if (b == 0)
            throw "Cannot divide by zero."; 
        cout << a/b << endl;  
    }
    catch (const char *d)
    {
        cout << "Error of: " << endl;
        cerr << d << endl;

    }
}