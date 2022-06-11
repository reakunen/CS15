//
// maze.cpp
// Doga Ozkaracaabatlioglu
// December 5, 2018
// Assignment 8
// reads a maze from a text file into an array, prints the unsolved maze,
// solves the maze, and then prints the solution.
// @ - Represents impasse
// # - Trace/Solution
// * - Walls
//

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <fstream>
#include <iomanip>

using namespace std;

struct arrayLoc
{
    int x = 0; // C++11 
    int y = 0; // C++11
};

void clearArray(char arr[24][81]);
void printArray(char arr[][81], int map_sizeX, int map_sizeY, ostream &out);
bool isInBounds(int go[4][2], int i, int map_sizeX, int map_sizeY,
                arrayLoc &curLocation);
void solveMaze(char arr[][81], int map_sizeX, int map_sizeY,
               arrayLoc &curLocation, arrayLoc last_pos);


int main(int argc, char *argv[])
{
    // Parse Command Line Parameters
    if (argc < 2)
    {
        cout << "Error. Please run the program like: "
             << "this_program input_map_file.txt "
             << "output_file.txt" << endl;
        return -1;
    }
    // Open Files
    ifstream fin;
    ofstream fout;
    fin.open(argv[1]);
    fout.open(argv[2]);
    fin >> noskipws; // Don't skip whitespace.
    // Check for open failure.
    if( !fin || !fout )
    {
       cout << "Input or output file open failed\n";
       return -2;
    }
    //read the map && save initial position of the mouse and bridges
    int map_sizeX = 0, map_sizeY = 0;
    char temp = ' ', the_map[24][81], solution_map[24][81];
    arrayLoc curLocation, startingPoint, endingPoint;
    clearArray(the_map);
    clearArray(solution_map);
    fin >> map_sizeY;
    fin.ignore();
    fin >> map_sizeX;
    fin.ignore();
    //Reading the map into array
    for (int cur_y=0;cur_y < map_sizeY;cur_y++)
    {
        for (int cur_x=0;cur_x < map_sizeX;cur_x++)
        {
        fin >> temp;
        the_map[cur_x][cur_y] = temp;
        solution_map[cur_x][cur_y] = temp;
        }
        fin.ignore();
      
    }
    fin.close(); // Map is read, so close the input file.

    // Placing starting point marker on the map
    solution_map[startingPoint.x][startingPoint.y] = '#';

    // Now solve by using solution map...
    solveMaze(solution_map, map_sizeX, map_sizeY, startingPoint, startingPoint);

    //print the everything
    fout << "@ - Impasse (backtracked for solution)\n"
         << "# - Trace/Solution \n* - Walls" << endl;
    fout << "Supplied Parameters:" << endl;
    for (int i=0;i<argc;i++)
    {
        fout << i << " : " << argv[i] << endl;
    }
    fout << "Input File: " << argv[1] << endl;
    fout << "Output File: " << argv[2] << endl;
    fout << "Map: " << endl;
    printArray(the_map, map_sizeX, map_sizeY, fout);
    fout << "Solution Map: " << endl;
    printArray(solution_map,map_sizeX,map_sizeY, fout);
    fout.close();
    return 0;
}
void clearArray(char arr[24][81])
{
    for(int i=0;i<24;i++)
        for (int j=0;j<81;j++)
            arr[i][j] = ' ';
}
void printArray(char arr[][81], int map_sizeX, int map_sizeY, ostream &out)
{
    int limit = (map_sizeX*map_sizeY);
    int n = 0;
    while (limit /= map_sizeX)
        n++;

    for (int cur_y=0;cur_y < map_sizeY;cur_y++)
    {
        for (int cur_x=0;cur_x < map_sizeX;cur_x++)
            out << setw(n+1) << arr[cur_x][cur_y] << flush;
        out << endl;
    }
}
bool isInBounds(int go[4][2], int i, int map_sizeX, int map_sizeY, arrayLoc &curLocation)
{
    return (curLocation.x+go[i][0] <= map_sizeX &&
             curLocation.y+go[i][1] <= map_sizeY) ? true : false;
}

void solveMaze(char arr[][81], int map_sizeX, int map_sizeY, arrayLoc &curLocation, arrayLoc last_pos)
{
     // up, right, down, left
    static int go[4][2] = {{0,-1}, {+1,0}, {0,+1}, {-1,0}};
    static arrayLoc traces[1000];
    static int where = 0;
    static bool path_blocked = false;
    
    if (!path_blocked)
    {
        int error = 0;
        for(int i=0;i<4;i++)
        {
            if (isInBounds(go, i, map_sizeX, map_sizeY, curLocation)
                && arr[curLocation.x+go[i][0]][curLocation.y+go[i][1]] == ' ')
            {
                //Save last location if it's needed to go back
                traces[where] = curLocation;
                where++;
                //This direction is clear. So, go for it.
                curLocation.x += go[i][0];
                curLocation.y += go[i][1];
                arr[curLocation.x][curLocation.y] = '#';
            }
            else //This direction is blocked
                error++;
        }
        // if all directions are blocked, it got stuck.
        if(error >= 4)
        {
            //Mark the blocked path
            arr[curLocation.x][curLocation.y] = '@';
            // Go back
            where--;
            curLocation = traces[where];
            path_blocked = false;
        }
    }
    // Continue recursing if you didn't reach to the end of maze.
    if (curLocation.x < map_sizeX && curLocation.y < map_sizeY)
    {
      solveMaze(arr, map_sizeX, map_sizeY, curLocation, last_pos);
    }
}