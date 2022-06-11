#include <iostream>
#include <cstring>

#define SIZE_OF_STRING 50 
#define SIZE_OF_DELIMITER 5
#define NUL '\0'

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
char *strtok1(char *p, const char *d)
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

/* Make the temp_ptr as static, so it will hold the previous pointing address */
static char *temp_ptr = NULL;

char *string_token(char *str, char *delimiter)
{
    char *final_ptr = NULL;  
    /* Flag has been defined as static to avoid the parent function loop
     * runs infinitely after reaching end of string.
     */ 
    static int flag = 0;
    int i, j;

    if (delimiter == NULL) {
        return NULL;
    }

    /* If flag is 1, it will denote the end of the string */
    if (flag == 1) {
        return NULL;
    }

    /* The below condition is to avoid temp_ptr is getting assigned 
     * with NULL string from the parent function main. Without
     * the below condition, NULL will be assigned to temp_ptr 
     * and final_ptr, so accessing these pointers will lead to
     * segmentation fault.
     */
    if (str != NULL) { 
        temp_ptr = str; 
    }

    /* Before function call ends, temp_ptr should move to the next char,
     * so we can't return the temp_ptr. Hence, we introduced a new pointer
     * final_ptr which points to temp_ptr.
     */
    final_ptr = temp_ptr;

    for (i = 0; i <= strlen1(temp_ptr); i++)
    {
        for (j = 0; j < strlen1(delimiter); j++) {

            if (temp_ptr[i] == '\0') {
                /* If the flag is not set, both the temp_ptr and flag_ptr 
                 * will be holding string "Jasmine" which will make parent 
                 * to call this function string_token infinitely. 
                 */
                flag = 1;
                return final_ptr;
            }

            if (temp_ptr[i] == *(delimiter+j)) {
                /* NULL character is assigned, so that final_ptr will return 
                 * til NULL character. Here, final_ptr points to temp_ptr.
                 */
                temp_ptr[i] = '\0';
                temp_ptr += i+1;
                return final_ptr;
            }
        }
    }
    /* You will somehow end up here if for loop condition fails.
     * If this function doesn't return any char pointer, it will 
     * lead to segmentation fault in the parent function.
     */
    return NULL;
}


int main()
{

    char dog[] = "dog"; 
    cout << strlen1(dog) << endl; 
    return 0;
}