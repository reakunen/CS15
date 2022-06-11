//
// lab6.cpp
//
// Brian Mai, Jordan Consul
// 4/19/2022
// CS15 Lab 6
// Palindrome Finder using Recursion & Iteration
//

#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

#define MAX 100

void makeLower(char *p)
{
    char temp = '\0';
    int i = 0; 
    while (p[i] != '\0')
    {
        if (isalpha(p[i]))
        {
            temp = tolower(p[i]);
            p[i] = temp;
        }
        i++; 
    }
    return;
}

char *simplify(const char *in)
{
    static char out[MAX] = "";
    char copied[MAX] = "";
    char *temp;

    strcpy( out, "" );                   // reseting the return value
    strcpy( copied, in );                // making a copy of the string
    makeLower( copied );                 // makes the copy lowercase
    temp = strtok( copied, ",.'!? " );    //
    while ( temp != nullptr )            //
    {                                    // <- adds tokens to the out string
        strcat( out, temp );
        temp = strtok( nullptr, ",.'!? " );
    }

    return out;
}

bool iterativePal(const char *p)
{
    // find all Alphanumeric characters
    // Find the size of the palindrome, and make a copy of the string
    int i = 0, j;
    char* ptr = simplify(p);    // simplify function to make the string
                                // easier to sort through.

    j = strlen(ptr) - 1;

    while (ptr[i] == ptr[j])    // checks the characters if they are the same
    {                           // then goes to the next group
        i++;
        j--;
        if (j - i <= 1)
        {
            ptr = nullptr;
            return true;
        }
    }
    ptr = nullptr;
    return false;
}

bool recursivePal(const char *p)
{
    char *temp = simplify(p);   // delims and lower cases the original string
    static int low = 0, high;   // to a copy string
    high = strlen(temp) - low;  // high and low are made/used

    if (high == low || high - low == 1  )
    {
        low = 0;
        return true;
    }
    else if ( temp[low] == temp[high-1] )
    {
        low++;                                 // check characters then goes
        high--;                                // to next characters.
        return recursivePal(p);
    }
    low = 0;
    return false;
}

int main()
{
    char d[MAX] = "Madam, I'm Adam.";

    cout << "here is the base run. Enter \"quit\" to end program." << endl;
    do
    {
        cout <<"\nIterative: <" << d << ">" << flush;
        if (iterativePal(d))
        {
            cout << " is a PALINDROME" << endl;
        }
        else
        {
            cout << " is NOT a PALINDROME" << endl;
        }

        //temp = simplify(d);
        cout << "Recursive: <" << d << ">" << flush;
        if (recursivePal(d))
        {
            cout << " is a PALINDROME\n" << endl;
        }
        else
        {
            cout << " is NOT a PALINDROME\n" << endl;
        }

        cout << "Type in a string: " << flush;
        cin.getline( d, MAX-1 );
    } while( strcmp( d, "quit" ) );

    return 0;
}