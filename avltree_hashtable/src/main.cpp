//---------------------------------------------------------------------
// File      : main.cpp
// Subject   : main program; call main operations to menage the 
// Author    : Gabriel Henrique dos Santos Gonçalves (gabrielhenri.sg@gmail.com)
// Changes   : 2022-12-09 - file created
//             2022-12-14 - program finished - 1.0
//---------------------------------------------------------------------
#include"tree.hpp"
#include"hash.hpp"
#include"functions.hpp"
#include<iostream>
#include<fstream>
#include"msgassert.h"

using namespace std;

int main (int argc, char ** argv) {
     //argc and argv configuration
    opt s;
    Parse_Args(argc,argv,&s);
    
    //choosing between tree or hash implementation
    if(s.command=="arv"){
        //tree implementation
        TreeDictionary p(s.input,s.output);
        string line;
        //insert all file words in the tree
        p.CompleteTree();
        p.Print();
        //remove all words that have a meaning
        p.Update();
        p.Print();
        //destroy dictionary
        p.Destroy();
    }else if (s.command=="hash"){
        //hash implementation
        Hash x(s.input,s.output);
        //insert all file words in the hash table
        x.CompleteHash();
        x.PrintHash();
        //remove all words that have a meaning
        x.UpdateHash();
        x.PrintHash();
        //destroy dictionary
        x.DestroyHash();
    } else{
        cout<<"Comando inválido. Favor escolher entre a árvore e o hash.";
    }

    return 0;
}