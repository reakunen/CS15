//
// main.cpp
//
// Brian Mai
// 3/07/2022
// CS15 Assignment 3
// Illustrate a mouse's survivability in a certain
// map using srand() random generator & seeding
// Modified on 4/22/2022 to include 2D array class
//

#include <cmath>
#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

#include "MyArray.h"
#include "TwoDArray.h"
using namespace std;

struct Mouse
{
    int row;
    int col;
    int totalMoves;
    int drowned;
    int starved;
    int escaped;
};

void takeExits(Mouse exit[], TwoDArray &map, int rows, int cols);
int mouseMove (Mouse &mouse, Mouse exit[], TwoDArray &map, TwoDArray &moves);
void printMap(TwoDArray &map, int rows, int cols, ofstream &fout);
void takeMap(Mouse &mouse, TwoDArray &map, int rows, int cols, ifstream &fin);

int main (int argc, char* argv[])
{
    //g++ -o main main.cpp MyArray.cpp TwoDArray.cpp && ./main input.txt output.txt 100
    /* Parsing for files through command line arguments */
    ifstream fin;
    ofstream fout;
    if (argc < 3 || argc > 5)
   {
       cout << "Usage: " << argv[0] << " input.txt output.txt seed "
            << " (Seed number is optional)" << endl;
       return 0;
   }

   fin.open(argv[1]);
   fout.open(argv[2]);
   fout << setfill('-') << setw(44) << '-' << setfill(' ') << endl;
   fout << "Input: " << argv[1] << "\t\t Output: " << argv[2] << endl;

   if (!fout || !fin)
   {
       cout << "Error opening files. Program will end." << endl;
       return -1;
   }
   /* See if the user inputting argument counts correctly & seed */
   if (argc == 4)
   {
       fout << "Seeded with: " << argv[3] << endl;
       fout << setfill('-') << setw(44) << '-' << setfill(' ') << endl;
       srand(atoi(argv[3]));
   }
   else
   {
       fout << "No seed" << endl;
       fout << setfill('-') << setw(44) << '-' << setfill(' ') << endl;
       srand(time(nullptr));
   }

    /* Initialize variables */
    // int matrix[20][20] = { { 0 } }, moves[20][20] = { { 0 } };
    int rows = 0, cols = 0, mouseAlive = 0;
    fin >> rows >> cols;          // take in rows and cols
    
    Mouse mouse = {}, originalLocation = {}, exit[2] = {};
    TwoDArray matrix(rows, cols);
    TwoDArray moves(rows, cols);
    /* Take input of map and set mouse's initial location */
    takeMap(originalLocation, matrix, rows, cols, fin);
    takeExits(exit, matrix, rows, cols);
    printMap(matrix, rows, cols, fout);
    fout << setfill('-') << setw(44) << '-' << setfill(' ') << endl;

    /* Loop over 100 lives and see how the mouse does */
    for (int i = 1; i < 101; i++)
    {
        //reset for the next mouse's life
        mouse.row = originalLocation.row;
        mouse.col = originalLocation.col;
        mouse.totalMoves = 0;
        mouseAlive = 0;
        //while mouse is still alive, keep moving
        while (mouseAlive == 0)
        {
            mouseAlive = mouseMove(mouse, exit, matrix, moves);
        }

        if (mouseAlive == -1)
        {
            //mouse has drowned
            fout << "Mouse " << i << " drank too much water." << endl;
        }
        if (mouseAlive == -2)
        {
            //mouse has starved
            fout << "Mouse " << i << " forgot to eat breakfast today..." << endl;

        }
        if (mouseAlive == -3)
        {
            //mouse has escaped
            fout << "Mouse " << i << " has immigrated to Canada!" << endl;
        }
        //reset mouse location & everything for next life
    }

    /* Prints the statistics and move count map */
    fout << setfill('-') << setw(44) << '-' << setfill(' ') << endl;
    fout << "Statistics over the lives of 100 unfortunate mice: "<< endl;
    fout << "Total Mice Drowned: " << mouse.drowned << endl;
    fout << "Total Mice Starved: " << mouse.starved << endl;
    fout << "Total Mice Escaped: " << mouse.escaped << endl;
    fout << setfill('-') << setw(44) << '-' << setfill(' ') << endl;
    fout << "Mice move counts: " << endl;
    printMap(moves, rows, cols, fout);
    fout << setfill('-') << setw(44) << '-' << setfill(' ') << endl;

    fout.close();
    fin.close();
    cout << "Program finished running." << endl; 
    return 0;
}

