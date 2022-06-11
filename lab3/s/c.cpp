

#include <iostream>

using namespace std; 

size_t strlen1(char *p)
{
    /* pointer arithmetic */
    char *s = p; 
    while (*p)
    {
        p++; 
    }
    return p-s; 
}

size_t strspn1(char p[], const char* d)
{
    //p is string, d is delimiter 
    //how many letters to "skip" whitespace
    size_t shortest = strlen1(p); 
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

char *mystrtok(char *p, const char *d)
{
    /* Static variables */
    static char *next; 
    static int ct; 
    static int max = strlen1(p); 
    

    if (ct == max)
    {
        return NULL; 
    }

    /* Returning where the pointer is to the array.
       Points to the "NUL" character ('\0) */
    return p; 
}

char * s1(char *str, const char *delim)
{
    static char *nxt; /* static variable used to advance the string to replace delimiters */
    static int size;  /* static variable used to count until the end of the string        */

    /* IMPORTANT: any advance to 'nxt' must be followed by a diminution of 'size', and vice verce */

    int i; /* counter of delimiter(s) in string */

    /* initialize the string when strtok2 is first called and supplied with a valid string */
    if(str != NULL)
    {
        nxt = str;
        size = strlen1(str);
    }

    /* if we havn't reached the end of the string, any other call to strtok2 with NULL will come here */
    else if(size > 0)
    {
        nxt++;      /* last run left nxt on a null terminator, so we have to advance it */
        size--;     /* any advancement must follow diminution of size                   */
        str = nxt;  /* string now points to the first char after the last delimiter     */ 
    }

    /* if we reached the end of string, return NULL pointer */
    else
    {
        str = NULL;
    }

    /* nxt is used to advance the string until a delimiter or a series of delimiters are encountered; 
    * it then stops on the last delimiter which has turned to NULL terminator
    */
    while(*nxt)
    {
        i = strspn(nxt, delim);
        cout << i << endl; 
        while(i > 1)        /* turns delimiters to NULL terminator (except the last one) */
        {
            *nxt = '\0';
            nxt++;
            size--;
            i--;
        }                   /* in the last delimiter we have to do something a      */
        if(1 == i)          /* bit different we have to actually take nxt backwards */
        {                   /* one step, to break the while(*nxt) loop              */
            *nxt = '\0';
            if(size > 1)    /* if the delimiter is last char, don't do next lines   */
            {
                nxt--;
                size++;     /* nxt is diminished so size increases                    */
            }
        }
        nxt++;          /* if no delimiter is found, advance nxt                  */
        size--;         /* in case of the last delimiter in a series, we took nxt */
    }                   /* a step back, so now moving it a step forward means     */
                        /* it rests on a NULL terminator                          */
    return str;
}

char* my_strtok(char *str, char *c){

	if(!c)
		return NULL;

	static char *buffer = NULL;

	if(str){
		buffer = str;
	}else{
		if(!buffer || !*buffer){
			return NULL;
		}
	}

	char *token = buffer;
	int i = 0;
	int len = strlen(c); //length is the length of string

        while(*buffer && i != len){ // while not end of file && not NUL
            while(*buffer && *buffer != *c){
                buffer += 1; //adding one to buffer which will happen next time 
            }
            while(buffer[i] == c[i] && i < len){
                i += 1;
            }
            if(i == len){
                *buffer = 0;
                buffer += len;
            }else{
                buffer += 1;
            }
        }
        if (*buffer == *c)
    cout << *token << endl; 
	return token;

}//my_strtok*/


int main ()
{
    const int SIZE = 100; 
    char d[5] = "og"; 
    char dog[100] = "fat dog"; 
    cout << strspn1(dog, d) << endl;
   
    cout << "Enter string" << endl;
    cin.getline(dog, SIZE-1, '\n'); 

    char *token = NULL;
    char del[SIZE] = "\t";

    token = s1(dog, del);
    while (token != NULL) {       
        cout << "Token: " << token << endl; 
        token = s1(NULL, del);
    }
    
   return 0; 
}