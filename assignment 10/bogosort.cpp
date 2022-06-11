// C++ implementation of Bogo Sort
#include <iostream>
using namespace std;

// To check if array is sorted or not
bool isSorted(int a[], int n)
{
    static int ct = 0; 
    for (int i = 0; i < n-1; i++)
    {
        if (a[i] > a[i+1])
        {
            cout << "ct: " << ++ct << " | " << flush; 
            return false; 
        }
    }
    return true; 
}
// bool isSorted(int a[], int n)
// {
// 	while ( --n > 1 )
// 		if (a[n] < a[n-1])
// 			return false;
// 	return true;
// }

// To generate permutation of the array
void shuffle(int a[], int n)
{
	for (int i=0; i < n; i++)
		swap(a[i], a[rand()%n]);
}

// prints the array
void printArray(int a[], int n)
{
	for (int i=0; i<n; i++)
		printf("%d ", a[i]);
	printf("\n");
}

// Sorts array a[0..n-1] using Bogo sort
void bogosort(int a[], int n)
{
	// if array is not sorted then shuffle
	// the array again
	while ( !isSorted(a, n) )
    {    
        printArray(a, n);
		shuffle(a, n);
    }
} // its using rand() to sort 


// Driver code
int main()
{
    cout << "Enter size of array: " << endl;
    int n = 10; 
    cin >> n; 
    int *a = new int[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Enter values: " << flush;
        cin >> a[i]; 
    }
	bogosort(a, n);
	printf("Sorted array :\n");
	printArray(a,n);
    delete[] a; 

	return 0;
}
