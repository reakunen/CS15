#include <iostream>
#include <fstream>

using namespace std;

int main () {

    ifstream fin; 
    fin.open("a.txt"); 

    int a,b,c; 
    cout << a << b << c << endl; 
    while (fin) 
    {
        fin >> a >> b >> c; 
        cout << a << " " << b << " " << c << endl;
        fin.ignore(); 
        if (fin.fail())
        {
            cout << "Error in data file!" << endl; 
        }
    }
}