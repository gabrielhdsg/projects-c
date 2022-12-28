//---------------------------------------------------------------------
// File      : image.cpp
// Subject   : this program has the PPM and PGM classes 
// Author    : Gabriel Henrique dos Santos Gonçalves (gabrielhenri.sg@gmail.com)
// Changes   : 2022-09-18 - file created
//---------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "image.h"
#include "msgassert.h"

using namespace std;

PPM::PPM(string arqin) {
// Description: create PPM var
// Input: arqin
// Output: *m

    // open file
    fin.open(arqin,ios_base::in);
    erroAssert(fin.is_open(),"Unable to open the file");

    // auxiliary vars
    string type_file;
    string dimensions;
    string max_size;

    // verify if file is P3
    getline(fin,type_file);
    erroAssert(type_file=="P3","File has not the right format");

    // get file dimensions
    getline(fin,dimensions);
    stringstream sin(dimensions);
    sin>>this->pixels;
    sin>>this->lines;

    // get file max pixel size
    getline(fin,max_size);
    erroAssert(max_size=="255","File has not the right format");

    // create PPM vector
    int c=(this->getlines()*this->getpixels()*3);
    this->m = new int [c];

    // get file values and store it into the vector
    for (int i=0;i<c;i++) {
        fin>>this->m[i];
    }

    // close file
    fin.close();  
}

int PPM::getlines(){
// Description: return PPM lines number
// Input: -
// Output: lines
    return this->lines;
}

int PPM::getpixels(){
// Description: return PPM pixels number
// Input: -
// Output: pixels
    return this->pixels;
}

int PPM::getfileline(int i) {
// Description: return value of the specified vector position
// Input: i
// Output: m[i]
    return this->m[i];
}

PPM::~PPM(){
// Description: free vector memory usage 
// Input: -
// Output: -
    delete [] this->m;
}

PGM::PGM(PPM *target) {
// Description: create PGM var
// Input: target
// Output: *m

    //get PPM dimensions
    this->pixels = target->getpixels();
    this->lines = target->getlines();

    //craeate PGM vector
    this->m = new int[(this->lines*this->pixels)];
    
    //auxiliary vars
    int next_line = 0;
    int PGM_line = 0;
    int compare = this->pixels*3;
    int R,G,B;

    //get PPM values and calculate the respective PGM pixel
    for(int i=0; i<(this->getlines());i++){
        for(int j=next_line; j<compare ;j+=3) {
            //get RGB values stored into PPM vector
            R=target->getfileline(j);
            G=target->getfileline(j+1);
            B=target->getfileline(j+2);
            //equation to get the PGM pixel value
            int c = (49*(0.30*(float)R + 0.59*(float)G + 0.11*(float)B))/255;
            this->m[PGM_line] = c;
            PGM_line++;
        }
        next_line += this->pixels*3;
        compare += this->pixels*3;
    }

}

void PGM::export_file(string arqout) {
// Description: create PPM var
// Input: arqout
// Output: fout

    // open file
    fout.open(arqout,ios_base::out);
    erroAssert(fout.is_open(),"Unable to open the file");

    //write basic .pgm information into the file
    fout<<"P2"<<endl;
    fout<<to_string((this->getpixels())) + " " + to_string((this->getlines()))<<endl;
    fout<<"49"<<endl;

    //auxiliary vars
    int next_line = 0;
    int compara = this->pixels;

    //get PGM vector values and write it into the file
    for(int i=0;i<(this->getlines());i++){
        for(int j=next_line;j<compara;j++){
            fout<<to_string(this->getfileline(j)) + " ";
        }
        fout<<endl;
        next_line += this->pixels;
        compara += this->pixels;
     }

    //close file
    fout.close();
}

int PGM::getlines(){
// Description: return PGM lines number
// Input: -
// Output: lines
    return this->lines;
}

int PGM::getpixels(){
// Description: return PGM pixels number
// Input: -
// Output: pixels
    return this->pixels;
}

int PGM::getfileline(int i) {
// Description: return value of the specified vector position
// Input: i
// Output: m[i]
    return this->m[i];
}

PGM::~PGM(){
// Description: free vector memory usage 
// Input: -
// Output: -
    delete [] this->m;
}