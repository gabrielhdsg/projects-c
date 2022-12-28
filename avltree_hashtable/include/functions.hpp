//---------------------------------------------------------------------
// File      : functions.hpp
// Subject   :  
// Author    : Gabriel Henrique dos Santos Gonçalves (gabrielhenri.sg@gmail.com)
// Changes   : 2022-12-09 - file created
//             2022-12-14 - program finished - 1.0
//---------------------------------------------------------------------
#ifndef DIC
#define DIC

#include <iostream>
#include <string>

using namespace std;

/*-------------------Meaning Class-------------------*/

class Meaning
{
private:
    string text_;
    Meaning *next_;
public:
    Meaning();

friend class Queue; 
};


/*-------------------Queue Class-------------------*/

class Queue
{
private:
    int size_;
    Meaning *first_;
    Meaning *last_; 
public:
    Queue();
    bool Empty();
    void Insert(string q);
    string GetItens();
    void Clean();
    ~Queue();
};

/*-------------------Program Struct------------------*/
struct opt {
    char input[100];
    char output[100];
    char register_file[100];
    string command;
};

void Parse_Args(int argc,char **argv, opt *opt);

#endif