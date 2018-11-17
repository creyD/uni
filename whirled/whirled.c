/* AuP WS 2018/19, bewertete Aufgabe 3 */
int printf(const char * restrict, ...);
void *malloc(unsigned long);
const char *whirled(const char * const str);
unsigned long int stringLen(const char * const string, unsigned long int length);
void flip(const char * const string, char * stringNew, unsigned long int laenge, unsigned long int iterator);

// Deklaration der Aufgabenfunktion
// ein Parameter uebergeben?
int main(int carg, const char **varg){
	if (carg != 2) return -1;
	printf("Die verwürfelte Version von \"%s\" ist \"%s\".\n", // gibt Ergebnis aus
		varg[1], whirled(varg[1]));
	return 0;
}

// Ihr Code ab hier

unsigned long int stringLen(const char * const string, unsigned long int length){
	if(string[length] != 0){
		length++;
		return stringLen(string, length);
	}
	else {
		return ++length;
	}
}

void flip(const char * const string, char * stringNew, unsigned long int laenge, unsigned long int iterator){
	if (iterator == laenge){
		stringNew[iterator] = '\0';
		return;
	}else{
		stringNew[iterator] = string[laenge - iterator];
		flip(string, stringNew, laenge, ++iterator);
	}
	
}

const char *whirled(const char * const str){
	// Get the length of the string
	unsigned long int laenge = stringLen(str, 0);
	// Allocate new editable pointer
	char *pointer = (char *)malloc(laenge);
	// flip
	unsigned long int iterator = 0;
	flip(str, pointer, laenge, iterator);
	// translate
	return pointer;
}
