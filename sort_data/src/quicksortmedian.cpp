//---------------------------------------------------------------------
// File      : quicksortmedian.cpp
// Subject   : quicksort median algorithm (reference: discipline classes - Estrutura de Dados/UFMG-2022)
// Author    : Gabriel Henrique dos Santos Gonçalves (gabrielhenri.sg@gmail.com)
// Changes   : 2022-11-80 - file created
//             2022-11-22 - program finished - 1.0
//---------------------------------------------------------------------
#include<iostream>
#include <stdlib.h> 
#include"sortfunctions.h"

using namespace std;

int FindMedian(int Esq, int Dir, Item *A, int k)
// Description: choose a  pivot from random k A values 
// Input: Esq, Dir, A, k
// Output: pivot
{
   int *aux, sortaux;
   Item *temp;
   aux = new int [k];
   temp = new Item [k];
   //getting random elements from A
   for (int j = 0; j < k; j++)
   {
        aux[j]=Esq+rand()%(Dir-Esq);
        temp[j] = A[aux[j]]; REGISTERCOPIES++;
        
   }
   delete aux;
   //sorting ascending order
    for(int u=0;u<k;u++)
	{		
		for(int y=u+1;y<k;y++)
		{
			if(temp[u].key>temp[y].key)
			{
                COMPARASIONS ++;
				sortaux=temp[u].key; REGISTERCOPIES++;
				temp[u].key=temp[y].key; REGISTERCOPIES++;
				temp[y].key=sortaux; REGISTERCOPIES++;
			}
		}
	}

    int result = temp[k/2].key;
    delete temp;
    return result;

}

void ParticaoMedian(int Esq, int Dir, int *i, int *j, Item *A, int k)
// Description: sort vector by a special pivot 
// Input: Esq, Dir, i, j, A, k
// Output: i, j
{
    Item w;
    *i = Esq; *j = Dir; 
    //get pivot
    int pivot = FindMedian(Esq,Dir,A,k);
    //swaping pivot right and left elements
    do
    {
        while (pivot > A[*i].key)
        {
            (*i)++;
            COMPARASIONS ++;
        }
        while (pivot < A[*j].key) 
        {
            (*j)--;
            COMPARASIONS ++;
        }
        if (*i <= *j)
        {
            w = A[*i];  REGISTERCOPIES++;
            A[*i] = A[*j]; REGISTERCOPIES++;
            A[*j] = w; REGISTERCOPIES++;
            (*i)++; (*j)--;
        }
    } while (*i <= *j);
}


void OrdenaMedian(int Esq, int Dir, Item *A, int k)
// Description: call partition until the vector is sorted
// Input: Esq, Dir, A, k
// Output: -
{ 
    int i, j;
    ParticaoMedian(Esq, Dir, &i, &j, A, k);
    if (Esq < j) OrdenaMedian(Esq, j, A, k);
    if (i < Dir) OrdenaMedian(i, Dir, A, k);
}

void QuickSortMedian(Item *A, int n, int k)
// Description: call respective sort function.
// Input: A, n, k
// Output: 
{
    OrdenaMedian(0, n-1, A, k);
}