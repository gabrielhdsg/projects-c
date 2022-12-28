//---------------------------------------------------------------------
// File      : heapsort.cpp
// Subject   : heapsort algorithm (reference: https://www.geeksforgeeks.org/heap-sort/)
// Author    : Gabriel Henrique dos Santos Gonçalves (gabrielhenri.sg@gmail.com)
// Changes   : 2022-11-80 - file created
//             2022-11-22 - program finished - 1.0
//---------------------------------------------------------------------
#include<iostream>
#include"sortfunctions.h"

using namespace std;

void Rebuild(Item *A, int n, int i)
// Description: to rebuild a subtree rooted with node i which is an index in A[]. n is size of heap.
// Input: A, n, i
// Output: -
{
    //variables initialization
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    //compare left and right child 
    if (l < n && A[l].key > A[largest].key)
        largest = l;
    COMPARASIONS++;
    if (r < n && A[r].key > A[largest].key)
        largest = r;
    COMPARASIONS++;
    // if largest is not root
    Item aux;
    if (largest != i) {
        aux = A[i]; REGISTERCOPIES++;
        A[i]=A[largest]; REGISTERCOPIES++;
        A[largest] = aux; REGISTERCOPIES++;
        Rebuild(A, n, largest);
    }
}


void OrdenaHeapSort(Item *A, int n) 
// Description: call rebuild until the vector is sorted
// Input: Esq, Dir, A
// Output: -
{
    //build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        Rebuild(A, n, i);
 
    //one by one extract an element from heap
    Item aux;
    for (int i = n - 1; i > 0; i--) {
        aux = A[0]; REGISTERCOPIES++;
        A[0]=A[i]; REGISTERCOPIES++;
        A[i] = aux; REGISTERCOPIES++;
        Rebuild(A, i, 0);
    }
}

void HeapSort(Item *A, int n)
// Description: call respective sort function.
// Input: A, n
// Output: -
{
    OrdenaHeapSort(A, n);
}