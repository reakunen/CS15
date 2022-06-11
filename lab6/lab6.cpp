// 
// lab6.cpp
// 
// Brian Mai
// 4/19/2022
// CS15 Lab 6
// Palindrome Finder using Recursion & Iteration
// 

#include <iostream>
#include <cstring>
#include <cctype>

#define MAX 1000 
using namespace std; 

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
        cout << *ptr1 << "is the same as " << *ptr2 << endl; // debugging code 
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

void makeLowerPal(char *p, int i)
{
    if (i == -1) return; // base case
    char temp = tolower(p[i]); 
    p[i] = temp; 
    makeLowerPal(p, i-1); 
}
// use as recursivePal(stringname, 0, strlen(stringname)-1); 
bool recursivePal(char *p, int a, int b)
{   
    cout << p[a] << "\t" << p[b] << endl;  // debugging code
    makeLowerPal(p, strlen(p)); // this makes the word all lower case 
    if (p[a] != p[b]) return false;  //if they are not equal, return false 
    if (a == b || b - a == 1) 
    {
        return true; 
    }
    return recursivePal(p, a+1, b-1); // a is the bottom, b is top 

}


int main (int argc, char **argv)
{
    char d[100] = "sus";
    int a = 0 , b = 0; 
    
    if (recursivePal(d, a, strlen(d)-1))
    {
        cout << "<|" << d << "|>" << " is a PALINDROME" << endl; 
    } 
    else
    {
        cout << "<|" << d << "|>" << " is NOT a PALINDROME" << endl; 
    }
    cout << d << endl; 
    return 0; 
}