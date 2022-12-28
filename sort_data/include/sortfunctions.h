//---------------------------------------------------------------------
// File      : sortfunctions.h
// Subject   : this file has the program functions, methods and list declarations
// Author    : Gabriel Henrique dos Santos Gonçalves (gabrielhenri.sg@gmail.com)
// Changes   : 2022-11-80 - file created
//             2022-11-22 - program finished - 1.0
//---------------------------------------------------------------------
#ifndef QUICKSORT  
#define QUICKSORT

#include<iostream>
#include<string>

using namespace std;

extern int COMPARASIONS;
extern int REGISTERCOPIES;

/*-------------------------------------------------------------------Program Structs ------------------------------------------------------------------------------------*/
struct opt {
    char input[100];
    char output[100];
    int random;
    int command;
    int median;
    int select;
};

struct Item
{
    int key;
    char chains[15][200];
    float real[10];

};

/*----------------------------------------------------------------Pile Structs and Classes ----------------------------------------------------------------------------------*/

struct Index
{
    int left;
    int right;
};

class TipoCelula
{
    public:
        TipoCelula();
    private:
        Index direction;
        TipoCelula *prox;
    friend class Pilha;
};
/*-------------------------------------------------------------------Pile Class-----------------------------------------------------------------------------------*/
class Pilha
{
    public:
        Pilha();
        virtual ~Pilha();
        void Empilha(Index item);
        Index Desempilha();
        bool Empty();
        void Limpa();
    private:
        int size_;
        TipoCelula* topo;
};

/*-------------------------------------------------------------------Algorithms  Funcions-----------------------------------------------------------------------------------*/

void QuickSortRecursive(Item *A, int n);
void QuickSortMedian(Item *A, int n, int k);
void QuickSortNoRecursive(Item *A, int n);
void QuickSortSelection(Item *A, int n, int m);
void QuickSortSmartPile(Item *A, int n);
void MergeSort(Item *A,int n);
void HeapSort(Item *A,int n);
void RandomGenerate(Item *A, int random, int vecsize);
void Parse_Args(int argc,char **argv, opt *opt);
#endif