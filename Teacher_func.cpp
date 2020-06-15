#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "header.h"
using namespace std;


void Remote_teacher(char* students_filename, char* teachers_filename){

    int ind = -1;
    ///Авторизация
    while (ind == -1){
        char login[50];
        get_login(login);
        char password[50];
        get_password(password);
        ind = check_data_teachers(login, password, teachers_filename);
        if (ind != -1){
            cout << "\n\nDobro pojalovat!";
            break;
        }
        else cout << "\nNe verno login ili parol!\n";
    }


    ///Если авторизация прошла успешно, то спрашиваем о дальнейших командах
    while (1){
        vector <teacher> teachers;
        int len = get_people(teachers, teachers_filename);
        cout << "\n\nViberite deystvie:\nZapolnit ocenki gruppi - 1\nZapolnit poseshaemost gruppi - 2\nDobavit novogo studenta v gruppu - 3\nPeremestit studenta is gruppi - 4\nVistovit itogovuu ocenku studentu - 5\nDobavit gruppu - 6\nVivesti tekushie gruppi - 7\nUdalit gruppu - 8\nvihod - 0\n\n";
        int call;
        cin >> call;

        switch (call){
            case 1: give_grades(teachers[ind], students_filename); break;        ///Выставить оценку группе за определенную дату
            case 2: is_student_present(teachers[ind], students_filename); break; ///Проставить посещаемость группе за какой то день
            case 3: add_to_group(students_filename); break;                      ///Создать студента
            case 4: to_moove_student(students_filename); break;                  ///Перевести студента в другую группу
            case 5: to_final_rate(teachers[ind], students_filename); break;      ///Выставить студенту итоговую оценку за курс
            case 6: add_group(teachers[ind], teachers_filename); break;          ///Добавить группы учителю
            case 7: show_curr_groups(teachers[ind]); break;
            case 8: delete_group(teachers[ind], teachers_filename); break;
            case 0: exit(0);                                                     ///exit(0)
        }
    }
}



void give_grades(teacher a, char* students_filename){
    ///Считывание даты
    int month, day, group, i;

    ///Ввод группы и проверка доступа
    while (1){
        int res;
        group = get_group();
        res = is_group_exist(a.groups, group);
        if (!res) cout << "Net dostupa k etoy gruppe!\n";
        else break;
    }

    month = get_month(1);
    day = get_day(1);
    vector <student> students;
    int len = get_people(students, students_filename);

    ///Выставление оценок
    for (i = 0; i < len; i++){
        if (students[i].group == group){
            cout << endl << students[i].login << " ";
            cin >> students[i].grades[a.subject][month][day];
        }
    }


    dump_data(students_filename, len, students);

    cout << "Uspeshno zaversheno!\n";
}



void is_student_present(teacher a,char* students_filename){

    ///Считывание даты
    int month, day, group, i;

    ///Ввод группы и проверка доступа
    while (1){
        int res;
        group = get_group();
        res = is_group_exist(a.groups, group);
        if (!res) cout << "Net dostupa k etoy gruppe!\n";
        else break;
    }

    month = get_month(1);
    day = get_day(1);
    vector <student> students;
    int len = get_people(students, students_filename);

    ///Выставление посещаемости
    cout << "Vvedite 1 esli student bil na pare, -1 esli ne bil:\n";
    for (i = 0; i < len; i++){
        if (students[i].group == group){
            cout << endl << students[i].login << " ";
            cin >> students[i].attendance[a.subject][month][day];
        }
    }

    dump_data(students_filename, len, students);

    cout << "Uspeshno zaversheno!\n";
}





void add_to_group(char* students_filename){
    student a;
    a.group = get_group();


    int res = -1;
    ///Проверка на наличие введенного логина
    while (res != 0){

        get_login(a.login);
        int res = is_student_login_exist(a.login, students_filename);
        if (res != 0) cout << "Tagoy login uze est!\n";
        else break;
    }

    create_password(a.password);

    append_data(students_filename, a);

    cout << "Student uspeshno sozdan i dobavlen v gruppu!\n";
}


