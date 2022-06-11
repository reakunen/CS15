//
//
//
// Jordan Consul, Brian Mai
// 5/1/2022
// Lab 6
//
//

#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

#define MAX 100

void makeLower(char *p)
{
    int i = 0, ct = 0;
    while (p[i] != '\0')
    {
        if (isalpha(p[i]))
        {
            ct++;
        }
        i++;
    }
    int length = strlen(p);
    char temp = '\0';
    for (i = 0; i < length; i++)
    {
        temp = tolower(p[i]);
        p[i] = temp;
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
    temp = strtok( copied, ",.'! " );    //
    while ( temp != nullptr )            //
    {                                    // <- adds tokens to the out string
        strcat( out, temp );
        temp = strtok( nullptr, ",.'! " );
    }

    return out;
}

bool iterativePal(const char *p)
{
    // find all Alphanumeric characters
    // Find the size of the palindrome, and make a copy of the string
    int size = strlen(p), times = 0;
    char* ptr = nullptr;
    ptr = new char[size+1];
    strcpy(ptr, p);
    makeLower(ptr);
    // ptr1 points to the base, ptr2 points to top-1.
    char *ptr1 = &ptr[0], *ptr2 = &ptr[size-1];
    while (*ptr1 == *ptr2)
    {
        times += 1;
        ptr1 += 1;
        ptr2 -= 1;
        if (times >= size)
        {
            delete[] ptr;
            ptr = nullptr;
            return true;
        }
    }
    delete[] ptr;
    ptr = nullptr;
    return false;
}

// use as recursivePal(stringname, 0, strlen(stringname));
bool recursivePal(char *p, int a, int b)
{
    if (p[a] != p[b]) return false;  //if they are not equal, return false
    if (a == b || b - a == 1)
    {
        return true;
    }
    return recursivePal(p, a+1, b-1); // a is the bottom, b is top
}

int main()
{
    char d[MAX] = "Madam, I'm Adam.";
    char *temp;
    int start = 0;

    cout << "here is the base run. Enter \"quit\" to end program.\n" << endl;
    do
    {
        temp = simplify(d);


        cout <<"Iterative: <" << d << ">" << flush;
        if (iterativePal(temp))
        {
            cout << " is a PALINDROME" << endl;
        }
        else
        {
            cout << " is NOT a PALINDROME" << endl;
        }

        cout << "Recursive: <" << d << ">" << flush;
        if (recursivePal(temp, start, strlen(temp)-1))
        {
            cout << " is a PALINDROME\n" << endl;
        }
        else
        {
            cout << " is NOT a PALINDROME\n" << endl;
        }

        cin.getline( d, MAX-1 );
    } while( strcmp( d, "quit" ) );

    return 0;
}