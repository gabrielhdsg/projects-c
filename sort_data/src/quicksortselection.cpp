//---------------------------------------------------------------------
// File      : quicksortselection.cpp
// Subject   : quicksort selection algorithm (reference: discipline classes - Estrutura de Dados/UFMG-2022)
// Author    : Gabriel Henrique dos Santos Gonçalves (gabrielhenri.sg@gmail.com)
// Changes   : 2022-11-80 - file created
//             2022-11-22 - program finished - 1.0
//---------------------------------------------------------------------
#include<iostream>
#include"sortfunctions.h"

using namespace std;


void Selecao (Item *v, int n)
// Description: sort vector by a pivot or selection algorithm
// Input: v, n
// Output: -
{
    Item temp;
    int w, u, Min;
    //sort values function
    for (w = 0; w < n - 1; w++)
    {
        Min = w;
        for (u = w + 1 ; u < n; u++)
        {
            if (v[u].key < v[Min].key)
                {
                    Min = u;
                    REGISTERCOPIES++;
                }
            COMPARASIONS++;
        }
        temp = v[w]; REGISTERCOPIES++;
        v[w] = v[Min]; REGISTERCOPIES++;
        v[Min] = temp; REGISTERCOPIES++;
    }
}

void ParticaoSelection(int Esq, int Dir, int *i, int *j, Item *A, int m)
// Description: sort vector by a pivot or selection algorithm
// Input: Esq, Dir, i, j, A, m
// Output: i, j
{
    Item x, w;
    *i = Esq; *j = Dir;
    //if partition size is less than m, go to selection algorithm
    if (*i+*j<=m)
    {
        Selecao(A, *i+*j);
        *i = Dir;
        *j = Esq;
    }
    else {
        //get pivot
        x = A[(*i + *j)/2];
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
}

void OrdenaSelection(int Esq, int Dir, Item *A, int m)
// Description: call partition until the vector is sorted
// Input: Esq, Dir, A, m
// Output: -
{ 
    int i, j;
    ParticaoSelection(Esq, Dir, &i, &j, A, m);
    if (Esq < j) OrdenaSelection(Esq, j, A, m);
    if (i < Dir) OrdenaSelection(i, Dir, A, m);
}

void QuickSortSelection(Item *A, int n, int m)
// Description: call respective sort function.
// Input: A, n, m
// Output: -
{
    OrdenaSelection(0, n-1, A, m);
}