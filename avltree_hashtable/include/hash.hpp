//---------------------------------------------------------------------
// File      : hash.hpp
// Subject   :  
// Author    : Gabriel Henrique dos Santos Gonçalves (gabrielhenri.sg@gmail.com)
// Changes   : 2022-12-09 - file created
//             2022-12-14 - program finished - 1.0
//---------------------------------------------------------------------

#ifndef HASH
#define HASH
#include <iostream>
#include <string>
#include<fstream>
#include"functions.hpp"

using namespace std;

/*-------------------Entry Class-------------------*/

class EntryHash
{
private:
    string value_;
    string key_;
    string type_;
    Queue *mng_;
    
    public:
    EntryHash();
    void Insert(string line, bool reapeted = 0);
    string Print();
    string GetWord();

friend class Hash;
};

/*-------------------Hash Class-------------------*/

class Hash
{
private:
    int size_;
    int HashFunction(string key);
    void InsertHash(string line);
    bool SearchItem(string word);
    void Partition(int Esq, int Dir, int *i, int *j, EntryHash *A);
    void Sort(int Esq, int Dir, EntryHash *A);
    void QuickSortRecursive(EntryHash *A, int n);
    EntryHash *table_;
    bool *empty_;
    bool *removed_;
    fstream fin_,fout_;
public:
    Hash(string input,string output);
    void CompleteHash();
    void DestroyHash();
    void PrintHash();
    void UpdateHash();
    
};




#endif