//
// a10.cpp
//
// Brian Mai
// 5/5/2022
// CS15 Final Assignment
// Using recursive backtracking to find the end of a maze
//

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;
#define ROWMAX 24
#define COLMAX 81

//pseudocode: make a struct made out of the vec rows and cols.
// will be used to
struct Player
{
    int rows;
    int cols;
};

//bool recursiveMove(char *matrix[]);
void printMap(char matrix[][COLMAX], int rows, int cols, ostream &out)
{
    int area = rows*cols, c = 2;
    while (area /= 10)
    {
        c += 1;
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            out << setw(c) << matrix[i][j] << " " << flush;
        }
        out << endl;
    }
    return;
}
void takeMap(char matrix[][COLMAX], int &rows, int &cols, istream &fin)
{
    fin >> rows >> cols;
    fin.ignore();
    int i = 0;
    while (!fin.eof())
    {
        fin.getline(matrix[i], cols, '\n');
        cout << matrix[i] << endl;
    }
}

int main (int argc, char** argv)
{
    // if (argc != 3)
    // {
    //     cout << "Usage: "<< argv[0] << " <input.txt> <output.txt> " << endl;
    //     return -1;
    // }
    ifstream fin;
    ofstream fout;
    // fin.open(argv[1]);
    // fout.open(argv[2]);
    fin.open("/Users/brianmai/Documents/csci15/assignment 10/assign10/assign10/input.txt");
    fout.open("/Users/brianmai/Documents/csci15/assignment 10/assign10/assign10/output.txt");
    if (!fin || !fout)
    {
        cout << "Error opening files. Program will end. " << endl;
        return -2;
    }
    int rows = ROWMAX, cols = COLMAX;
    char matrix[ROWMAX][COLMAX];
    Player p = {0, 0};
    fout << "Rows: " << rows << "\nColumns: " << cols << endl;
    //extract the map
    takeMap(matrix, rows, cols, fin);
    printMap(matrix, rows, cols, fout);
    
    fin.close();
    fout.close();
    return 0;
}
