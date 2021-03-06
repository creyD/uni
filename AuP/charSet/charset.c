#include "stdaup.h"
#include "charset.h"

// Gibt die Laenge eines Strings zurueck
int stringLength(const char * string, unsigned long int length){
	if (string[length] != 0){
		return stringLength(string, ++length);
	}
	return ++length;
}

// Exponentialfunktion
int expon(int base, int exp){
	int c = 1;
	if (exp != 0){
		for (int i = 0; i < exp; i++){
			c *= base;
		}
	}
	return c;
}

// Ueberpruefe ob ein Element in einem Chararray vorhanden ist
int stringContains(char * searchString, char test){
	for (int i = 0; i < stringLength(searchString, 0); i++){
		if (searchString[i] == test){
			return 1;
		}
	}
	return 0;
}

charset_t *charset_new(const char* elements){
	charset_t *new_charset = (charset_t *)malloc(7);
	int inputLaenge = stringLength(elements, 0);

	// Gesamten input einlesen und jedes Zeichen speichern, wenn es ein valides Zeichen ist
	for (int i = 0; i <= inputLaenge - 1; i++){
		int j = -1;
		if (elements[i] >= 65 && elements[i] <= 90){
			// Kleinbuchstaben 97 - 122
			j = elements[i] - 65;
		}
		else if (elements[i] >= 97 && elements[i] <= 122){
			// Kleinbuchstaben 97 - 122
			j = elements[i] - 71;
		}
		if (j != -1){
			// Finde das Sektion/ das Byte heraus (0-7)
			int section = j / 8;
			// Finde die Position/ das Bit heraus (0-7)
			int position = j % 8;
			new_charset->bits[section] = new_charset->bits[section] | expon(2, 7 - position);
		}
	}
	return new_charset;
}

int charset_op(charset_t* s1, const charset_t *s2, csopt_t op){
	switch (op){
		// Mengen vereinigen -> alle Zeichen uebernehmen
		case CS_UNION:
			for (int i = 0; i < 8; i++){
				s1->bits[i] = s1->bits[i] | s2->bits[i];
			}
			break;
		// Schnittmenge erstellen -> Wenn Zeichen nur in beiden Menge wird es gespeichert
		case CS_CUT:
			for (int i = 0; i < 8; i++){
				s1->bits[i] = s1->bits[i] & s2->bits[i];
			}
			break;
		// Symetrische Differenz berechnen -> Wenn Zeichen nur in einer Menge wird es gespeichert
		case CS_SYMDIFF:
			for (int i = 0; i < 8; i++){
				s1->bits[i] = s1->bits[i] ^ s2->bits[i];
			}
			break;
		default:
			return -1;
	}
	return 0;
}

char *charset_tos(const charset_t* s){
	// Reserviere die maximale Anzahl an Zeichenketten (alle Grossbuchstaben (26) + Kleinbuchstaben (26) + Nullterm (1))
	char *string = (char *) malloc(52);
	// Iterator fuer die Stelle im Zielstring, die beschrieben wird
	int iterator = 0;
	for (int i = 0; i < 7; i++){
		for (int j = 0; j < 8; j++){
			// Verknuepfe die Stelle im Charset mit der j-ten Potenz von 2 -> Wenn wahr dann ist die Stelle besetzt, wenn falsch nicht
			if (s->bits[i] & expon(2, 7 - j)){
				// Determiniere ob das Zeichen ein Grossbuchstabe ist
				if ((i * 8) + j + 65 <= 90){
					string[iterator] = (i * 8) + j + 65;
				}
				else{
					string[iterator] = (i * 8) + j + 71;
				}
				iterator++;
			}
		}
	}
	// Nullterminieren fuer Weiterverwendbarkeit des Strings
	string[iterator] = '\0';
	// Den Speicher auf die noetige Groesse beschraenken um ueberfluessigen Speicher freizugeben
	string = (char *) realloc(string, iterator);

	// Sortiere den String nach den gegebenen Kriterien
	int stelleSortiert = 0;
	char *sortierterString = (char *) malloc(iterator);

	// Jede Stelle des Alphabets ueberpruefen und erst den Grossbuchstaben und dann den Kleinbuchstaben hinzufuegen
	for (int i = 0; i < 26; i++){
		if (stringContains(string, 65 + i)){
			sortierterString[stelleSortiert] = 65 + i;
			stelleSortiert++;
		}
		if (stringContains(string, 97 + i)){
			sortierterString[stelleSortiert] = 97 + i;
			stelleSortiert++;
		}
	}
	// Neuen String nullterminieren fuer weiterverwendbarkeit
	sortierterString[stelleSortiert] = '\0';
	// Speicher fuer den initialen String wieder freigeben
	free(string);

	return sortierterString;
}
