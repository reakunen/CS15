#include "point.cpp"
#include "quadrilateral.cpp"
#include "equals.cpp"

using namespace std;
#include <fstream>
int main ()
{
    ifstream fin; 
    fin.open("input.txt"); 

    cout << "opened " << fin << endl;
    Quadrilateral q; 
    cout << q << endl;
    q.read(fin); 
    cout << q << endl;



}