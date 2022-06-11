#include <iostream>
#include <fstream>

using namespace std;
#define MAX 100

struct Vec
{
    int rows = 0;
    int cols = 0; 
};

void clearEnds(char matrix[][MAX], int rows, int cols)
{
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
void printMap(char matrix[][MAX], int rows, int cols, ostream &out)
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

void makeMove(char matrix[][MAX], Vec &p, int j)
{
    static int moves[4][2] = { {+1, +0}, {0, -1}, {-1, 0}, {0, +1} };
    matrix[p.rows][p.cols] = '#'; 

    if (j == 1)
    {
        p.rows -= 1; 
        matrix[p.rows][p.cols] = '@'; 
    }
    if (j == 2)
    {
        p.cols -= 1; 
        matrix[p.rows][p.cols] = '@'; 

    }
    if (j == 3)
    {
        p.rows += 1; 
        matrix[p.rows][p.cols] = '@'; 
    }
    if (j == 4)
    {
        p.cols += 1; 
        matrix[p.rows][p.cols] = '@'; 
    }
}

int main ()
{
    Vec pos; 
    char matrix[MAX][MAX] = { { ' ' } }; 
    int p = 0; 
    //up left down right 
    while (p != 5)
    {
        cout << "Enter Move (1-4): " << flush; 
        cin >> p; 
        makeMove(matrix, pos, p); 
        printMap(matrix, 10, 16, cout); 
    }

}