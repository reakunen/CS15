
   
// mouse-island.cpp
//
// Lisa Lehrman
// Oct 1, 2021
// CS15
// Assignment 3
// A program that models the scenario of a mouse on an island.
// The mouse has 100 lives and a max of 100 moves per life
// that it can use to try to escape the island.
// The program will print the statistics of what happened
// to the mouse to an output file.

#include <iostream>
#include <string>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iomanip>

using namespace std;

struct Vec2
{
    int x;
    int y;
};

/*
parseFirstLine is a helper function that takes a char* header and two longs as
reference parameters that represent rows and columns. It will assign values to
the rows and columns variables.
*/
void parseFirstLine(char *header, long &rows, long &cols)
{
    char *pEnd;
    rows = strtol(header, &pEnd, 10);
    cols = strtol(pEnd, NULL, 0);
}

/*
parseHeader is the function responsible for handling the first line of the
input file, which is expected to contain the values for rows and cols. It takes
an input file handle, and two longs representing rows and cols as reference
paramters.
*/
void parseHeader(ifstream &inputFile, long &mapRows, long &mapCols)
{
    char line[21];
    while (!inputFile.eof())
    {
        int size = sizeof(line);
        inputFile.getline(line, size);
        parseFirstLine(line, mapRows, mapCols);
        break;
    }
}

/*
parseLine will parse a single row of the map. It changes the value of
the map elements to int. The function takes a char** map, a pointer 
to a char called line and a long that represents the number of 
columns of a given line. The function returns no value.
*/
void parseLine(int **map, char *line, int currentRow, long cols)
{
    const int numericBase = 10;
    char *pEnd;
    long int n = strtol(line, &pEnd, numericBase);
    map[currentRow][0] = (int)n;
    for (int i = 1; i < cols; i++)
    {
        long int n = strtol(pEnd, &pEnd, numericBase);
        map[currentRow][i] = (int)n;
    }
}

/*
parseMap takes an inputFile handle, an int **map, and two longs 
that represent the number of rows and columns on the map.
The function will read lines from the input file and
create the island map. 
*/
void parseMap(ifstream &inputFile, int **map, long mapRows, long mapCols)
{
    int row = 0;
    string line;

    while (getline(inputFile, line))
    {
        char *cLine = new char[line.size() + 1];
        copy(line.begin(), line.end(), cLine);
        cLine[line.size()] = '\0';
        parseLine(map, cLine, row, mapCols);
        row++;
    }
}

int countDigits(int result)
{
    int count = 0;
    if (result < 0)
    {
        // negative numbers need an extra space for the
        // minus sign
        count += 1;
    }
    while (result != 0)
    {
        result = result / 10;
        count++;
    }
    return count;
}
/*
PrintArray takes the island map and two ints to
represent the numbers of rows and cols of the map.
It will print the array to standard output. 
*/
void printArray(ofstream &outputFile, int **map, int nRows, int nCols)
{
    int maxSize = 1;
    for (int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < nCols; j++)
        {
            maxSize = max(maxSize, countDigits(map[i][j]));
        }
    }

    for (int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < nCols; j++)
        {
            outputFile << setw(maxSize) << map[i][j] << ' ';
        }
        outputFile << '\n';
    }
}
/*
GetmousePosition takes the island map, and two ints 
that represent the numbers of rows and cols.
It will return a Vec2 type struct of which 
the values of x and y represent the current position
of the mouse on the map. 
*/
Vec2 getMousePosition(int **map, int nRows, int nCols)
{
    Vec2 mousePosition;
    mousePosition.x = -1;
    mousePosition.y = -1;
    int mouse = 1;
    for (int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < nCols; j++)
        {
            if (map[i][j] == mouse)
            {
                mousePosition.x = j;
                mousePosition.y = i;
                return mousePosition;
            }
        }
    }
    return mousePosition;
}
/*
moveMouse takes a reference to the Vec2 struct that 
contains the current mouse position on the map. It 
uses tabled complexity to move the mouse in pseudo-random 
movements around the map.
*/
void moveMouse(Vec2 &currentMousePosition)
{
    static const int mouseMoves[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    int r = rand() % 4; // random 0-3
    currentMousePosition.x += mouseMoves[r][0];
    currentMousePosition.y += mouseMoves[r][1];
}
/*
ClearMap takes the island map and two ints representing
the number of rows and cols on the map. It will set
all elements in the map to zeroes. 
*/
void clearMap(int **map, int nRows, int nCols)
{
    for (int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < nCols; j++)
        {
            map[i][j] = 0;
        }
    }
}
/*
getBridgePosition takes the island map, two ints to represent
the number of rows and cols in the map and an array of Vec2 structs to 
store the positions of the bridges on the map.
The bridges will only be located on the perimeter of the map. 
*/
void getBridgePositions(int **map, int nRows, int nCols, Vec2 *bridges)
{
    int bridgesFound = 0;
    for (int x = 0; x < nCols; x++)
    {
        if (map[nRows - 1][x] == 0)
        {
            bridges[bridgesFound].x = x;
            bridges[bridgesFound].y = nRows - 1;
            bridgesFound += 1;
        }
        if (map[0][x] == 0)
        {
            bridges[bridgesFound].x = x;
            bridges[bridgesFound].y = 0;
            bridgesFound += 1;
        }
    }
    for (int y = 1; y < nRows - 1; y++)
    {
        if (map[y][0] == 0)
        {
            bridges[bridgesFound].x = 0;
            bridges[bridgesFound].y = y;
            bridgesFound += 1;
        }
        if (map[y][nCols - 1] == 0)
        {
            bridges[bridgesFound].x = nCols - 1;
            bridges[bridgesFound].y = y;
            bridgesFound += 1;
        }
    }
}

