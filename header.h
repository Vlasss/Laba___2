#include <iostream>
#include <vector>
#pragma once

using namespace std;


/**
@class human
Класс, наследуемый другими классами, который содержит в себе логин и пароль пользователя.
*/
class human {
public:
    char login[50];
    char password[50];
};



/**
@class student
Класс студента, который наследует класс human, то есть в нем поля с логином и паролем не объявляем.
Дополнительно содержит в себе переменную, в которой хранится группа студента и 2 трехмерных массива с
оценками и данными о посещаемости. В оценках 1 элемент - идентификатор предмета (Matan - 1, Programirovanie - 2, AG - 3, English - 4),
Второй элемент - месяц, третий - день месяца, причем в каждом месяце есть дополнительная ячейка, в которой
хранится итоговая оценка за курс, который кончился в соответствующем месяце. Таким образом Хранятся оценки студента за все предметы.
В данных о посещаемости то же самое, токо 1 - был, -1 не был.
*/
class student : public human {
public:
    ///Номер группы студента.
    int group;
    ///Хранилище оценок.
    double grades[5][13][33]{};
    ///Хранилище информации о посещаемости
    int attendance [5][13][32]{};
    friend ostream& operator<<(ostream &out, const student a);
};



/**
@class teacher
Класс учителя, который наследует класс human, то есть в нем поля с логином и паролем тоже не объявляем.
subject хранит в себе номер предмета преподавателя (Matan - 1, Programirovanie - 2, AG - 3, English - 4),
groups - набор групп, которые числятся у данного преподавателя.
*/
class teacher : public human {
public:
    ///Предмет
    int subject;
    ///Группы учителя
    int groups[50]{};
    friend ostream& operator<<(ostream &out, const teacher a);
};

ostream& operator<<(ostream &out, const student a);
ostream& operator<<(ostream &out, const teacher a);




/**
    @function lockdown
    Вызывается, когда нужно завершить программу когда не получилось открыть файл.
*/
void lockdown();




/**
    @function dump_data
    Имеет 2 реализации эта с студентами, другая с учителями.
    Загружает массив класса student через перегруженный оператор вывода
    @param len - длина массива
    @param arr - массив
*/
void dump_data(char *filename, int len, vector <student> &arr);




/**
    @function dump_data
    Имеет 2 реализации эта с учителями, другая с студентами.
    Загружает массив класса teacher через перегруженный оператор вывода
    @param len - длина массива
    @param arr - массив
*/
void dump_data(char *filename, int len, vector <teacher> &arr);




/**
    @function append_data
    Имеет 2 реализации эта с студентами, другая с учителями.
    Загружает экземпляр класса student в конец файла через перегруженный оператор вывода
*/
void append_data(char *filename, student &a);




/**
    @function append_data
    Имеет 2 реализации, первая с студентами, эта с учителями.
    Загружает экземпляр класса teacher в конец файла через перегруженный оператор вывода
*/
void append_data(char *filename, teacher &a);




/**
    @function is_teacher_login_exist
    Проверяет, есть ли учитель с данным логином.
    @return 1 - есть
    @return 2 - нету
*/
int is_teacher_login_exist(char* login, char* teachers_filename);




/**
    @function is_student_login_exist
    Проверяет, есть ли студент с данным логином.
    @return 1 - есть
    @return 2 - нету
*/
int is_student_login_exist(char* login, char* students_filename);




void get_login(char *login);
void get_password(char *password);




/**
    @function create_password
    Создает пароль с проверкой ввода.
    @param password - указатель на массив, куда считывать пароль
*/
void create_password(char *password);




/**
    @function get_people
    Имеет 2 реализации, с файлом teachers_filename и students_filename, загружает в массив людей и соответствующего
    файла, возвращает длину массива.
    @param arr - массив, в который нужна загрузить данные
*/
int get_people(vector <student> &arr, char* students_filename);





/**
    @function get_people
    Имеет 2 реализации, с файлом teachers_filename и students_filename, загружает в массив людей и соответствующего
    файла, возвращает длину массива.
    @param arr - массив, в который нужна загрузить данные
*/
int get_people(vector <teacher> &arr, char* teachers_filename);




