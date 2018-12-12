#include "stdaup.h"
#include "charset.h"

int main(int argc, char const *argv[])
{
	printf("%d\n", argc);
	charset_t *charset = charset_new(*argv);
	free(charset);
	return 0;
}

// Länge eines Strings
int stringLength(const char * string, unsigned long int length){
	if(string[length] != 0){
		return stringLength(string, ++length);
	}
	return ++length;
}

// Exponentialfunktion
int expon(int base, int exp){
	int c = 1;
	for (int i = 0; i < exp; i++){
		c *= base;
	}
	return c;
}

charset_t *charset_new(const char* elements){
	charset_t *new_charset = (charset_t *)malloc(7);
	int inputLaenge = stringLength(elements, 0);

	// Gesamten input einlesen und jedes Zeichen speichern, wenn es ein valides Zeichen ist
	for (int i = 0; i <= inputLaenge; i++){
		if ((elements[i] >= 65 && elements[i] <= 72) || (elements[i] >= 97 && elements[i] <= 122)){
			int j = 0;
			// Großbuchstaben 65 - 90
			if (elements[i] >= 65 && elements[i] <= 72){
				j = elements[i] - 65;
			}
			// Kleinbuchstaben 97 - 122
			else if (elements[i] >= 97 && elements[i] <= 122){
				j = elements[i] - 97 + 26;
			}
			// Finde das Sektion/ das Byte heraus (0-7)
			int section = j / 8;
			// Finde die Position/ das Bit heraus (0-7)
			int position = j % 8;
			new_charset->bits[section] = new_charset->bits[section] | expon(2, 8 - position);
		}
	}
	return new_charset;
}

int charset_op(charset_t* s1, const charset_t *s2, csopt_t op){
	switch (op){
		// Mengen vereinigen (jedes Zeichen) übernehmen
		case CS_UNION:
			for (int i = 0; i < 7; i++){
				s1->bits[i] = s1->bits[i] | s2->bits[i];
			}
			break;
		// Schnittmenge erstellen (nur wenn das Zeichen in beiden ist wird es übernommen)
		case CS_CUT:
			for (int i = 0; i < 7; i++){
				// Wenn Element nicht in beiden Mengen ist, dann 0 setzen
				if (!(s1->bits[i] && s2->bits[i])){
					s1->bits[i] = 0;
				}
			}
			break;
		case CS_SYMDIFF:
			for (int i = 0; i < 7; i++){
				// Wenn Element nicht in beiden Mengen ist, dann 0 setzen
				if (s1->bits[i] && s2->bits[i]){
					s1->bits[i] = 0;
				}else{
					s1->bits[i] = s1->bits[i] | s2->bits[i];
				}
			}
			break;
		default:
			return -1;
	}
	return 0;
}
