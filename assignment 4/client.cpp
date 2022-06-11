#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>

using namespace std;

#include "quadrilateral.cpp"
#include "trapezoid.cpp"
#include "parallelogram.cpp"
#include "rectangle.cpp"
#include "square.cpp"
#include "equals.cpp"
#include "point.cpp"

int main (int argc, char *argv[])
{
    cout << "working" << endl; 
    //g++ -o client client.cpp quadrilateral.cpp trapezoid.cpp parallelogram.cpp rectangle.cpp square.cpp && ./client
    if (argc != 3)
    {
        cout << "Usage: <client>\t <input>\t <output>\n"; 
        return -1; 
    }

    ifstream fin;
    fin.open(argv[1]); 
    ofstream fout;
    fout.open(argv[2]);

    if (!fin || !fout) 
    {
        cout << "Error opening files.\n"; 
        return -2; 
    }
    char type; 
    Quadrilateral q; 
    Trapezoid t; 
    Parallelogram p;
    Rectangle r; 
    Square s; 
    while (fin)
    {
        fin >> type;
        switch (type)
        {
            case 'Q':
                    fout << q << endl;
                    q.print(fout); 
                    fout << "Area:      " << q.area() << endl;
                    fout << "Perimeter: " << q.perimeter() << endl;
                break;
            case 'T':
                    fout << q << endl;
                    q.print(fout); 
                    fout << "Area:      " << q.area() << endl;
                    fout << "Perimeter: " << q.perimeter() << endl;
                break;
            case 'P':
                    fout << p << endl;
                    p.print(fout); 
                    fout << "Area:      " << p.area() << endl;
                    fout << "Perimeter: " << p.perimeter() << endl;
                break;
            case 'R': 
                    fout << r << endl;
                    r.print(fout); 
                    fout << "Area:      " << r.area() << endl;
                    fout << "Perimeter: " << r.perimeter() << endl;
                break;
            case 'S': 
                    fout << s << endl;
                    s.print(fout); 
                    fout << "Area:      " << s.area() << endl;
                    fout << "Perimeter: " << s.perimeter() << endl;
                break;
        }
    }
    fin.close();
    fout.close(); 
    return 0; 
}