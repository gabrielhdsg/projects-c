//---------------------------------------------------------------------
// File      : quicksortrecursive.cpp
// Subject   : quicksort recursive algorithm (reference: discipline classes - Estrutura de Dados/UFMG-2022)
// Author    : Gabriel Henrique dos Santos Gonçalves (gabrielhenri.sg@gmail.com)
// Changes   : 2022-11-80 - file created
//             2022-11-22 - program finished - 1.0
//---------------------------------------------------------------------
#include<iostream>
#include"sortfunctions.h"

using namespace std;


void Particao(int Esq, int Dir, int *i, int *j, Item *A)
// Description: sort vector by a pivot
// Input: Esq, Dir, i, j, A
// Output: i, j
{
    Item x, w;
    *i = Esq; *j = Dir;
    //get pivot
    x = A[(*i + *j)/2]; REGISTERCOPIES++; 
    //swaping pivot right and left elements
    do
    {
        while (x.key > A[*i].key) 
        {
            (*i)++;
            COMPARASIONS ++;
        }
        while (x.key < A[*j].key) 
        {
            (*j)--;
            COMPARASIONS ++;
        }
        
        if (*i <= *j)
        {
            w = A[*i]; REGISTERCOPIES++;
            A[*i] = A[*j]; REGISTERCOPIES++;
            A[*j] = w; REGISTERCOPIES++;
            (*i)++; (*j)--;
        }
    } while (*i <= *j);
}

void Ordena(int Esq, int Dir, Item *A)
// Description: call partition until the vector is sorted
// Input: Esq, Dir, A
// Output: -
{ 
    int i, j;
    Particao(Esq, Dir, &i, &j, A);
    if (Esq < j) Ordena(Esq, j, A);
    if (i < Dir) Ordena(i, Dir, A);
}

void QuickSortRecursive(Item *A, int n)
// Description: call respective sort function.
// Input: A, n
// Output: -
{
    Ordena(0, n-1, A);
}

