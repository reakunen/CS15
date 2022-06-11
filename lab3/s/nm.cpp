#include <iostream>

using namespace std;

size_t strlen1(const char *p)
{
    size_t ct = 0; 
    while (*p != '\0')
    {
        ct++; 
        p++; 
    }
    return ct; 
}

size_t strspn1(char p[], const char d[])
{
    //p is string, d is delimiter 
    //how many letters to "skip" whitespace
    size_t shortest = strlen(p); 
    int i = 0, j = 0;  
    while (d[i] != '\0') // while it is not null, compare
    {
        j = 0; 
        while(p[j] != '\0') // while delimiters is not nul
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



char *strtok1(char *p, const char* d) 
{
    //passes in the address of (base of the array) 
    /* Initialize pointers to the starting value as static */
    /* fast pointer will drop NUL character, slow pointer will be returned */

]]
    static char *fast = p, *slow = p, *base = p;  
    static int max = strlen1(p); 
    static int incr = 0, incrTotal = 0, dropNul = 0; 
    static int olds = 0; 

    cout << "slow address1: " << *slow << endl; 
    if (d == NULL) return p; // if delimiter is empty, return back string
    // increment address for slow pointer & fast. 
    //string: "dog cat"; 
    //slow at first would be at p[0], then should be at index p[4]
    // slow += olds; 
    slow += dropNul +1; 
    incr = strspn1(slow, d); // tells length of string until there is a nul character
    //increment the fast pointer so it is in the spot of the delim to put whitespace

    incrTotal += incr; 
    dropNul += incr + 1; 
    //if *olds is a DELIM, increment olds until end of string, until its not.
    *(base + dropNul) = '\0'; 
    
    return slow; 
}

int main ()
{
    /********** Psuedo Code **********/
    //strtok returns the POINTER address of the character array (cstring)
    //char *strtok(char *originalstring, const char* delimiter)
    //  1)find if CHARACTER is in delimiter, using find() if not, can index the (FAST) pointer.
    //  2) when found the delimiter, put a NUL character (FAST POINTER) address.
    //  3) use the closest delimiter to put NUL character 
    //  4) return the SLOW pointer. 
    // When end of string (end of string length using strlen(), it will be changed back to zero) 

    char p[50] = "Monkey Water Poop Awooga"; 
    char d[10] = " /"; 
    char *ptr = nullptr; 
    cout << p << endl; 
    ptr = strtok1(p, d);
    cout << ptr << endl; 
    ptr = strtok1(NULL, d);
    cout << ptr << endl; 

    return 0; 
}