// 
// a.cpp
// 
// Brian Mai
// 1/20/2021
// CS15 Assignment 1
// Calculates quadratic 
// 

#include <iostream> 
#include <cmath>
#include <fstream> 
#include <iomanip> 
#include <string>

using namespace std;

void showResults (double root1, double root2, ostream &out, bool dataError, int num);
bool errorParsing (double &a, double &b, double &c, istream &in, bool &end);
int doQuadratic (double &root1, double &root2, double &a, double &b, double &c);

int main () 
{
    ifstream fin; 
    ofstream fout; 

    string input, output; 
    cout << "Enter input file: " << flush; 
    cin >> input; 
    cout << "Enter output file: " << flush; 
    cin >> output;

    fin.open(input); 
    fout.open(output); 
    //parse for files;
    if (!fin || !fout) 
    {
        cout << "Error opening files. Program will end." << endl; 
        fin.close(); 
        fout.close();
        return -1; 
    }
    
    double a, b, c, root1, root2, discrim; 
    bool isError = false, end; 
    int num;

    while (fin) 
    {
        isError = errorParsing(a, b, c, fin, end); 
        if (end) break; 
        if (isError) 
        {
            showResults(root1, root2, fout, isError, num); 
            break;
        }
        // if everything is ok, do this 
        num = doQuadratic(root1, root2, a, b, c); 
        showResults(root1, root2, fout, isError, num); 
        
    }

    fin.close(); 
    fout.close(); 
    return 0; 
}

bool errorParsing (double &a, double &b, double &c, istream &in, bool &end)
{
//  The data error you must deal with here is too few values on the line,
//  e.g., the line has a and b values only and no c value
    bool error = false; 
    end = false; 
    // if end of file, end the program 
    if (in.eof()) 
    {
        end =  true; 
        return error; 
    }
    // takes input of coefficients 
        in >> a; 
        
    if (in.eof()) return true; 
        in >> b; 

    if (in.eof()) return true; 
        in >> c; 

    return error; 
}

void showResults (double root1, double root2, ostream &out, bool dataError, int num)
{

    static bool called = false; 

    if (!called) //legend at the top 
    {
        out << "- Quadratic calculator -" << endl; 
        out << " Root 1" << setw(8) << ' ' << "Root 2"<< endl; 
        called = true; 
    }

    if (dataError)
    {
        // if error, do not calculate and just return
        out << "Error in data file." << endl;
        return; 
    }

    switch (num) 
    {
        case 0: 
            out << setprecision(5) << setw(7) << root1 << setw(7) 
                << " " << setw(7) << root2 << endl; 
            break;

        case -1: 
            out << "Error cannot have \"a\" as 0" << endl;
            break;

        case -2: 
            out << "Complex/ imaginary roots" << endl; 
            break; 
    }
    return; 
}

int doQuadratic (double &root1, double &root2, double &a, double &b, double &c)
{
    //if discriminant is negative or a = 0, return error (can't do it)
    if (a == 0) return -1;
    //complex/ imaginary roots, when discriminant is negative 
    if ((pow(b, 2) < (4*a*c))) return -2; 
    
    // returns roots if it is valid
    double discrim = sqrt((pow(b, 2)) - (4 * a * c));
    root1 = ((-b + discrim) / (2*a));
    root2 = ((-b - discrim) / (2*a));
    return 0; 
}