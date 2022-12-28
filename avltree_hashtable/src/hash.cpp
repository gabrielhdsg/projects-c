//---------------------------------------------------------------------
// File      : hash.cpp
// Subject   : 
// Author    : Gabriel Henrique dos Santos Gonçalves (gabrielhenri.sg@gmail.com)
// Changes   : 2022-12-09 - file created
//             2022-12-14 - program finished - 1.0
//---------------------------------------------------------------------

#include"hash.hpp"
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include"functions.hpp"
#include"msgassert.h"

using namespace std;

/*-----------------------Entry Class-------------------------*/
EntryHash::EntryHash()
// Description: Entry initialization
// Input: -
// Output: -
{
    mng_=new Queue;
    value_.clear();
}

string EntryHash::Print()
// Description: print Entry with type and meaning
// Input: -
// Output: result
{
    string result, aux;
    aux=value_;
    aux=value_.substr(0,value_.size()-3);
    result = aux + " (" + this->type_[0] + ")\n";
    if(!this->mng_->Empty())
        result += (this->mng_->GetItens());
    return result;
}

void EntryHash::Insert(string line, bool reapeted)
// Description: insert values into Entry variable
// Input: line and repeated variable
// Output: -
{
    if (reapeted==0){
        //if word does not exist the whole struct will be add
        string meaning,aux;
        this->type_=line.substr(0,1);
        int pos=line.find("]");
        this->value_=line.substr(3,pos-3);
        this->key_=value_;
        this->value_+="  "+type_;
        if(pos+1<int(line.size()))
            meaning=line.substr(pos+2,line.size());
        if(!meaning.empty())
            this->mng_->Insert(meaning);
    } else{
        //if word is reapeted only the meaning(if it exists) will be add
        stringstream sin(line);
        string meaning,aux,dump;
        sin>>dump;sin>>dump;
        while (sin>>aux)
        {
            meaning+=aux + " ";
        }
        if(!meaning.empty())
            this->mng_->Insert(meaning);
    }
}

string EntryHash::GetWord()
{
    return value_;
}

/*-----------------------Hash Class-------------------------*/

Hash::Hash(string input,string output)
// Description: hash initializer function 
// Input: input and output name
// Output: -
{
    int count=0; string aux;
    fin_.open(input,ifstream::in);
    erroAssert(fin_.is_open(),"Nao foi possivel abrir o arquivo de entrada");
    fout_.open(output,ofstream::out);
    erroAssert(fout_.is_open(),"Nao foi possivel criar o arquivo de saída");
    while(getline(fin_,aux))
        count++;
    size_=count;
    fin_.clear();
    fin_.seekg(0);
    table_=new EntryHash[count];
    empty_=new bool[count];
    removed_=new bool[count];
    for (int y = 0; y < count; y++)
    {
        empty_[y]=true;
        removed_[y]=false;
    }
    
}

int Hash::HashFunction(string word)
// Description: hash function; calculate word position  
// Input: word
// Output: position
{
    int result=0,multiplier=1;
    for (int i = 0; i < int(word.length()); i++)
    {
        result+=word[i]*multiplier;
        multiplier++;
    }
    return result % size_;
}


bool Hash::SearchItem(string word)
// Description: check if a word is in the table
// Input: word
// Output: true or false
{
    int pos,i;
    pos=HashFunction(word);
    i=0;
    while((i<size_)&&!empty_[(pos+i)%size_]&&table_[(pos+i)%size_].value_!=word)
        i++;
 
    if ((table_[(pos+i)%size_].value_==word)&&!removed_[(pos+i)%size_])
    {
        //item is found
        return true;
    }else{
        //item is not in the table
        return false;
    }
        
}

void Hash::InsertHash(string line)
// Description: insert a new item in the table
// Input: file line
// Output: -
{
    int pos;
    EntryHash aux;
    string word,type; 
    stringstream sin(line);
    sin>>type;sin>>word;
    word.erase(0,1);
    word.erase(word.size()-1);
    word+="  "+type;
    if(SearchItem(word))
    {
        //reapeted item
        pos=HashFunction(word);
        int u=0;
        while(table_[(pos+u)%size_].value_!=word)
            u++;
        table_[(pos+u)%size_].Insert(line,1);
    }else{
        //new item
        aux.Insert(line);
        pos=HashFunction(word);
        int i=0;
        while((i<size_)&&!empty_[(pos+i)%size_]&&!removed_[(pos+i)%size_])
            i++;
        if(i==size_){
            cout<<"Tabela Cheia.";
            return;
        }
        else{
            table_[(pos+i)%size_]=aux;
            empty_[(pos+i)%size_]=false;
            removed_[(pos+i)%size_]=false;
        }
    }

}

void Hash::Partition(int Esq, int Dir, int *i, int *j, EntryHash *A)
// Description: sort vector by a pivot
// Input: Esq, Dir, i, j, A
// Output: i, j
{
    bool p,t;
    EntryHash x, w;
    *i = Esq; *j = Dir;
    //get pivot
    x = A[(*i + *j)/2];  
    //swaping pivot right and left elements
    do
    {
        while (x.GetWord().compare(A[*i].GetWord())>0) 
        {
            (*i)++;
        }
        while (x.GetWord().compare(A[*j].GetWord())<0) 
        {
            (*j)--;
        }
        if (*i <= *j)
        {
            p=empty_[*i];
            t=removed_[*i];
            w = A[*i];
            empty_[*i]=empty_[*j]; 
            removed_[*i]=removed_[*j];
            A[*i] = A[*j];
            A[*j] = w;
            removed_[*j]=t;
            empty_[*j]=p;

            (*i)++; (*j)--;
        }
    } while (*i <= *j);
}

void Hash::Sort(int Esq, int Dir, EntryHash *A)
// Description: call partition until the vector is sorted
// Input: Esq, Dir, A
// Output: -
{ 
    int i, j;
    Partition(Esq, Dir, &i, &j, A);
    if (Esq < j) Sort(Esq, j, A);
    if (i < Dir) Sort(i, Dir, A);
}

void Hash::QuickSortRecursive(EntryHash *A, int n)
// Description: call respective sort function.
// Input: A, n
// Output: -
{
    Sort(0, n-1, A);
}


void Hash::PrintHash()
// Description: print table itens ordered using a quicksort
// Input: -
// Output: -
{
    int i=0; 
    while(i<size_)
    {
        if(!empty_[i]&&!removed_[i])
        {
            fout_<<table_[i].Print();
        }
        i++;
    }
}

void Hash::UpdateHash()
// Description: remove all entries with meaning
// Input: -
// Output: -
{
    int i=0;
    while(i<size_)
    {
        if(!table_[i].mng_->Empty())
        {
            removed_[i]=true;
        }
        i++;
    }
}

void Hash::DestroyHash()
// Description: delete hash variable
// Input: -
// Output: -
{
    delete [] empty_;
    delete [] removed_;
    delete [] table_;
    fin_.close();
    fout_.close();
}

void Hash::CompleteHash()
// Description: fill table with file words
// Input: -
// Output: -
{
    string aux;
    while (getline(fin_,aux))
    {
        this->InsertHash(aux);
    }
    QuickSortRecursive(this->table_,size_);
}