int main(int argc, char *argv[])
{

    ifstream inputFile;
    ofstream outputFile;
    const char *inputFileName = argv[1];
    const char *outputFileName = argv[2];

    inputFile.open(inputFileName);
    outputFile.open(outputFileName);
    if (!inputFile)
    {
        cout << "There was a problem opening input file " << inputFileName << endl;
        return -1;
    }
    if (!outputFile)
    {
        cout << "There was a problem opening output file " << outputFileName << endl;
        return -1;
    }
    outputFile << inputFileName << " " << outputFileName << endl;
    outputFile << "--------------------------------------------------\n";
    char *seed = nullptr;
    if (argc < 3 || argc > 5)
    {
        cout << "Usage: " << argv[0] << " <input> <output> [<seed>]" << endl;
        cout << "\nEnter the seed value OR the string TIME" << endl;
        cout << "in uppercase to seed the random number" << endl;
        cout << "generator using the current time." << endl;
        cout << "If no value for seed is entered, the number" << endl;
        cout << "generator will not be seeded." << endl;
        return 0;
    }
    if (argc == 4)
    {
        seed = argv[3];
    }
    if (seed && strcmp(seed, "TIME") == 0)
    {
        srand(time(NULL));
        outputFile << "seeded with time" << endl;
    }
    else if (seed)
    {
        int s = atoi(seed);
        srand(s);
        outputFile << "Need: " << s << endl;
    }
    else
    {
        outputFile << "No seed provided" << endl;
    }
    
    long mapRows, mapCols;

    Vec2 initialMousePosition;
    Vec2 currentMousePosition;
    Vec2 bridges[2];

    parseHeader(inputFile, mapRows, mapCols);

    int **map = new int *[mapRows];
    int **mouseMovesMap = new int *[mapRows];

    for (int i = 0; i < mapRows; i++)
    {
        map[i] = new int[mapCols];
        mouseMovesMap[i] = new int[mapCols];
    }
    clearMap(mouseMovesMap, mapRows, mapCols);
    parseMap(inputFile, map, mapRows, mapCols);
    outputFile << "--------------------------------------------------\n";
    outputFile << "Island map" << endl;
    printArray(outputFile, map, mapRows, mapCols);

    initialMousePosition = getMousePosition(map, mapRows, mapCols);

    getBridgePositions(map, mapRows, mapCols, bridges);
    outputFile << "--------------------------------------------------\n";
    outputFile << "mouse initial position: (" << initialMousePosition.x << ", "
               << initialMousePosition.y << ")"
               << endl;
    outputFile << "--------------------------------------------------\n";
    map[initialMousePosition.y][initialMousePosition.x] = 0;

    int drownCount = 0;
    int escapeCount = 0;
    int starveCount = 0;
    for (int life = 0; life < 100; life += 1)
    {
        currentMousePosition.x = initialMousePosition.x;
        currentMousePosition.y = initialMousePosition.y;

        int move = 0;
        for (; move < 100; move += 1)
        {
            moveMouse(currentMousePosition);
            mouseMovesMap[currentMousePosition.y][currentMousePosition.x] += 1;
            int terrain = map[currentMousePosition.y][currentMousePosition.x];
            bool drowned = terrain == -1;
            bool escaped = false;
            for (int i = 0; i < 2; i += 1)
            {
                if (currentMousePosition.x == bridges[i].x
                    && currentMousePosition.y == bridges[i].y)
                {
                    escaped = true;
                    break;
                }
            }
            if (drowned)
            {
                outputFile << "Mouse " << life + 1
                           << " tried to breathe underwater." << endl;
                drownCount += 1;
                break;
            }
            if (escaped)
            {
                outputFile << "Mouse " << life + 1
                           << " escaped. Where will he go?" << endl;
                escapeCount += 1;
                break;
            }
        }
        if (move == 100)
        {
            outputFile << "Mouse " << life + 1
                       << " is bereft of food and life." << endl;
            starveCount += 1;
        }
    }
    outputFile << "--------------------------------------------------\n";
    outputFile << "Here's a summary of what happened for each life: " << endl;
    outputFile << "The mouse drowned " << drownCount << " times." << endl;
    outputFile << "The mouse escaped the island " << escapeCount << " times." << endl;
    outputFile << "The mouse starved " << starveCount << " times." << endl;
    outputFile << "--------------------------------------------------\n";
    outputFile << "Map of mouse move counts" << endl;
    printArray(outputFile, mouseMovesMap, mapRows, mapCols);
    outputFile << "--------------------------------------------------\n";
    inputFile.close();
    outputFile.close();
    return 0;
}