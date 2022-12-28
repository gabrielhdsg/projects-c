//---------------------------------------------------------------------
// File      : quicksortsmartpile.cpp
// Subject   : quicksort smart pile algorithm (reference: discipline classes - Estrutura de Dados/UFMG-2022)
// Author    : Gabriel Henrique dos Santos Gonçalves (gabrielhenri.sg@gmail.com)
// Changes   : 2022-11-80 - file created
//             2022-11-22 - program finished - 1.0
//---------------------------------------------------------------------
#include<iostream>
#include"sortfunctions.h"


using namespace std;

void ParticaoSmartPile(int Esq, int Dir, int *i, int *j, Item *A)
{
    Item x, w;
    *i = Esq; *j = Dir;
    //get pivot
    x = A[(*i + *j)/2];
    //swaping pivot right and left elements
    do
    {
        while (x.key > A[*i].key) 
        {
            (*i)++;
            COMPARASIONS++;
        }
        while (x.key < A[*j].key) 
        {
            (*j)--;
            COMPARASIONS++;
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

void QuickSortSmartPile(Item *A, int n) {
// Description: non recursive quicksort using a pile to store index
// Input: A, n
// Output: -
    Pilha pilha;
    Index item; 
    int left, right, i, j;

    left = 0;
    right = n-1;
    item.right = right;
    item.left = left;
    pilha.Empilha(item);
    //swaping pivot right and left elements 
    do
        if (right > left) {
            ParticaoSmartPile(left, right,&i,&j,A);
            //smart pile asking which side is the minor value
            if ((j-left)>(right-i)) {
                item.right = j;
                item.left = left;
                pilha.Empilha(item);
                left = i;
            }
            else {
                item.left = i;
                item.right = right;
                pilha.Empilha(item);
                right = j;
            }
        }
        else {
        item=pilha.Desempilha();
        right = item.right;
        left = item.left;
    } while (!pilha.Empty());
    pilha.Limpa();
}