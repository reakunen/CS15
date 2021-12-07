//
// zzz.cpp
// Brian Mai 
// December 4, 2021
// Assignment 2
// Reading lines from a file and tokenizing them
//

#include <iostream>
#include <cstring> 
#include <fstream>
#include <iomanip> 
using namespace std;

#define DELIMITER " .,;:!?\n\t\r"

struct Word {
    char word[100]; 
    int count;
};

int main (int argc, char* argv[]) {
    
    ifstream fin; 
    ofstream fout;

    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return 1;
    }
    fin.open(argv[1]);
    fout.open(argv[2]);

    if (!fin.is_open()) {
        cout << "Error: could not open file " << argv[1] << endl;
        return 1;
    }
    if (!fout.is_open()) {
        cout << "Error: could not open file " << argv[2] << endl;
        return 1;
    }
    Word word[100];
    char lineZ[256][100], longest[100], shortest[100]; 
    int ct = 0, ctZ = 0, ctT = 0; 
    bool unique = true; 
    while (!fin.eof()) {
        fin.getline(lineZ[ctZ], 256);
        fout << lineZ[ctZ] << endl; 
        char* token = strtok(lineZ[ctZ], DELIMITER);
        // strcpy(line[++ct], token);
        while (token != NULL) {
            ctT += 1; 
            if (ct == 0) {
                strcpy(word[ct].word, token);
                word[ct].count = 1;
                strcpy(longest, token);
                strcpy(shortest, token);
                ct++;
                token = strtok(NULL, DELIMITER);
                break; 
            }
            for (int i = 0; i < ct; i++) 
            {
                //if they are the same, word count increment, else unique
                unique = true; 
                if (strcmp(word[i].word, token) == 0) 
                {
                    word[i].count += 1; 
                    unique = false; 
                    break;
                }   
            }
            if (unique)
                {
                    strcpy(word[ct].word, token);
                    cout << word[ct].word << endl;
                    word[ct].count = 1;
                    ct++; 
                    if (strlen(shortest) > strlen(token))
                    {
                        strcpy(shortest, token);
                    }

                    if (strlen(longest) < strlen(token))
                    {
                        strcpy(longest, token);
                    }
                }
            //./zzz z.txt zap.txt
            token = strtok(NULL, DELIMITER);
        }
        ctZ++; 
    }

    fout << setfill('-') << setw(20) << '-' <<  setfill(' ') << endl;
    fout << setw(5) << "Word Count " << setw(9) << "Word" << endl; 
    fout << setfill('-') << setw(20) << '-' << setfill(' ') << endl;

    for (int i = 0; i < ct; i++) 
    {       
        fout << setw(3) << word[i].count << " " << setw(16) << word[i].word << endl;
    }

    fout << '\n' << setfill('-') << setw(20) << '-' << setfill(' ') << endl;
    fout << "Output" << endl;
    fout << setfill('-') << setw(20) << '-' << setfill(' ') << endl;

    fout << setw(3) << "Smallest Word: " << shortest << endl;
    fout << setw(3) << "Longest Word: " << longest << endl;
    fout << setw(3) << "Total Words: " << ctT << endl;
    fout << setw(3) << "Line Count: " << ctZ << endl;
    fout << setw(3) << "Unique Words: " << ct << endl;

    fin.close();
    fout.close();
    return 0;
}