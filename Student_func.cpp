#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "header.h"
using namespace std;



void Remote_student(char* students_filename, char* teachers_filename) {

	int ind = -1;
	/**
		Авторизация путем ввода логина и пароля и соответствующей проверки.
	*/
	while (ind == -1) {
		char login[50];
		get_login(login);
		char password[50];
		get_password(password);
		///ind - получает -1, если логин или пароль не верны или индекс успешно авторизовавшегося студента в массиве.
		ind = check_data_students(login, password, students_filename);
		if (ind != -1) {
			cout << "\n\nDobro pojalovat!";
			break;
		}
		else cout << "\nNe verno login ili parol!\n";
	}

	int call = -1;
	///Если авторизация прошла успешно, то спрашиваем о дальнейших командах
	while (1) {
		while (call < 0 || call > 3) {
			cout << "\nPosmotret ocenki - 1, uznat itogovuu za kusr - 2, Posmotret poseshaemost - 3 vihod - 0: ";
			cin >> call;
			if (call < 0 || call > 3) cout << "Ne korrektno vvedena komanda!\n";
		}
		switch (call) {
		case 1: show_grades(ind, students_filename); call = -1; break;      ///Показать оценки за определенный период
		case 2: show_final_rate(ind, students_filename); call = -1; break;  ///Показать итоговую оценку за курс по определенному предмету , который закончился в определенном месяце
		case 3: show_attendance(ind, students_filename); call = -1; break;  ///Показать посещаемость за определенный период
		case 0: exit(0);                                                    ///exit(0)
		}
	}

}


void show_grades(int ind, char* students_filename) {
	int subject, month, day = 0;
	subject = get_subject();
	month = get_month(0);
	if (month != 0) day = get_day(0);
	vector <student> students;
	int len = get_people(students, students_filename), i, j;

	if (month == 0) {
		for (i = 1; i < 13; i++) {
			for (j = 1; j < 32; j++) {
				if (students[ind].grades[subject][i][j]) {
					cout << i << "." << j << ".20 - " << students[ind].grades[subject][i][j] << endl << endl;
				}
			}
		}
	}

	else if (day == 0) {
		for (i = 1; i < 32; i++) {
			if (students[ind].grades[subject][month][i]) {
				cout << month << "." << i << ".20 - " << students[ind].grades[subject][month][i] << endl;
			}
		}
	}
	else {
		if (students[ind].grades[subject][month][day]) {
			cout << month << "." << day << ".20 - " << students[ind].grades[subject][month][day] << endl;
		}
	}

}



void show_attendance(int ind, char* students_filename) {
	int subject, month, day = 0;
	subject = get_subject();
	month = get_month(0);
	if (month != 0) day = get_day(0);
	vector <student> students;
	int len = get_people(students, students_filename), i, j;

	if (month == 0) {
		for (i = 1; i < 13; i++) {
			for (j = 1; j < 32; j++) {
				if (students[ind].attendance[subject][i][j] == 1) {
					cout << i << "." << j << ".20 - " << "bil" << endl << endl;
				}
				else if (students[ind].attendance[subject][i][j] == -1) {
					cout << i << "." << j << ".20 - " << "Ne bil" << endl << endl;
				}
			}
		}
	}

	else if (day == 0) {
		for (i = 1; i < 32; i++) {
			if (students[ind].attendance[subject][month][i] == 1) {
				cout << month << "." << i << ".20 - " << "bil" << endl;
			}
			else if (students[ind].attendance[subject][month][i] == -1) {
				cout << month << "." << i << ".20 - " << "Ne bil" << endl;
			}
		}
	}
	else {
		if (students[ind].attendance[subject][month][day] == 1) {
			cout << month << "." << day << ".20 - " << "bil" << endl;
		}
		else if (students[ind].attendance[subject][month][day] == -1) {
			cout << month << "." << day << ".20 - " << "Ne bil" << endl;
		}
	}

}


void show_final_rate(int ind, char* students_filename) {
	int subject;
	subject = get_subject();
	cout << "Vvedite posledniy mesyac kursa: ";
	int mk;
	cin >> mk;

	///students - массив студентов, len - длина массива
	vector <student> students;
	int len = get_people(students, students_filename);

	if (students[ind].grades[subject][mk][32] != 0) cout << "Vawa ocenka za kurs - " << students[ind].grades[subject][mk][32] << endl;
	else cout << "Ocenka ewe ne vistovlena!";
}