void to_moove_student(char* students_filename){
    int new_group;
    char login[50];
    get_login(login);
    cout << "Vvedite novuu gruppu: ";
    cin >> new_group;

    ///students - массив студентов, len - Длина массива.
    vector <student> students;
    int len = get_people(students, students_filename), i = 0;


    for (i; i < len; i++){
        if (!strcmp(students[i].login, login)){
            students[i].group = new_group;
        }
    }

    dump_data(students_filename, len, students);

    cout << "Uspeshno zaversheno!";
}


void to_final_rate(teacher a, char* students_filename){
    ///mn - месяц старта, dn - день старта, mk - месяц конца, dk - день конца курса
    int dn, mn, dk, mk, i = 0;
    double sum = 0.0, counT = 0.0;
    char login[50];
    get_login(login);
    cout << "Vvedite period ocenivaya: \n";
    cout << "S kakogo nomera mesyaca: ";
    cin >> mn;
    cout << "S kakogo dnya: ";
    cin >> dn;
    cout << "Do kakogo nomera mesyaca: ";
    cin >> mk;
    cout << "Do kakogo dnya: ";
    cin >> dk;

    vector <student> students;
    int len = get_people(students, students_filename);
    ///Подсчет данных для вычисления ср.ариф.
    for (i; i < len; i++){
        if (!strcmp(students[i].login, login)){

            for (mn; mn < (mk + 1); mn++){

                if (mn == mk){
                    for (dn; dn < (dk + 1); dn++){
                        int grade = students[i].grades[a.subject][mn][dn];
                        if (grade){
                            sum += grade;
                            counT ++;
                        }
                    }
                }

                else {
                    for (dn; dn < 32; dn++){
                        int grade = students[i].grades[a.subject][mn][dn];
                        if (grade){
                            sum += grade;
                            counT ++;
                        }
                    }
                }
                dn = 1;
            }
            break;
        }
    }

    ///Выставление итоговой оценки за курс
    students[i].grades[a.subject][mk][32] =sum/counT;
    cout << "Itogovaya za kurs: " << students[i].grades[a.subject][mk][32] << endl;

    dump_data(students_filename, len, students);
}



void add_group(teacher a, char* teachers_filename){
    ///teachers -массив с учителями, len - длина массива
    vector <teacher> teachers;
    int len = get_people(teachers, teachers_filename);
    int n, i = -1, j, p;
    while (a.groups[++i]){}

    cout << "Vvedite kol-vo grupp: ";
    cin >> n;
    j = i + n;

    cout << "Vvedite nomera grupp kotorie hotite dobavit: ";
    for (p = 0; p < len; p++){
        if (!strcmp(teachers[p].login, a.login)){
            for (i; i < j; i++) {

                int res;
                cin >> n;
                res = is_group_exist(teachers[p].groups, n);
                if (!res) {
                    teachers[p].groups[i] = n;
                }
                else{
                    i--;
                    j--;
                }
            }
            show_curr_groups(teachers[p]);
            break;
        }
    }


    dump_data(teachers_filename, len, teachers);

    cout << "\nUspeshno dobavleno!\n";

}




void show_curr_groups(teacher a){
    int i = 0;
    cout << "Vashi gruppi: ";
    while (a.groups[i]){
        cout << a.groups[i] << " ";
        i++;
    }
}




void delete_group(teacher a, char* teacher_filename){


    vector <teacher> teachers;
    int len = get_people(teachers, teacher_filename), i = 0, n;
    cout << "Vvedite gruppu dla udaleniya: ";
    cin >> n;

    ///Удаление указаной группы у данного учителя
    while (a.groups[i]){

        if (a.groups[i] == n){
            int p = a.groups[i + 1];
            if (p != 0){
                a.groups[i + 1] = a.groups[i];
                a.groups[i] = p;
            }
            else a.groups[i] = 0;
        }
        i++;
    }

    ///Замена старого экземпляра учителя на новый, с новыми группами
    for (i = 0; i < len; i++){
        if (!strcmp(a.login, teachers[i].login)){
            teachers[i] = a;
            break;
        }
    }

    dump_data(teacher_filename, len, teachers);

    cout << "Uspesho udaleno!\n";
}
