//---------------------------------------------------------------------
// File      : imageop.cpp
// Subject   : main program. call main operations to transform a .ppm into a .pgm
// Author    : Gabriel Henrique dos Santos Gonçalves (gabrielhenri.sg@gmail.com)
// Changes   : 2022-09-18 - file created
//             2022-12-27 - memlog removed
//---------------------------------------------------------------------

#include <iostream>
#include <string>
#include <string.h>
#include <getopt.h>
#include "image.h"
#include "msgassert.h"

#define REGISTER_ACESS 1;

using namespace std;

struct opt {
    char name_input[100];
    char name_output[100];
};

void parse_args(int argc,char **argv, opt *opt) {
// Description: get console commands
// Input: argc, argv, opt 
// Output: opt

     // auxiliary vars
     int c;

    // inicialize global var
     opt->name_input[0] = 0;
     opt->name_output[0] = 0;
     
     // getopt - letter indicates an operation
     while ((c = getopt(argc, argv, "o:i:")) != EOF)
       switch(c) {
         case 'o': 
	         strcpy(opt->name_output,optarg);
		    break;
         case 'i': 
	          strcpy(opt->name_input,optarg);
		    break;

       }

}

int main (int argc, char ** argv) 
{   
    //variable to get input informations
    opt s;
    parse_args(argc,argv,&s);

    //create variable input of class PPM, this var will recieve the path of the .ppm file tha will be read
    PPM input(s.name_input);

    //create variable output of class PGM, this variable will recieve the .ppm file stored in the input var
    PGM output(&input);

    //method that will create a external .pgm file with the informations stored in the output var
    output.export_file(s.name_output);

    //end of the file
    return 0;
}