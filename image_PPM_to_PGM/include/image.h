#ifndef IMAGE_H
#define IMAGE_H


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define INFOS_FILE 4
#define DIMENSION_LINE 2

using namespace std;

class PPM {
    private:
    
    int pixels;
    int lines;
    int *m;
    fstream fin;

    public:

    PPM(string arqin);
    int getlines();
    int getpixels();
    int getfileline(int i);
    ~PPM();

};

class PGM {
    private:

    int pixels;
    int lines;
    int *m;
    fstream fout;

    public:
    
    PGM(PPM *target);
    int getlines();
    int getpixels();
    int getfileline(int i);
    void export_file(string arqout);
    ~PGM();

};

#endif