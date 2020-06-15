#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "header.h"
using namespace std;



ostream& operator<<(ostream &out, const student a){
    out.write((char*)&a, sizeof(student));
    return out;
}

ostream& operator<<(ostream &out, const teacher a){
    out.write((char*)&a, sizeof(teacher));
    return out;
}



int get_people(vector <student> &arr, char* students_filename){
    ifstream f;
    int i = 0;
    f.open(students_filename);
    if (!f.is_open()) lockdown();

    student a;
    while (f.read((char*)&a, sizeof(student))){
        arr.push_back(a);
        i++;
    }
    f.close();

    return i;
}


int get_people(vector <teacher> &arr, char* teachers_filename){
    ifstream f;
    int i = 0;
    f.open(teachers_filename);
    if (!f.is_open()) lockdown();

    teacher a;

    while (f.read((char*)&a, sizeof(teacher))){
        arr.push_back(a);
        i++;
    }

    f.close();

    return i;
}
