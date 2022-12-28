//---------------------------------------------------------------------
// File      : main.cpp
// Subject   : main program; call main operations to menage the mail list
// Author    : Gabriel Henrique dos Santos Gonçalves (gabrielhenri.sg@gmail.com)
// Changes   : 2022-10-08 - file created
//             2022-10-13 - program finished - 1.0
//---------------------------------------------------------------------
#include<iostream>
#include<string>
#include<string.h>
#include<sstream>
#include "mail.hpp"
#include "msgassert.h"


using namespace std;


int main (int argc, char ** argv) {
    //server will be the variable that controls users list.
    List Server;
    //auxiliary string to read input
    string command,line;
    while (getline(cin,line)) {
        //split string
        stringstream sin(line);
        sin>>command;
        if(command == "CADASTRA"){
            //if the command informed by input is to cadastrate a new user
            int id;
            sin>>id;
            avisoAssert(0<=id && id<=1000000,"ID FORA DAS DIMEMSÕES");
            //list method to add a new user
            Server.SetUser(id);
        } else if(command == "REMOVE"){
            //if the command informed by input is to remove an user
            int id;
            sin>>id;
            //list method to remove an user
            Server.RemoveUser(id);
        } else if(command == "ENTREGA"){
            //if the command informed by input is to delivery a message for an user
            int id, priority;
            string msg, aux;
            sin>>id;
            sin>>priority;
            avisoAssert(0<=priority && priority<=9,"PRIORIDADE FORA DAS DIMEMSÕES");
            //get the message from input
            while(aux!="FIM"){
                msg+=aux + " ";
                sin>>aux;
            }
            //list method to send a message to an user
            Server.SendMessage(id, priority, msg);
        } else if(command == "CONSULTA"){
            //if the command informed by input is to read the inbox of an user
            int id;
            sin>>id;
            //list method to read the mailbox of an user
            Server.ConsultMessage(id);
        }
    }
    //end program
    return 0;
}