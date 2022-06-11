#include <iostream>
#include <exception>
#include <ctime> 
#include "myarray.cpp"

using namespace std;

void swap(MyArray &a, MyArray &b)
{
    MyArray temp = a;
    a = b; 
    b = temp; 
}

void bubbleSort(MyArray arr, int n)
{
    int i, j;
    for (i = 0; i < n-1; i++)  
    {
        for (j = 0; j < n-1; j++)
        {
            if (arr[j] > arr[j+1])
            {
                swap(arr[j], arr[j+1]); 
            }
        }
    }  
    return;
}
void printArray ( MyArray &a ); 
// Create a client that creates a MyArray of at least
// 30 elements, populates it with random integers (remember to seed the random number
// generator appropriately), prints each element in the array, performs a simple sort on the
// elements (using a sort function in the client, not a method) and then prints the elements in
// the array again. Print the elements 10 to a line separated by tabs. Then add a try block,
// and access an element out of the bounds of the array, catching the exception and printing
// its message.
int main ()
{
    srand(atol(nullptr)); 
    MyArray arr(30); 
    for (int i = 0; i < 30; i++)
    {
        int x = rand() % 100 + 1; 
        arr[i] = x; 
    }
    printArray(arr); 
    return 0; 
}

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