/* mouseMove is used to determine where the mouse walks to using rand() to
 * have an arbitrary location. Return value is an int which determines if the
 * mouse has fallen in the water, drowned, or escaped. */
int mouseMove (Mouse &mouse, Mouse exit[], TwoDArray &matrix, TwoDArray &moves)
{
    int r = rand() % 4;       // from 0 - 3
    static const int Direction[4][2] = { {0, -1}, {+1, 0}, {0, +1}, {-1, 0} };

    mouse.row += Direction[r][0];
    mouse.col += Direction[r][1];
    moves[mouse.row][mouse.col] += 1;
    mouse.totalMoves += 1;

    if (matrix[mouse.row][mouse.col] == -1) //return
    {
        //mouse is dead (drowned)
        mouse.drowned += 1;
        return -1;
    }
    else if (mouse.totalMoves > 100) //will return at a hundred moves
    {
        //mouse has starved
        mouse.starved += 1;
        return -2;
    }

    for (int i = 0; i < 2; i++)
    {
        if (mouse.row == exit[i].row && exit[i].col == mouse.col)
        {
            //mouse has escaped
            mouse.escaped += 1;
            return -3;
        }
    }
    return 0; //if mouse is alive (return 0), just moved
}

/* printMap prints the map, first sees how large the map's characters between
 * each letter is by diving the max area by 10 to find digits of 10's */
void printMap(TwoDArray &map, int rows, int cols, ofstream &fout)
{
    int num = 1, max = rows*cols;

    while (max /= 10)   // Divides until it is 0 (false)
    {
        num += 1;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fout << setw(num) << map[i][j] << ' ' << flush;
        }
        fout << '\n';
    }
    return;
}

/* takeExits takes in the map's bridge locations. The loops only cover
 * the outside (perimeter of the map) to find the bridge locations.
 * Then it stores the bridge location in a struct, in rows and cols */
void takeExits(Mouse exit[], TwoDArray &map, int rows, int cols)
{
    int amt = 0;
    // up to down
    for (int i = 0; i < rows; i++)
    {
        if (map[i][0] == 0)
        {
            exit[amt].row = i;
            exit[amt].col = 0;
            amt += 1;
        }
        if (map[i][cols-1] == 0)
        {
            exit[amt].row = i;
            exit[amt].col = cols-1;
            amt += 1;
        }
    }
    // left to right i = 1 so it doesn't redo spot
    for (int i = 1; i < cols-1; i++)
    {
        if (map[0][i] == 0)
        {
            exit[amt].row = 0;
            exit[amt].col = i;
            amt += 1;
        }
        if (map[rows-1][i] == 0)
        {
            exit[amt].row = rows-1;
            exit[amt].col = i;
            amt += 1;
        }
    }
    return;
}

/* takeMap is a function that reads from the input file and takes in rows and
 * columns. Then it assigns the mouse's initial location into a struct when
 * the mouse's location is found (integer 1). */
void takeMap(Mouse &mouse, TwoDArray &map, int rows, int cols, ifstream &fin)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fin >> map[i][j];
            if (map[i][j] == 1)   // take input on the mouse's location
            {
                mouse.totalMoves = 0;
                mouse.row = i;
                mouse.col = j;
            }
        }
    }
    return;
}
