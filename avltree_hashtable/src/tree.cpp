//---------------------------------------------------------------------
// File      : tree.cpp
// Subject   : 
// Author    : Gabriel Henrique dos Santos Gonçalves (gabrielhenri.sg@gmail.com)
// Changes   : 2022-12-09 - file created
//             2022-12-14 - program finished - 1.0
//---------------------------------------------------------------------

#include"tree.hpp"
#include<iostream>
#include<string>
#include<msgassert.h>
#include<fstream>
#include<sstream>

using namespace std;

/*-----------------------TreeDictionary Class-------------------------*/

TreeDictionary::TreeDictionary(string input,string output)
// Description: initializate files
// Input: -
// Output: -
{
    fin_.open(input,ifstream::in);
    erroAssert(fin_.is_open(),"Nao foi possivel abrir o arquivo de entrada");
    fout_.open(output,ofstream::out);
    erroAssert(fout_.is_open(),"Nao foi possivel criar o arquivo de saída");
}


void TreeDictionary::CompleteTree()
// Description: insert all the file words to the dictionary
// Input: -
// Output: -
{
    string aux;
    while (getline(fin_,aux))
    {
        data_.Insert(aux);
    }
}

void TreeDictionary::Print()
// Description: print all dictionary elements
// Input: -
// Output: -
{
    data_.PrintTree(fout_);
}

void TreeDictionary::Update()
// Description: remove all elements that have a meaning
// Input: -
// Output: -
{   
    data_.Update();
}

void TreeDictionary::Destroy()
// Description: destroy dictionary, removing it from memory
// Input: -
// Output: -
{
    data_.Clean();
}

/*-----------------------Entry Class-------------------------*/
Entry::Entry()
// Description: Entry initialization
// Input: -
// Output: -
{
    mng_=new Queue;
    left_=NULL;
    right_=NULL;
    parent_=NULL;
    value_.clear();
}

string Entry::Print()
// Description: print Entry with type and meaning
// Input: -
// Output: result
{
    string result, aux;
    aux=value_;
    aux=value_.substr(0,value_.size()-4);
    result = aux + " (" + this->type_ + ")\n";
    if(!this->mng_->Empty())
        result += (this->mng_->GetItens());
    return result;
}

void Entry::Insert(string line, bool reapeted, Entry* before)
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
        this->value_+="   "+type_;
        if(pos+1<int(line.size()))
            meaning=line.substr(pos+2,line.size());
        if(!meaning.empty())
            this->mng_->Insert(meaning);
        this->parent_=before;
    } else{
        //if word is reapeted only the meaning(if it exists) will be add
        stringstream sin(line);
        string meaning,aux,type,word;
        sin>>type;sin>>word;
        while (sin>>aux)
        {
            meaning+=aux + " ";
        }
        if(!meaning.empty())
            this->mng_->Insert(meaning);
    }
}
/*-----------------------Tree Class-------------------------*/

AVLTree::AVLTree()
// Description: tree initialization
// Input: -
// Output: -
{
    root_=NULL;
}

AVLTree::~AVLTree()
// Description: tree destructor
// Input: -
// Output: -
{
    Clean();
}

void AVLTree::Clean()
// Description: clean all tree
// Input: -
// Output: -
{
    RecursiveDeletion(root_);
    root_=NULL;
}

void AVLTree::RecursiveDeletion(Entry *y)
// Description: remove recursively all itens bellow the node
// Input: y
// Output: -
{
    if(y!=NULL){
        RecursiveDeletion(y->left_);
        RecursiveDeletion(y->right_);
        delete y;
    }
}

void AVLTree::PrintTree(fstream &output)
// Description: call InOrder function to print the tree
// Input: file
// Output: -
{
    InOrderPrint(this->root_,output);
}

void AVLTree::InOrderPrint(Entry *y,fstream &output)
// Description: print tree in order
// Input: y and file
// Output: -
{
    if (y!=NULL)
    {
        InOrderPrint(y->left_,output);
        output<<y->Print();
        InOrderPrint(y->right_,output);
    }
}


void AVLTree::Insert(string line)
// Description: call insertion method 
// Input: line
// Output: -
{
    RecursiveInsertion(this->root_,line);
}

int Compare(string value,string x, bool remove = 0)
// Description: compare node word and line word
// Input: node value, a string an a bool variable
// Output: comparation result
{
    if (remove==0)
    {
        string aux, word;
        int pos;
        aux = x.substr(0,1);
        pos = x.find("]");
        word = x.substr(3,pos-3);
        word+="   "+aux;
        return value.compare(word);
    } else {
         return value.compare(x);
    }
    
}

void AVLTree::Predecessor(Entry *p, Entry *&r)
// Description: find predecessor node
// Input: node and path to your predecessor
// Output: -
{
    if(r->right_!=NULL) {
        Predecessor(p,r->right_);
        return;
    }
    p->value_=r->value_;
    p->type_=r->type_;
    p->mng_=r->mng_;
    p=r;
    if(r->left_!=NULL)
        r->left_->parent_=r->parent_;
    r=r->left_;
    delete p;
}

