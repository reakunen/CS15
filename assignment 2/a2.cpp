// 
// a2.cpp
// 
// Brian Mai
// 2/3/2022
// CS15 Assignment 2
// Unique word counter
// 

#include <iostream>
#include <fstream>
#include <cstring> 

#define MAX 101
#define DELIMS " .,;:!?\n\t\r"

using namespace std;

void length(char *longest, char *shortest, char *p);
void search (char unique[][16], int count[], char *p, int &uniCt);
void printData(char longest[], char shortest[], char unique[][16], 
               int uniCt, int ct, int lineCt, int count[], ostream &out);

int main (int argc, char *argv[]) 
{
    //parse for files 
    ifstream fin; 
    ofstream fout; 
    if (argc < 3)
    {
        cout << "Usage: ./" << argv[0] <<
            " input.txt output.txt" << endl;
        return 0;
    }
    fin.open(argv[1]);
    fout.open(argv[2]);
    if (!fin || !fout) 
    {
        cout << "Error opening files. Program will end." << endl; 
        return -1; 
    }
    //header for the input/output 
    fout << setfill('-') << setw(35) << '-' << endl;
    fout << "Input File: " << argv[1] << endl;
    fout << "Output File: " << argv[2] << endl; 
    fout << setfill('-') << setw(35) << '-' << endl;
    //initiate variables, max word count is 15, and holds '\0' at 16. 
    char unique[100][16] = { { "" } }, line[MAX] = "",
         words[200][16] = { { "" } }, tokdata[MAX] = "",
         longest[16] = "", shortest[16] = "", *p1 = nullptr; 
        // count is for unique # 
    int count[100] = { 0 }, uniCt = 0, ct = 0, lineCt = 0;

    while (fin) 
    {
        lineCt += 1; 
        fin.getline(line, MAX-1, '\n');
        strcpy(tokdata, line); //copy line into tokdata (from getline); 
        fout << tokdata << endl;
        p1 = strtok(tokdata, DELIMS); //tokenize the word, destroys it.
        while (p1 != nullptr) //if there is still data, keep tokenizing. 
        {
            strcpy(words[ct++], p1);
            length(longest, shortest, p1); //checks for length of cstring
            search (unique, count, p1, uniCt); //checks if unique 
            p1 = strtok(nullptr, DELIMS); 
        }
    }
    printData(longest, shortest, unique, uniCt, ct, lineCt, count, fout);
    fin.close(); 
    fout.close(); 
    return 0;  
}

void printData(char longest[], char shortest[], char unique[][16], 
               int uniCt, int ct, int lineCt, int count[], ostream &out)
{
    out << setfill('-') << setw(35) << '-' << setfill(' ') << endl;
    out << "Word Count" << setw(10) << ' ' << "Word" << endl; 
    out << setfill('-') << setw(35) << '-' << endl;
    for (int i = 0; i < uniCt; i++)
    {
        out << count[i] << setfill(' ') << setw(19) 
            << ' ' << unique[i] << endl; 
    }
    out << setfill('-') << setw(35) << '-' << endl;
    out << "Statistics" << endl;
    out << setfill('-') << setw(35) << '-' << setfill(' ') << endl;
    out << setw(16) << "Longest Word: " << setw(10) << longest << endl;
    out << setw(16) << "Shortest Word: " << setw(10) << shortest << endl;
    out << setw(16) << "Total Words: " << setw(10) << ct << endl;
    out << setw(16) << "Unique Words: " << setw(10) << uniCt << endl;
    out << setw(16) << "Total Lines: " << setw(10) << lineCt-1 << endl;
    out << setfill('-') << setw(35) << '-' << endl;
    return; 
}

void search (char unique[][16], int count[], char *p, int &uniCt)
{
    // traverse through the unique words, if it is not found, then add it
    for (int i = 0; i < uniCt; i++)
    { //if 0, they are the same (not unique) add to count
        if (strcmp(unique[i], p) == 0) 
        {
            count[i] += 1; 
            return; 
        }
    }
    //if it is not found while traversing, it is unique, so add it
    strcpy(unique[uniCt], p); 
    count[uniCt++] += 1;  //increment unictto be ready for next word 
    return; 
}

void length(char *longest, char *shortest, char *p) 
{
    static bool first = true; //first word becomes shortest & longest
    if (first) 
    {
        strcpy(shortest, p); 
        strcpy(longest, p); 
        first = false; 
        return; 
    } //compare length 
    if (strlen(shortest) > strlen(p)) strcpy(shortest, p); 
    if (strlen(longest) < strlen(p)) strcpy(longest, p); 
    return; 
}