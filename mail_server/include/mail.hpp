//---------------------------------------------------------------------
// File      : mail.hpp
// Subject   : this file has the user list and e-mail list methods declarations
// Author    : Gabriel Henrique dos Santos Gonçalves (gabrielhenri.sg@gmail.com)
// Changes   : 2022-09-09 - file created
//             2022-09-13 - file finished - 1.0
//---------------------------------------------------------------------
#ifndef MAIL_H
#define MAIL_H
#include <iostream>
#include <string>

using namespace std;

/*-----------------------------------------------------------------Mailbox Class----------------------------------------------------------------------------------*/
class Mailbox 
{
private:
    string message_;
    int priority_;
    Mailbox* next_;
public:
    Mailbox();

friend class Maillist; 
};

/*-----------------------------------------------------------------Maillist Class---------------------------------------------------------------------------------*/

class Maillist
{
private:
    Mailbox* first_;
    Mailbox* last_;
    int size_;
    Mailbox* PositionByPriority(int p);
    void Clean();
public:
    Maillist();
    ~Maillist();
    
    void RecieveMessage(int p, string msg);
    string RemoveMessage();
    int GetSize();
};

/*-------------------------------------------------------------------User Class-----------------------------------------------------------------------------------*/

class User
{
private:
    int id_;
    User* next_;
    Maillist* emails_;

public:
    User();

friend class List;    
};

/*-------------------------------------------------------------------List Class-----------------------------------------------------------------------------------*/

class List
{
private:
    User* first_;
    User* last_;
    int size_;
    User* PositionById(int id,  bool before);
    void Clean();

public:
    List();
    ~List();

    void SetUser(int id);
    void RemoveUser(int id);
    void SendMessage(int id, int p, string msg);
    void ConsultMessage(int id);

};

#endif