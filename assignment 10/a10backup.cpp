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
struct Loc 
{
    int rows; 
    int cols; 
}; 

void printMap(char matrix[][COLMAX], int rows, int cols, ostream &out)
{
    int area = rows*cols, c = 0;
    // while (area /= 10)
    // {    
    //     c += 1; 
    // }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            out << matrix[i][j] << flush;
        }
        out << endl; 
    }
    return; 
}

void takeMap(char matrix[][COLMAX], int &rows, int &cols, istream &fin)
{
    fin >> rows >> cols; 
    cout << rows << endl; 
    cout << cols << endl;  
    fin.ignore(9999, '\n');
    int i = 0;  
    while (fin && i < rows)
    {   
        fin.getline(matrix[i++], COLMAX-1, '\n'); 
    }
    return;
}
bool makeMove(char matrix[COLMAX], int rows, int cols, Loc &curr, char p)
{

}
void recursiveSolve(char matrix[][COLMAX], int rows, int cols, Loc &curr, Loc last )
{
    static int tries = 0; 
    /* Place down the first (starting move) */
    static bool first = true, solved = false; 
    if (solved)
        first = true; 
    if (first) 
    {
        matrix[curr.rows][curr.cols] = '#'; 
        first = false, solved = false; 
    }
    /* Move from top, left bottom right, make sure its in bounds */
    if (matrix[curr.rows-1][curr.cols] == ' ' && curr.rows-1 >= 0 )
    {
        last.rows = curr.rows; 
        curr.rows -= 1; 
        matrix[curr.rows][curr.cols] = '#'; 
        recursiveSolve(matrix, rows, cols, curr, last); 
    }
    else if (matrix[curr.rows][curr.cols-1] == ' ' && curr.cols-1 >= 0 )
    {
        last.cols = curr.cols; 
        curr.cols -= 1; 
        matrix[curr.rows][curr.cols] = '#'; 
        recursiveSolve(matrix, rows, cols, curr, last); 
    }
    else if (matrix[curr.rows+1][curr.cols] == ' ' && curr.rows+1 < rows)
    {
        last.rows = curr.rows; 
        curr.rows += 1; 
        matrix[curr.rows][curr.cols] = '#'; 
        if (curr.rows == rows && curr.cols == cols)
        {
            solved = true; 
            return; //check if it has won 
        }
        recursiveSolve(matrix, rows, cols, curr, last); 
    }
    else if (matrix[curr.rows][curr.cols+1] == ' ' && curr.cols+1 < cols)
    {
        last.cols = curr.cols; 
        curr.cols += 1;
        matrix[curr.rows][curr.cols] = '#';  
        if (curr.rows == rows && curr.cols == cols)
        {
            solved = true; 
            return; //check if it has won 
        }
        recursiveSolve(matrix, rows, cols, curr, last); 
    }
    /* If it is unable to move, recursively backtrack */
    printMap(matrix, rows, cols, cout);

    cout << "pos: " <<  curr.rows << "\t" << curr.cols << " is: " << matrix[curr.rows][curr.cols] << endl; 
    matrix[curr.rows][curr.cols] = '@'; // it is a blocked path (dead end)
    curr.rows = last.rows; 
    curr.cols = last.cols; 
    printMap(matrix, rows, cols, cout);

    recursiveSolve(matrix, rows, cols, curr, last); 
    tries++; 
    if (tries == 10) return; 
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
    fin.open("mymaze2.txt");
    fout.open("output.txt"); 
    if (!fin || !fout)
    {
        cout << "Error opening files. Program will end. " << endl;
        return -2; 
    }
    int rows = 0, cols = 0; 
    char matrix[ROWMAX][COLMAX];
    Loc pos = {0, 0}, lpos = {0, 0}; 
    //extract the map 
    fout << "Taking Map" << endl; 
    takeMap(matrix, rows, cols, fin); 
    fout << "Rows: " << rows << "\nColumns: " << cols << endl; 
    printMap(matrix, rows, cols, fout);
    recursiveSolve(matrix, rows, cols, pos, lpos);
    fout << "sus is done. hate" << endl; 
    printMap(matrix, rows, cols, fout);

    fin.close(); 
    fout.close(); 
    return 0; 
}