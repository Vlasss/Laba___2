#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "header.h"
using namespace std;



void dump_data(char *filename, int len, vector <student> &arr){
    int i;
    ofstream f;
    f.open(filename);
    if (!f) lockdown();
    for (i = 0; i < len; i++) f << arr[i];
    f.close();
}

void dump_data(char *filename, int len, vector <teacher> &arr){
    int i;
    ofstream f;
    f.open(filename);
    if (!f) lockdown();
    for (i = 0; i < len; i++) f << arr[i];
    f.close();
}



void append_data(char *filename, student &a){
    fstream f;
    f.open(filename, fstream::app);
    if (!f) lockdown();
    f << a;
    f.close();
}


void append_data(char *filename, teacher &a){
    fstream f;
    f.open(filename, fstream::app);
    if (!f) lockdown();
    f << a;
    f.close();
}
