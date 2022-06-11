#include <iostream>
#include <cstdlib>      // for standard library function rand(), atol() etc.
#include <cmath>
#include <ctime>
using namespace std;


char *mystrcat(char *p, const char *t)
{
    char *s = p; 
    while (*p)
    {
        p++;
    }
    while ((*p++ = *t++)); 
    return s; 
}

int main ()
{
    //does a random number generator 
    char d[10] = "Hello", a[10] = "ee"; 
    char *ptr = nullptr; 
    ptr = mystrcat(d, a);  
    cout << ptr << endl; 
    srand(time(nullptr)); 

    for (int i = 0; i < 50; i++)
    {
        cout << rand() % 10 + 1 << endl;
    }
    return 0;
}