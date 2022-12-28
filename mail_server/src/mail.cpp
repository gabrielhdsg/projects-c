//---------------------------------------------------------------------
// File      : mail.cpp
// Subject   : this file has the user list and e-mail list methods
// Author    : Gabriel Henrique dos Santos Gonçalves (gabrielhenri.sg@gmail.com)
// Changes   : 2022-09-09 - file created
//             2022-09-13 - file finished - 1.0
//---------------------------------------------------------------------
#include<iostream>
#include<string>
#include "mail.hpp"


using namespace std;

Mailbox::Mailbox()
// Description: initialize Mailbox variable
// Input: -
// Output: -
{
    next_=NULL;
    priority_=-1;
}

User::User()
// Description: initialize User variable
// Input: -
// Output: -
{
    id_=-1;
    next_=NULL;
    emails_=new Maillist;

}

List::List()
// Description: initialize List variable
// Input: -
// Output: -
{
    size_=0;
    first_=new User;
    last_=first_;
}

List::~List()
// Description: List destructor
// Input: -
// Output: -
{   
    Clean();
    delete first_;
}

void List::Clean() 
// Description: List restart
// Input: -
// Output: -
{
    size_= 0;
}

User* List::PositionById(int id,  bool before) 
// Description: by an user id the function returns a pointer to its position in the list
// Input: id, before
// Output: a variable User
{
    User *p, *q; int pos=0;
    //creation of two variables. one is the position before the s
    p = first_->next_;
    q = first_;
    for(pos=1; pos<=size_; pos++){
        if (p->id_==id)
            break;
        p = p->next_;
        q = q->next_;
    }
    if (p==NULL)
        return NULL;
// if before is true goes to the previous position
    if(before) {
        return q;
    }
    else {
        return p;   
    }
}

void List::SetUser(int id)
// Description: set a new user in the list
// Input: id
// Output: -
{
    if (PositionById(id,false)==NULL) {
        User *p;
        p = new User();
        p->id_ = id;
        last_->next_ = p;
        last_ = p;
        size_++;
        cout<<"OK: CONTA "<<id<<" CADASTRADA"<<endl;
    }
    else{
        cout<<"ERRO: CONTA "<<id<<" JA EXISTENTE"<<endl;
    }
}

void List::RemoveUser(int id){
// Description: remove an user of the list
// Input: id
// Output: -
    User *p, *q;
    p=PositionById(id, true);
    if(p==NULL){
        cout<<"ERRO: CONTA "<<id<< " NAO EXISTE"<<endl;
    } else {
        q=p->next_;
        p->next_=q->next_;
        size_--;
        delete q;
        cout<<"OK: CONTA "<<id<<" REMOVIDA"<<endl;
        if(p->next_==NULL)
            last_=p;
    }
}

void List::SendMessage(int id, int p, string msg)
// Description: add a message in the user's Maillist
// Input: id, p(priority), msg
// Output: -
{
    User *q;
    q = PositionById(id, false);
    if (q==NULL) {
        cout<<"ERRO: CONTA "<<id<< " NAO EXISTE"<<endl;
    } else {
        q->emails_->RecieveMessage(p,msg);
        cout<<"OK: MENSAGEM PARA "<<id<<" ENTREGUE"<<endl;
    }
    
}

void List::ConsultMessage(int id)
// Description: consult the first message of the user's Maillist
// Input: id
// Output: -
{
    User *q;
    q = PositionById(id,false);
    if (q==NULL){
        cout<<"ERRO: CONTA "<<id<< " NAO EXISTE"<<endl;
    } else {
        if (q->emails_->GetSize()==0) {
            cout<<"CONSULTA "<<id<<": CAIXA DE ENTRADA VAZIA"<<endl;
        }
        else {
            cout<<"CONSULTA "<<id<<":"<< q->emails_->RemoveMessage()<<endl;
        }
    }
}

Maillist::Maillist()
// Description: inizialize Maillist variable
// Input: -
// Output: -
{
    size_=0;
    first_=new Mailbox;
    last_=first_;
}

Maillist::~Maillist()
// Description: Maillist destructor
// Input: -
// Output: -
{
    Clean();
    delete first_;
}

void Maillist::Clean()
// Description: clean Maillist variables
// Input: -
// Output: -
{
    size_=0;
}

int Maillist::GetSize()
// Description: returns Maillist size
// Input: -
// Output: size of the Maillist
{
    return size_;
}

Mailbox* Maillist::PositionByPriority(int p)
// Description: returns a pointer to the position right after the priority informed
// Input: p(priority)
// Output: Maillist position
{
    Mailbox *r, *q; int i;
    r = first_->next_;
    q = first_;
    for(i=1;i<=size_;i++){
        if (r->priority_<p)
            break;
        r = r->next_;
        q = q->next_;
    }
    
    return q;
}

void Maillist::RecieveMessage(int p, string msg) 
// Description: add an message in the user's Maillist
// Input: p(priority), message
// Output: -
{
    Mailbox *r, *q;
    r=PositionByPriority(p);
    q=new Mailbox;
    q->message_=msg;
    q->priority_=p;
    q->next_=r->next_;
    r->next_=q;
    size_++;
    if(q->next_==NULL) {
        last_= q;
    }
}

string Maillist::RemoveMessage()
// Description: remove the first message of the user's Maillist after being read
// Input: -
// Output: message read 
{
    Mailbox *r, *q;
    string aux;
    q = first_; 
    r = first_->next_;
    q->next_= r->next_;
    aux=r->message_;
    size_--;
    delete r;
    return aux;
}