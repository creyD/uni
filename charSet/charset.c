#include "stdaup.h"
#include "charset.h"

int main() {
charset_t *s1 = charset_new("Hallo"); charset_t *s2 = charset_new("ABCabc"); char *str1 = charset_tos(s1); charset_op(s1,s2,CS_UNION);
char *str2 = charset_tos(s1);
printf("str1=\"%s\"\n",str1); // ergibt: "aHlo" 
printf("str2=\"%s\"\n",str2); // ergibt: "AaBbCcHlo"
free(s1); free(s2); free(str1); free(str2); return 0;
}

// Laenge eines Strings
int stringLength(const char * string, unsigned long int length){
	if(string[length] != 0){
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
	char *string = (char *) malloc(7);
	int iterator = 0;
	for (int i = 0; i < 7; i++){
		for (int j = 0; j < 8; j++){
			if (s->bits[i] & expon(2, 7 - j)){
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
	return string;
}
