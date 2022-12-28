//---------------------------------------------------------------------
// File      : sortfunctions.cpp
// Subject   : this file has the program functions, methods and list code
// Author    : Gabriel Henrique dos Santos Gonçalves (gabrielhenri.sg@gmail.com)
// Changes   : 2022-11-80 - file created
//             2022-11-22 - program finished - 1.0
//---------------------------------------------------------------------
#include"sortfunctions.h"
#include<iostream>
#include <stdlib.h> 
#include<getopt.h>
#include<string.h>   

using namespace std;

Pilha::Pilha()
// Description: initialize pile variable
// Input: -
// Output: -
{
    topo = NULL;
    size_=0;
}

Pilha::~Pilha()
// Description: pile destructor
// Input: -
// Output: -
{
    Limpa();
}

TipoCelula::TipoCelula()
// Description: initialize TipoCelula variable
// Input: -
// Output: -
{
    direction.left=-1;
    direction.right=-1;
    prox = NULL;
}

void Pilha::Empilha(Index item)
// Description: insert new Index in the pile
// Input: Index
// Output: -
{
    TipoCelula *nova;
    nova = new TipoCelula();
    nova->direction.left = item.left;
    nova->direction.right = item.right;
    nova->prox = topo;
    topo = nova;
    size_++;
};

Index Pilha::Desempilha()
// Description: remove Index from the pile
// Input: -
// Output: Index
{
    Index aux; TipoCelula *p;
    if(size_ == 0)
        cout<<"Pile empty!!";
    aux = topo->direction;
    p = topo;
    topo = topo->prox;
    delete p;
    size_--;
    return aux;
};

void Pilha::Limpa()
// Description: pile clean
// Input: -
// Output: -
{
    while(!Empty())
        Desempilha();
}

bool Pilha::Empty()
// Description: check if pile is empty
// Input: -
// Output: -
{
    return size_==0;
}

void RandomGenerate(Item *A, int random, int vecsize)
// Description: insert random values into the array.
// Input: A, random, vecsize
// Output: -
{
    srand (random);
    for (int i = 0; i < vecsize; i++)
    {
        A[i].key=rand();
    }
}

void Parse_Args(int argc,char **argv, opt *opt) {
// Description: get console commands
// Input: argc, argv, opt 
// Output: opt

     //auxiliary vars
     int c;

    //inicialize global var
     opt->input[0] = 0;
     opt->output[0] = 0;
     opt->random = 0;
     opt->command = 0;
     opt->median = 0;
     opt->select = 0;
    
     //getopt - letter indicates an operation
     while ((c = getopt(argc, argv, "v:s:i:o:k:m:")) != EOF)
       switch(c) {
         case 'v': 
	           opt->command = stoi(optarg);
		    break;
         case 's':
               opt->random = stoi(optarg);
		    break;
        case 'i':
               strcpy(opt->input,optarg);
		    break;
        case 'o':
               strcpy(opt->output,optarg);
		    break;
        case 'k':
               opt->median = stoi(optarg);
		    break;
        case 'm':
               opt->select = stoi(optarg);
		    break;
       }

}