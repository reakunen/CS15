// 
// stringtoken.cpp
// 
// Brian Mai, Yanming Luo
// 2/26/2022
// CS15 Lab 3
// A clone of strtok
//  

#include <iostream>

#define MAX 100
#define DELIM " .!?,\t"

using namespace std;

char *mystrcpy(char *d, char *s)
{
   char *temp = d;
   while (*d++ = *s++); 
   return temp;
}

int mystrcmp(const char *s, const char *t)
{
    while (*s && *s == *t)
    {
        t++; 
        s++; 
    }
    return *s-*t; 
}

size_t mystrlen(const char *p)
{
    size_t ct = 0; 
    while (*p != '\0')
    {
        ct++; 
        p++; 
    }
    return ct; 
}

size_t findDelim(char *p, const char *d)
{
    //how many letters to "skip" whitespace
    size_t shortest = mystrlen(p); 
    int i = 0, j = 0;  
    while (d[i] != '\0') // while it is not null, compare
    {
        j = 0; 
        while(p[j] != '\0') // while delimiters are not nul
        {
            if (p[j] == d[i]) 
            {
                if (j < shortest)
                {
                    shortest = j; 
                }
                break;
            }
            j++; 
        }
        i++; 
    }
    return shortest; 
}

char *mystrtok(char *p, const char* d) 
{
    // Initialize pointers to the starting value as static so
    // values aren't changed through function calls 
    // fast pointer will drop NUL character, slow pointer will be returned 
    // as the address of the next token
    static int size = mystrlen(p); 
    static char *fast = p, *slow = p, *base = p;  
    static int total = 0; 
    static bool first = true, reset = false; 

    // resets static variable if new string is passed in
    if (reset == true)
    {
        fast = p, slow = p, base = p; 
        total = 0, size = strlen(p); 
        first = true, reset = false; 
    }

    slow += total;           // moves the slow pointer to be start of string
    if (d == NULL) return p; // if delimiter is empty, return back string

    // If it is the end of string (no more tokens to tokenize),            
    // return back NULL and RESET all of the static variables so they can  
    // hold the next string when the next string passed in    
    
    if (*slow == '\0') 
    {
        for (int i = 0; i < size; i++)
        {
            base[i] = '\0'; // Destroys the string, allowing the next line 
        }
        reset = true;       // reset will reset the static variables
        return NULL;        // return NULL to signify the string has ended
    } 
    
    int incr = findDelim(slow, d);
    int ct = 0; 
    while (incr == 0)       // will keep on incrementing to find a non-delimiter
    {   
        ct++; 
        incr = findDelim(++slow, d);  
        if (*slow == '\0') 
        {
            reset = true;     // reset will reset the static variables
            return NULL;      // return NULL to signify the string has ended
        }         
    }
    if (!first) fast += 1; // see if the string is being tokenized the first 
    first = false;               
    fast += incr + ct;     // fast is where the delimiter will be  
    total = incr+1;        // total is what will be added to slow to move ptr
    *fast = '\0';          // drop nul character on delimiter
    return slow; 
}

int main ()
{
    /********** Psuedo Code **********/
    //  strtok returns the POINTER address of the character array (cstring)
    //  1) find if CHARACTER is in delimiter, using find() if not found, fast++
    //  2) when found the delimiter, put a NUL character (FAST POINTER)
    //  3) use the closest delimiter to put NUL character 
    //  4) return the SLOW pointer, increment it for next call 
    //  5) When end of string (when slow hits NUL) return NULL
    //  6) terminate the string (while size, put NUL for all)
    //  7) Reset all the static variables to take in next string from getline

    int ct = 0, tokenct = 0;  
    const char STOP[] = "quit"; 
    char line[MAX] = "", tokdata[MAX] = "", *ptr = nullptr;
    bool loop = true; 
    while (loop)
    {
        ct += 1, tokenct = 0;                       
        cout << "Enter line " << ct << ": " << flush; 
        cin.getline(line, MAX-1, '\n');
        if (mystrcmp(STOP, line)==0)    // if the user inputs "quit", end program. 
        {
            cout << "Program has ended. " << endl;
            return 0; 
        }
        mystrcpy(tokdata, line);
        cout << "line entered: " << tokdata << endl; 
        ptr = mystrtok(tokdata, DELIM); 
        while (ptr != NULL)
        {   
            cout << "token " << ++tokenct << ": " << ptr << endl;
            ptr = mystrtok(NULL, DELIM); 
        }
    }
    return 0; 
}