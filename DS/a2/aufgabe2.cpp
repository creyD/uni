#include <iostream>
#include <stdlib.h>

typedef struct {
	char* session_name;
} Session;

typedef struct {
	unsigned short number;
	char* name;
	Session* absolved [30];
} Student;

void menu(Student** university);

// INPUT FUNKTIONEN
// Frage den Nutzer nach der Matrikelnummer ab
unsigned short getMatNum() {
	std::cout << "Matrikelnummer (Nummer zwischen 1 und 999999):";
	unsigned short matricle_num;
	std::cin >> matricle_num;
	if (matricle_num >= 1 && matricle_num <= 999999) {
		return matricle_num;
	}
	else {
		std::cout << "Matrikelnummer ung\x81ltig. Erneut versuchen." << std::endl;
		return getMatNum();
	}
}

char* readString() {
	char str[100];
	std::cin >> str;
	return str;
}

// HELPER FUNKTIONEN
Student** move_up(Student** university, int start) {
	for (int i = 1000; i > start; i--) {
		university[i] = university[i - 1];
	}
	return university;
}

Student** move_down(Student** university, int start) {
	for (int i = start; i < 1000; i++) {
		university[i] = university[i + 1];
	}
	return university;
}

// Verdichtet das Array um Nullzeiger zwischen Elementen zu entfernen
Student** squash(Student** university) {
	for (int i = 0; i < 1000; i++) {
		if (!(university[i])) {
			move_down(university, i);
		}
	}
	return university;
}

// Sucht eine Matrikelnummer im Array und gibt den Index
int getIndex(Student** university, unsigned short search_num) {
	for (int i = 0; i < 1000; i++) {
		if (university[i]) {
			if ((*university)->number == search_num) {
				return i;
			}
		}
	}
	return -1;
}

// Fuegt einen Studierenden ein, ausser die Matrikelnummer existiert bereits
Student** insert(Student** university, Student * inserter) {
	int index_new_student = 0;
	for (int i = 0; i < 1000; i++) {
		if (university[i]) {
			if (university[i]->number == inserter->number) {
				std::cout << "Duplikat erkannt! Verwerfe Eingabe." << std::endl;
			}
			else if ((*university)[i].number > (*inserter).number) {
				index_new_student = i;
				university = move_up(university, i);
				break;
			}
		}
		else {
			index_new_student = i;
			break;
		}
	}
	university[index_new_student] = inserter;
	return university;
}

Student** addOption(Student** university) {
	std::cout << "Hinzuf\x81gen" << std::endl;
	std::cout << "===================" << std::endl;
	Student* current = new Student();
	// Matrikelnummer
	unsigned short matrikelnum = getMatNum();
	if (getIndex(university, matrikelnum) != -1) {
		std::cout << "Matrikelnummer bereits vergeben. Abbrechen." << std::endl;
		return university;
	}
	(*current).number = matrikelnum;
	// Name
	std::cout << "Name:";
	char* str;
	str = readString();
	(*current).name = str;
	// Absolvierte Module
	Session current_sessions[30];
	int option = 1;
	std::cout << "Eingabe der Lehrveranstaltungen:" << std::endl;
	for (int i = 0; i < 29; i++) {
		std::cout << "Weitere Lehrveranstaltungen hinzuf\x81gen? (1 = ja, 0 = nein)";
		std::cin >> option;
		if (option == 1) {
			std::cout << "Name der Lehrveranstaltung:" << std::endl;
			char* str;
			str = readString();
			current_sessions[i].session_name = str;
		}
		else {
			for (int j = i; j < 29; j++) {
				current_sessions[i].session_name = NULL;
			}
			break;
		}
	}
	(*(*current).absolved) = current_sessions;
	// Hinzufuegen zur universitaet
	university = insert(university, current);
	return university;
}

// Suchfunktion
void searchOption(Student** university) {
	std::cout << "Suche" << std::endl;
	std::cout << "===================" << std::endl;
	std::cout << "Matrikelnummer eingeben:" << std::endl;
	unsigned short search_num;
	std::cin >> search_num;
	if (getIndex(university, search_num) != -1) {
		std::cout << "Student ist im Feld." << std::endl;
	}
	else {
		std::cout << "Student ist nicht im Feld." << std::endl;
	}
	return;
}

// Loeschfunktion
void deleteOption(Student** university) {
	std::cout << "L\x94schen" << std::endl;
	std::cout << "===================" << std::endl;
	std::cout << "Matrikelnummer eingeben:" << std::endl;
	unsigned short search_num;
	std::cin >> search_num;
	int index = getIndex(university, search_num);
	if (index != -1) {
		delete[] university[index];
		university[index] = NULL;
		university = squash(university);
		std::cout << "Student erfolgreich gel\x94scht." << std::endl;
	}
	else {
		std::cout << "Student ist nicht im Feld. Nicht gel\x94scht." << std::endl;
	}
	return;
}

// MENUE FUNKTION
void menu(Student** university) {
	while (true) {
		char option;
		std::cout << "Studentenverwaltung" << std::endl;
		std::cout << "===================" << std::endl;
		std::cout << "Auswahlmen\x81:" << std::endl;
		std::cout << "A - Anlegen eines neuen Studenten und der bisher belegten Lehrveranstaltungen" << std::endl;
		std::cout << "S - Suchen eines Studenten" << std::endl;
		std::cout << "L - L\x94schen eines Studenten" << std::endl;
		std::cout << "E - Programmende" << std::endl;
		std::cout << "Option ausw\x84hlen:" << std::endl;
		std::cin >> option;

		switch (option) {
		case 'A':
			university = addOption(university);
			break;
		case 'S':
			searchOption(university);
			break;
		case 'L':
			deleteOption(university);
			break;
		case 'E':
			std::cout << "Programm wird beendet." << std::endl;
			for (int i = 0; i < 1000; i++) {
				delete university[i];
			}
			delete university;
			exit(0);
			break;
		default:
			std::cout << "Keine valide Eingabe erkannt!" << std::endl;
			menu(university);
		}
	}
}

int main()
{
	Student** university = new Student * [1000];
	for (int i = 0; i < 1000; i++) {
		university[i] = NULL;
	}
	menu(university);
}