/**
    @function check_data_students
    Абсолютно аналогична функции check_data_teachers, разница в имени файла, т.к. функции маленькии, то не стал в одну соединять с костылями.
    @param login - логин
    @param password - пароль
    @param students_filename - имя файла
    @return -1 - все плохо, такого пользователя нет
    @return i - вернуть индекс студента в массиве
*/
int check_data_students(char *login, char *password, char* students_filename);




/**
    @function check_data_teachers
    Проверяет, если учитель с данными логином и паролем в базе данных
    @param login - логин
    @param password - пароль
    @param teachers_filename - имя файла
    @return -1 - все плохо, такого пользователя нет
    @return i - вернуть индекс учителя в массиве
*/
int check_data_teachers(char *login, char *password, char* teachers_filename);



int get_subject();
int get_month(int flag = 0);
int get_day(int flag = 0);




/**
    @function show_grades
    Получает в себя индекс ученика в массиве, имя файла и выводит его оценки за введенный период.
    @param ind - индекс ученика в массиве
    @param students_filename - имя файла
*/
void show_grades(int ind, char* students_filename);




/**
    @function show_final_rate
    Выводит оценку по курсу по заданному предмету, который закончился в заданном месяце
    @param ind - индекс студента в массиве
*/
void show_final_rate(int ind, char* students_filename);




/**
    @function Remote_student
    Функция с авторизацией студента с последующими возможностями проверить оценки за весь период,
    за конкретный месяц или конкретный день, узнать итоговую оценку за курс, узнать посещаемость.
    @param students_filename - название файла, в котором хранятся экземпляры объекта student.
    @param teachers_filename - название файла, в котором хранятся экземпляры объекта teacher.
*/
void Remote_student(char* students_filename, char* teachers_filename);




/**
    @function get_group
    Возвращает номер группы
*/
int get_group();




/**
    @function give_grades
    Выставляет оценки определенной группе за какой то день.
*/
void give_grades(teacher a, char* students_filename);




/**
    @function add_to_group
    Добавляет студента в указаную группу.
*/
void add_to_group(char* students_filename);




/**
    @function add_group
    Добавляет группы к учителю
    @param a - Учитель, которому добавляются группы
*/
void add_group(teacher a, char* teachers_filename);





/**
    @function to_final_rate
    Выставляет итоговую оценку за курс, как ср.ариф. путем ввода периода курса.
    @param a - учитель, который выставляет итоговую оценку за курс
*/
void to_final_rate(teacher a, char* students_filename);





/**
    @function to_moove_student
    Меняет поле group у заданного студента, тем самым переводя его в другую группу.
*/
void to_moove_student(char* students_filename);






/**
    @function Remote_teacher
    С помощью других функций проводит авторизацию учителя, выполняет команды, данные пользователем.
    @students_filename - имя файла студентов
    @teachers_filename - имя файла учителей
*/
void Remote_teacher(char* students_filename, char* teachers_filename);






/**
    @function get_groups
    Регестрирует учителя, студенты регистрируются через учителя
    @param arr - указатель на массив с номерами групп препода
*/
void get_groups(int *arr);




/**
    @function show_curr_groups
    Выводит текущие группы учителя
*/
void show_curr_groups(teacher a);



/**
    @function delete_group
    Удаляет группу у учителя
*/
void delete_group(teacher a, char* teacher_filename);




/**
    @function delete_group
    Проверяет на существование введеную группу
    @return 1 - группа уже есть
    @return 0 - нету
*/
int is_group_exist(int *arr, int group);


/**
    @function Sign_up
    Регестрирует учителя, студенты регистрируются через учителя
    @param teachers_filename - имя файла
*/
void Sign_up(char* teachers_filename);



/**
    @function is_student_present
    Функция для выставления посещаемости группы за какой-то день
*/
void is_student_present(teacher a,char* students_filename);



/**
    @function show_attendance
    Функция, выводящая посещаемость студента
    @param ind - индекс студента в массиве
*/
void show_attendance(int ind, char* students_filename);
