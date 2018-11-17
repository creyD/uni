/* AuP WS 2018/19, bewertete Aufgabe 3 */
int printf(const char * restrict, ...);
void *malloc(unsigned long);
const char *whirled(const char * const str);
unsigned long int stringLen(const char * const string, unsigned long int length);
void flipNtranslate(const char * const str, char * stringNew, unsigned long int length, unsigned long int iterator);
char translate(char translateChar);

// Deklaration der Aufgabenfunktion
int main(int carg, const char **varg){
	if (carg != 2) return -1;
	printf("Die verwürfelte Version von \"%s\" ist \"%s\".\n", // gibt Ergebnis aus
		varg[1], whirled(varg[1]));
	return 0;
}

unsigned long int stringLen(const char * const string, unsigned long int length){
	if(string[length] != 0){
		return stringLen(string, ++length);
	}
	return ++length;
}

char translate(char translateChar){
	if (translateChar >= 65 && translateChar <= 90){
		translateChar += (77 - translateChar) * 2 + 1;
	}else if (translateChar >= 97 && translateChar <= 122){
		translateChar += (109 - translateChar) * 2 + 1;
	}
	return translateChar;
}

void flipNtranslate(const char * const str, char * stringNew, unsigned long int length, unsigned long int iterator){
	if (iterator == length){
		stringNew[length] = '\0';
		return;
	}
	stringNew[iterator] = translate(str[(length - 2) - iterator]);
	flipNtranslate(str, stringNew, length, ++iterator);
}

const char *whirled(const char * const str){
	// Get the length of the string
	unsigned long int length = stringLen(str, 0);
	// Allocate new editable pointer
	char *pointer = (char *)malloc(length);
	// flipNtranslate it
	flipNtranslate(str, pointer, length, 0);
	return pointer;
}
