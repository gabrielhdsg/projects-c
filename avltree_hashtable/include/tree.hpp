//---------------------------------------------------------------------
// File      : tree.hpp
// Subject   : 
// Author    : Gabriel Henrique dos Santos Gonçalves (gabrielhenri.sg@gmail.com)
// Changes   : 2022-12-09 - file created
//             2022-12-14 - program finished - 1.0
//---------------------------------------------------------------------

#ifndef TREE
#define TREE
#include <iostream>
#include <string>
#include<fstream>
#include"functions.hpp"

using namespace std;

/*-------------------Entry Class-------------------*/

class Entry
{
private:
    string value_;
    string type_;
    Queue *mng_;
    Entry *left_;
    Entry *right_;
    Entry *parent_;
public:
    Entry();
    void Insert(string line, bool reapeted = 0, Entry* before = NULL);
    string Print();

friend class AVLTree;
};

/*-----------------------Tree Class-------------------------*/

class AVLTree
{
private:
    Entry *root_;
    void RecursiveDeletion(Entry* y);
    void RecursiveInsertion(Entry* &y,string line, Entry* before = NULL);
    void InOrderPrint(Entry *y, fstream &output);
    void PosOrderUptade(Entry *&y);
    int BalanceFactor(Entry *y);
    void BalanceCheck(Entry *y);
    void RightRotation(Entry *y);
    void LeftRotation(Entry *y);
    int Height(Entry *y);
    void Predecessor(Entry *p, Entry *&r);
    void BalanceUpdate(Entry *y);
public:
    AVLTree();
    ~AVLTree();
    void Insert(string line);
    void Update();
    void PrintTree(fstream &output);
    void Clean();
};

/*-------------------TreeDictionary Class-------------------*/

class TreeDictionary
{
private:
    AVLTree data_;
    fstream fin_,fout_;
public:
    TreeDictionary(string input,string output);
    void CompleteTree();
    void Update();
    void Print();
    void Destroy();
};

#endif

