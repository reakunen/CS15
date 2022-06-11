//
// a10.cpp
//
// Brian Mai
// 5/5/2022
// CS15 Assignment 10
// Using recursive backtracking to find the end of a maze
//
#include <iostream>
#include <fstream>
#include <cstring> 

using namespace std;

#define ROWMAX 24
#define COLMAX 81

struct Loc 
{
    int rows; 
    int cols; 
}; 
void printMap(char matrix[][COLMAX], int rows, int cols, ostream &out); 
void takeMap(char matrix[][COLMAX], int &rows, int &cols, istream &fin);
void clearEnds(char matrix[][COLMAX], int rows, int cols);
void recursiveSolve(char matrix[][COLMAX], int rows, int cols, Loc &curr); 

int main(int argc, char** argv)
{
    if (argc != 3) 
    {
        cout << "Usage: "<< argv[0] << " <input.txt> <output.txt> " << endl;
        return -1; 
    }
    ifstream fin; 
    ofstream fout; 
    fin.open(argv[1]);  
    fout.open(argv[2]);  
    if (!fin || !fout)
    {
        cout << "Error opening files. Program will end. " << endl;
        return -2; 
    }
    int rows = ROWMAX, cols = COLMAX; 
    char matrix[ROWMAX][COLMAX]; 
    Loc pos = {0, 0}; 
    takeMap(matrix, rows, cols, fin);

    /* Print map statistics and the solution */
    fout << "Input : " << argv[1]  << '\n'
         << "Output: " << argv[2] << endl; 
    fout << "Rows: " << rows << "\tColumns: " << cols << endl;
    printMap(matrix, rows, cols, fout);
    fout << "================================================\nSolution:\n";
    recursiveSolve(matrix, rows, cols, pos);
    printMap(matrix, rows, cols, fout);
    fin.close();
    fout.close();
    return 0; 
}

void printMap(char matrix[][COLMAX], int rows, int cols, ostream &out)
{
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
    fin.ignore(9999, '\n');
    int i = 0;  
    while (fin && i < rows)
    {
        fin.getline(matrix[i++], COLMAX-1, '\n'); 
    }
    return;
}

void clearEnds(char matrix[][COLMAX], int rows, int cols)
{   /* Gets rid of the @ */ 
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j] == '@')
                matrix[i][j] = ' '; 
        }
    }
    return;
}

void recursiveSolve(char matrix[][COLMAX], int rows, int cols, Loc &curr)
{
    static Loc prevMoves[1000] = {}; 
    static int i = 0; 
    static bool first = true, solved = false; 
    /* Place down the first (starting move) */
    if (first) 
    {
        matrix[curr.rows][curr.cols] = '#'; 
        first = false; 
    }
    /* Check if the maze has ended, clear the @'s */
    if (curr.rows == rows-1 && curr.cols == cols-1)
    {
        clearEnds(matrix, rows, cols);
        solved = true; 
        return; 
    }
    if (solved) 
        return;
    /* Move from top, left bottom right & make sure its in bounds */
    if (matrix[curr.rows-1][curr.cols] == ' ' && curr.rows-1 >= 0)
    {
        prevMoves[i++] = curr; // Saves the previous location before changing
        curr.rows -= 1; 
        matrix[curr.rows][curr.cols] = '#'; 
        recursiveSolve(matrix, rows, cols, curr); 
    }
    else if (matrix[curr.rows][curr.cols-1] == ' ' && curr.cols-1 >= 0 )
    {
        prevMoves[i++] = curr;
        curr.cols -= 1; 
        matrix[curr.rows][curr.cols] = '#';     
        recursiveSolve(matrix, rows, cols, curr); 
    }
    else if (matrix[curr.rows+1][curr.cols] == ' ' && curr.rows+1 < rows)
    {
        prevMoves[i++] = curr;
        curr.rows += 1; 
        matrix[curr.rows][curr.cols] = '#';
        recursiveSolve(matrix, rows, cols, curr); 
    }
    else if (matrix[curr.rows][curr.cols+1] == ' ' && curr.cols+1 < cols)
    {
        prevMoves[i++] = curr;
        curr.cols += 1;
        matrix[curr.rows][curr.cols] = '#';      
        recursiveSolve(matrix, rows, cols, curr); 
    }
    /* If it is unable to move, recursively backtrack */    
    if (!solved)
    {    
        matrix[curr.rows][curr.cols] = '@'; // put dead-end symbol
        recursiveSolve(matrix, rows, cols, prevMoves[--i]); 
    }
    return; 
}