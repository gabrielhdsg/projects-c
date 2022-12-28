//---------------------------------------------------------------------
// File      : quicksortop.cpp
// Subject   : main program; call main operations to menage the mail list
// Author    : Gabriel Henrique dos Santos Gonçalves (gabrielhenri.sg@gmail.com)
// Changes   : 2022-11-80 - file created
//             2022-11-22 - program finished - 1.0
//---------------------------------------------------------------------
#include<iostream>
#include<sstream>
#include"msgassert.h"
#include <sys/resource.h>
#include<fstream>
#include"sortfunctions.h"


using namespace std;

int COMPARASIONS = 0;
int REGISTERCOPIES = 0;

int main (int argc, char ** argv) {

    //argc and argv configuration
    opt s;
    Parse_Args(argc,argv,&s);
    
    //creating input and output
    fstream fin(s.input,ifstream::in);
    erroAssert(fin.is_open(),"Nao foi possivel abrir o arquivo de entrada");
    fstream fout(s.output,ofstream::out);
    erroAssert(fout.is_open(),"Nao foi possivel criar o arquivo de saída");
    
    //variables that will recieve information from file
    int cycles, size;
    fin>>cycles;
    for(int i = 0; i<cycles; i++)
    {    
        //creating time usage variables
        struct rusage resources;
        int rc;
        double utime, stime, total_time;
        //generating random vector
        fin>>size;
        Item *vector;
        vector= new Item[size];
        RandomGenerate(vector,s.random, size);

        if (s.command==1)
        {
            //if the command informed by input is to use recursive quicksort
            QuickSortRecursive(vector, size);
        } else if (s.command==2) 
        {
            //if the command informed by input is to use median quicksort
            //check if median has a valid value
            if (s.median<=0)
            {
                cout<<"Mediana menor ou igual  zero. Valor padrão (3) será considerado."<<endl;
                s.median = 3;
            }    
            QuickSortMedian(vector, size, s.median);
        } else if (s.command==3) 
        {
            //if the command informed by input is to use selection quicksort
            //check if selection has a valid value
            if (s.select<=0)
            {
                cout<<"Seleção menor ou igual  zero. Valor padrão (1000) será considerado."<<endl;
                s.select = 1000;
            } 
            QuickSortSelection(vector, size, s.select);
        }else if (s.command==4) 
        {
            //if the command informed by input is to use non recursive quicksort
            QuickSortNoRecursive(vector, size);
        }else if (s.command==5) 
        {
            //if the command informed by input is to use smart non recursive quicksort 
            QuickSortSmartPile(vector, size);
        }else if (s.command==6)
        {
            //if the command informed by input is to use mergesort
            MergeSort(vector, size);
        }else if (s.command==7)
        {
            //if the command informed by input is to use heapsort
            HeapSort(vector, size);
        }

        if((rc = getrusage(RUSAGE_SELF, &resources)) != 0)
            perror("getrusage failed");
        //getting time usage and writing it on output file
        utime = (double) resources.ru_utime.tv_sec + 1.e-6 * (double) resources.ru_utime.tv_usec;
        stime = (double) resources.ru_stime.tv_sec + 1.e-6 * (double) resources.ru_stime.tv_usec;
        total_time = utime+stime; 
        fout<<size<<" "<<utime<<" "<<stime<<" "<<total_time<<" "<<COMPARASIONS<<" "<<REGISTERCOPIES<<endl;
        //delete random vector created
        delete vector;
    }

    //closing files
    fin.close();
    fout.close();
    
    //end file
    return 0;
}