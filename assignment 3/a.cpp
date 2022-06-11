#include <iostream>

using namespace std;

struct foo {

    int dog;
    int pop; 
    int a;
    int c; 
};
int main ()
{
    foo structName = {};
    cout << structName.dog << endl; 
        cout << structName.pop << endl; 
    cout << structName.a << endl; 
    cout << structName.c << endl; 

    return 0;

}