int Max(int v1, int v2)
// Description: return the biggest element
// Input: v1 and v2
// Output: -
{
    if (v1>v2)
    {
        return v1;
    }else{
        return v2;
    } 
}

void AVLTree::LeftRotation(Entry* y)
// Description: left rotation to balance the tree
// Input: y
// Output: -
{
    Entry *aux=y->right_;
    y->right_=aux->left_;
    if(aux->left_!=NULL)
        aux->left_->parent_=y;
    aux->left_ = y;
    aux->parent_=y->parent_;
    y->parent_=aux;
    if (aux->parent_!=NULL&&y->value_.compare(aux->parent_->value_)<0){
         aux->parent_->left_=aux;
    }
    else{
        if(aux->parent_!=NULL)
            aux->parent_->right_=aux;
    }
    y=aux;
}

void AVLTree::RightRotation(Entry* y)
// Description: right rotation to balance the tree
// Input: y
// Output: -
{
    Entry *aux=y->left_;
    y->left_=y->left_->right_;
    if(y->left_!=NULL)
        y->left_->parent_=y;
    aux->right_ = y;
    aux->parent_=y->parent_;
    y->parent_=aux;
    if (aux->parent_!=NULL&&y->value_.compare(aux->parent_->value_)<0){
        aux->parent_->left_=aux;
    }
    else{
        if(aux->parent_!=NULL)
            aux->parent_->right_=aux;
    }
    y=aux;
}

void AVLTree::BalanceCheck(Entry* y)
// Description: check tree balance by the node
// Input: y 
// Output: -
{
    Entry *aux = y;
    while (aux!=NULL)
    {
        if(BalanceFactor(aux)>1){
            if (BalanceFactor(aux->right_)<=-1)
                {
                    RightRotation(aux->right_);
                    LeftRotation(aux);
                } else {
                    //left rotation
                    LeftRotation(aux);
                }
        }else if(BalanceFactor(aux)<-1){
            if (BalanceFactor(aux->left_)>=1)
                {
                    LeftRotation(aux->left_);
                    RightRotation(aux);
                }else {
                    //right rotation
                    RightRotation(aux);
                }
        }
        if (aux->parent_==NULL)
            this->root_=aux;
        aux = aux->parent_;
    }
     
}

void AVLTree::RecursiveInsertion(Entry* &y,string line, Entry* before)
// Description: insert new item to the tree recursively
// Input: node and line
// Output: -
{
    if (y==NULL)
    {
        y = new Entry();
        y->Insert(line, 0,before);
        BalanceCheck(y);
    }else {
        if(Compare(y->value_,line)>0)
        {
            //node is greater than insert value
            RecursiveInsertion(y->left_,line, y);
        }else if(Compare(y->value_,line)<0){
            //node is less than insert value
            RecursiveInsertion(y->right_,line, y);
        }else {
            //node and insert value are equal
            y->Insert(line, 1);
        }
    }
}


void AVLTree::PosOrderUptade(Entry *&y)
// Description: walk through the tree checking each element
// Input: y
// Output: -
{
    if (y!=NULL)
    {
        PosOrderUptade(y->left_);
        PosOrderUptade(y->right_);
        if(y->mng_->Empty()==0)
            {
                Entry *aux;
                if (y->right_==NULL)
                {
                    aux=y;
                    y=y->left_;
                    if(y!=NULL)
                        y->parent_=aux->parent_;
                    delete(aux);
                } else if (y->left_==NULL) {
                    aux=y;
                    y=y->right_;
                    if(y!=NULL)
                        y->parent_=aux->parent_;
                    delete(aux);
                } else {
                    Predecessor(y,y->left_);
                }
            }
    }
}

void AVLTree::BalanceUpdate(Entry *y)
// Description: balance the tree after an update
// Input: -
// Output: -
{
    if(y!=NULL)
    {
        BalanceUpdate(y->left_);
        BalanceUpdate(y->right_);
        if(BalanceFactor(y)>1){
                if (BalanceFactor(y->right_)<=-1)
                    {
                        RightRotation(y->right_);
                        LeftRotation(y);
                  } else {
                    //left rotation
                     LeftRotation(y);
                    }
            }else if(BalanceFactor(y)<-1){
                if (BalanceFactor(y->left_)>=1)
                    {
                       LeftRotation(y->left_);
                       RightRotation(y);
                 }else {
                        //right rotation
                        RightRotation(y);
                    }
        }
        if (y->parent_==NULL)
            this->root_=y;
    }
}


void AVLTree::Update()
// Description: update tree by removing all word with meaning
// Input: -
// Output: -
{
    PosOrderUptade(root_);
    BalanceUpdate(root_);
}

int AVLTree::Height(Entry *y)
// Description: calculate node height recursively
// Input: y
// Output: node height
{
    if (y==NULL)
        return 0;
    return 1 + Max(Height(y->left_),Height(y->right_));
}


int AVLTree::BalanceFactor(Entry *y)
// Description: returns node balance factor
// Input: y
// Output: node bf
{
    if (y==NULL)
        return 0;
    int balance = Height(y->right_) - Height(y->left_);
    return balance;
}
