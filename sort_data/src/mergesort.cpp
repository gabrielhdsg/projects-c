//---------------------------------------------------------------------
// File      : mergesort.cpp
// Subject   : heapsort algorithm (reference: https://en.wikipedia.org/wiki/Merge_sort)
// Author    : Gabriel Henrique dos Santos Gonçalves (gabrielhenri.sg@gmail.com)
// Changes   : 2022-11-80 - file created
//             2022-11-22 - program finished - 1.0
//---------------------------------------------------------------------
#include<iostream>
#include"sortfunctions.h"

using namespace std;

void Merge(Item *arr, int l, int r, int m)
// Description: compare two sorted vectors 
// Input: Esq, Dir, A
// Output: -
{
    //varialbes
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    //insert sorted values in auxiliary array
    Item *L, *R;
    L = new Item [n1];
    R = new Item [n2];
    for (i = 0; i < n1; i++)
    {
        L[i] = arr[l + i];
        REGISTERCOPIES++;
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = arr[m + 1 + j];
        REGISTERCOPIES++;
    }
        
 
   //merge arrays back to the main vector
    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2) {
        if (L[i].key <= R[j].key) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        COMPARASIONS++;
        REGISTERCOPIES++;
        k++;
    }
 
    //if there is any remaining value
    while (i < n1) {
        arr[k] = L[i];
        REGISTERCOPIES++;
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        REGISTERCOPIES++;
        j++;
        k++;
    }
    delete R;
    delete L;
}


void OrdenaMergeSort(Item *A, int Esq, int Dir) 
// Description: call itself recursively and then call merge
// Input: Esq, Dir, A
// Output: -
{
    int middle;
    if (Esq<Dir)
    {
        middle = (Esq+Dir)/2;
        OrdenaMergeSort(A, Esq, middle);
        OrdenaMergeSort(A, middle+1, Dir);
        Merge(A, Esq, Dir, middle);
    }
}

void MergeSort(Item *A, int n)
// Description: call respective sort function.
// Input: A, n
// Output: -
{
    OrdenaMergeSort(A, 0, n-1);
}