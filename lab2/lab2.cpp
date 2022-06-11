//
// lab2.cpp
//
// Brian Mai, Kenneth Duong
// February 3, 2022
// Lab 2
// Matrices + Spiral Program
//

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std; 

#define ROWMAX 15
#define COLMAX 20

void printSpiral(int a[][COLMAX], int rows, int cols, ostream &out);
void makeSpiral(int a[][COLMAX], int row, int col); 
void clearArray(int a[][COLMAX]);

int main () 
{
    //prompt for output file
    ofstream fout; 
    string output; 
    cout << "Enter a output file: " << flush; 
    cin >> output; 
    fout.open(output); 
    //check for error
    if (!fout) 
    {
        cout << "Failed to open: " << output << ".\n" 
             << "Program will now end." << endl;
        return -1; 
    }
    //initializes all elements to 0 in array
    int spiral[ROWMAX][COLMAX] = { { 0 } }; 
    //sizes is the combinations for the matrix (ragged array)
    const int sizes[20][2] = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, 
                              {5, 5}, {4, 7}, {7, 4}, {3, 8}, 
                              {8, 3}, {15, 20}, {6,5}, {5,6}, 
                              {7,9}, {15, 15}, {1,2}, {0, 0}, 
                              {1,20}, {5,15}, {2,20}, {1,0}};
    //Print the output by loop  
    fout << "Output File: " << output << '\n' << endl; 
    for (int i = 0; i < 20; i++)
    {
        fout << "Size: " << sizes[i][0] << " by " << sizes[i][1] << endl;
        makeSpiral(spiral, sizes[i][0], sizes[i][1]);
        printSpiral(spiral, sizes[i][0], sizes[i][1], fout); 
        clearArray(spiral); 
    }
    fout.close(); 
    return 0; 
}

void clearArray(int a[][COLMAX])
{
    for (int i = 0; i < ROWMAX; i++)
    {
        for (int j = 0; j < COLMAX; j++)
        {
            a[i][j] = 0; 
        }
    }
    return; 
} 

void printSpiral(int a[][COLMAX], int rows, int cols, ostream &out)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            out << setw(3) << a[i][j] << ' ' << flush;
        }   
        out << endl; 
    } 
    out << '\n' << endl;
    return;       
}

void makeSpiral(int a[][COLMAX], int row, int col)
{   
    int ct = 0, max = row * col, 
        top = 0, bottom = row-1, 
        left = 0, right = col-1;  
    
    while (ct < max)
    {
        for (int i = left; i <= right; i++)
        {
            if (a[top][i] != 0) break;
            a[top][i] = ++ct; 
        }
        top++; 

        for (int i = top; i <= bottom; i++)
        {
            if (a[i][right] != 0) break;
            a[i][right] = ++ct;
        }
        right--; 

        for (int i = right; i >= left; i--)
        {
            if (a[bottom][i] != 0) break;
            a[bottom][i] = ++ct;
        }
        bottom--; 

        for (int i = bottom; i >= top; i--)
        {
            if (a[i][left] != 0) break;
            a[i][left] = ++ct; 
        }
        left++; 
    }
    return; 
}