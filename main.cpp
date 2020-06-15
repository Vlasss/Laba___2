#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "header.h"
using namespace std;


/**
    @function main
    Запрашивает команду для действия, передает управление функциям в соответстии с введенной командой.
    @param argc - кол-во поступивших агрументов в майн
    @param argv - агрументы
*/
int main(int argc, char *argv[])
{


    if (argc != 3){             ///Завершить программу, если поступило не 3 аргумента в мейн
        cout << "Nujno 2 argumenta! 1 - file s studentami, 2 - file s uchitelami\n";
        exit(0);
    }

    while (1){
        cout << "\nstudent - 1, U4itel - 2, registraciya (tolko dla uchiteley) - 3 vihod - 0 ";
        int who;
        cin >> who;
        switch (who) {
            case 1 : Remote_student(argv[1], argv[2]); break;   ///Передать управление пульту управления с студентом
            case 2 : Remote_teacher(argv[1], argv[2]); break;   ///Передать управление пульту управления с учителем
            case 3 : Sign_up(argv[2]); break;                   ///Зарегестрировать учителя
            case 0 : exit(0);                                   ///Выход из програмы
        }
    }

    return 0;
}
