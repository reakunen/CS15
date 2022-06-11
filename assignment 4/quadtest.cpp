#include "quadrilateral.cpp"
#include "point.cpp" 
#include <iostream> 
#include <fstream>

using namespace std;

int main ()
{   
    ofstream fout;
    ifstream fin; 
    char a; 
    fin.open("in.txt"); 
    fin >> a; 
    fout.open("out.txt"); 
    cout << "Test\n"; 
    Quadrilateral q; 
    Quadrilateral q1; 
    fin >> q; 
    q.print(fout); 
    fin >> a; 
    fin >> q1; 
    q1.print(fout); 
    double sum = q.perimeter();
    cout << "the sum is: " << sum << endl; 
    cout << q.area() << endl; 
    cout << q1.area() << endl; 
    cout << q << endl; 


    fout.close(); 
}