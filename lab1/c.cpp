#include <iostream>
#include <cmath> 
using namespace std;

bool equals(double a, double b)
{
    if (fabs(a - b) < pow(10, -12))
    {
        return true;
    }
    return false;
}
int main () 
{
    long int vec = pow(10, 100); 
    if (equals(vec, vec))
    {
        cout << "true" << endl; 
    }
}