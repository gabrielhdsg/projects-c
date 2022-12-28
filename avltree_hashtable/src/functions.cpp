//---------------------------------------------------------------------
// File      : functions.cpp
// Subject   : 
// Author    : Gabriel Henrique dos Santos Gonçalves (gabrielhenri.sg@gmail.com)
// Changes   : 2022-12-09 - file created
//             2022-12-14 - program finished - 1.0
//---------------------------------------------------------------------

#include<iostream>
#include<string>
#include<getopt.h>
#include<string.h>
#include"functions.hpp"

using namespace std;

/*-----------------------Meaning Class----------------------*/

Meaning::Meaning()
// Description: initializate meaning variable
// Input: -
// Output: -
{
    text_.clear();
    next_=NULL;
}

/*-----------------------Queue Class-------------------------*/

Queue::Queue()
// Description: initialize Queue variable
// Input: -
// Output: -
{
    size_=0;
    //head cell
    first_=new Meaning; 
    last_=first_;
}

Queue::~Queue()
// Description: Queue destructor
// Input: -
// Output: -
{   
    Clean();
    delete first_;
}

void Queue::Clean() 
// Description: remove Queue elements
// Input: -
// Output: -
{
    Meaning *p;
    p=first_->next_;
    while (p!=NULL)
    {
        first_->next_=p->next_;
        delete p;
        p=first_->next_;
    }
    size_= 0;
    last_=first_;
}

void Queue::Insert(string item)
// Description: insert new meaning
// Input: -
// Output: -
{
    Meaning *p;
    p=new Meaning;
    p->text_=item;
    last_->next_=p;
    last_=p;
    size_++;
}

bool Queue::Empty()
// Description: check if queue is empty
// Input: -
// Output: true or false
{
   if (this->size_==0)
   {
        return true;
   }else{
        return false;
   }
    
}

string Queue::GetItens()
// Description: get queue all meanings
// Input: -
// Output: meanings
{
    Meaning *p;
    string result;
    int i=1;
    p=first_->next_;
    while (p!=NULL)
    {
        result += to_string(i) + ". " + p->text_ + "\n";
        p = p->next_;
        i++;
    }
    return result;

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
     opt->command[0] = 0;
    
     //getopt - letter indicates an operation
     while ((c = getopt(argc, argv, "i:o:t:p:")) != EOF)
       switch(c) {
        case 'i':
               strcpy(opt->input,optarg);
		    break;
        case 'o':
               strcpy(opt->output,optarg);
		    break;
        case 't':
               opt->command=optarg;
		    break;
        case 'p':
               strcpy(opt->register_file,optarg);
		    break;
       }

}

