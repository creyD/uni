extern int printf(const char *restrict __format, ...);
extern void *malloc(unsigned long size_t);
//extern void *calloc(size_t, size_t);
//extern void *realloc (void *, size_t);
extern void free (void *);

int stringLenght(char *string){
	int i = 0;
	while(1){
		if (string[i] == '\0'){
			return i;
		}
		i++;
	}
}

int kommaIndex(char *string, int laenge){
	for (int i = 0; i < laenge; i++){
		if (string[i] == ','){
			return ++i;
		}
	}
	return 0;
}

char getVZ(char *string){
	if (string[0] == '-'){
		return '-';
	}
	return '+';
}

int charToInt(char character){
	return character - '0';
}

char *calculate(char *zahl1, char *zahl2, char operation, char vorzeichen){
	int zahl1Lenght = stringLenght(zahl1);
	int zahl1Komma = kommaIndex(zahl1, zahl1Lenght);
	int zahl1NachKomma = zahl1Lenght - zahl1Komma;

	int zahl2Lenght = stringLenght(zahl2);
	int zahl2Komma = kommaIndex(zahl2, zahl2Lenght);
	int zahl2NachKomma = zahl2Lenght - zahl2Komma;

	// Laengere Nachkommazahl bestimmen
	int leangereNachKommaZahl = 0;
	int diffNachKomma = 0;
	if (zahl1NachKomma < zahl2NachKomma){
		leangereNachKommaZahl = zahl2NachKomma;
		diffNachKomma = zahl2NachKomma - zahl1NachKomma;
	}else if (zahl1NachKomma == zahl2NachKomma){
		diffNachKomma = 0;
	}else{
		leangereNachKommaZahl = zahl1NachKomma;
		diffNachKomma = zahl1NachKomma - zahl2NachKomma;
	}

	// Laengere Vorkommazahl bestimmen
	int leangereVorKommaZahl = 0;
	int diffVorKomma;
	if (zahl1Komma < zahl2Komma){
		leangereVorKommaZahl = zahl2Komma;
		diffVorKomma = zahl2Komma - zahl1Komma;
	}else if (zahl1Komma == zahl2Komma){
		diffVorKomma = 0;
	}else{
		leangereVorKommaZahl = zahl1Komma;
		diffVorKomma = zahl1Komma - zahl2Komma;
	}

	// Uebertragsvariable
	int uebertrag = 0;

	// TODO: Gesamte Rechnung für Minus realisieren
	// Nachkomma Rechnung
	// Reserviere Speicher fuer das Zwischenergebnis der Nachkomma Rechnung
	char *ergebnisNachKomma = (char *)malloc(leangereNachKommaZahl + 1);
	
	for (int i = leangereNachKommaZahl; i < 0; i--){
		int zwischenspeicher = 0;
		if (i > zahl1NachKomma){
			ergebnisNachKomma[i] = zahl2[zahl2Lenght - i];
		}else if (i > zahl2NachKomma){
			ergebnisNachKomma[i] = zahl1[zahl1Lenght - i];
		}else{
			// Wenn beide Zahlen gleich viele Nachkommastellen besitzen, einfach runterzaehlen
			if (diffNachKomma == 0){
				zwischenspeicher = charToInt(zahl1[zahl1Lenght - i]) + charToInt(zahl2[zahl2Lenght - i]);
			}else{
				// Wenn Zahl 2 mehr NKS hat, als Zahl 1 dann füge bei Zahl 1 noch den Unterschied fuer richtige Indeze hinzu
				if (zahl1NachKomma < zahl2NachKomma){
					zwischenspeicher = charToInt(zahl2[zahl2Lenght - i]) + charToInt(zahl1[(zahl1Lenght + diffNachKomma) - i]);
				}else{
					zwischenspeicher = charToInt(zahl1[zahl1Lenght - i]) + charToInt(zahl2[(zahl2Lenght + diffNachKomma) - i]);
				}
			}
			// Wenn die beiden Zahlen zu mehr als 10 addieren, dann erstelle einen Uebertrag
		 	if (zwischenspeicher > 9){
				ergebnisNachKomma[i] = zwischenspeicher - 10 + uebertrag;
				uebertrag = 1;
			}else{
				ergebnisNachKomma[i] = zwischenspeicher + uebertrag;
				uebertrag= 0;
			}
		}
	}

	// Vorkommarechnung
	char *ergebnisVorKomma = (char *)malloc(leangereVorKommaZahl + 1);

	// -1 fuer Komma
	for (int i = leangereVorKommaZahl - 1; i < 0; i--){
		int zwischenspeicher = 0;
		if (diffVorKomma == 0){
			zwischenspeicher = zahl1[zahl1Komma - i] + zahl1[zahl2Komma - i];
		}
		if (zwischenspeicher > 9){
			ergebnisVorKomma[i] = zwischenspeicher - 10 + uebertrag;
			uebertrag = 1;
		}else{
			ergebnisVorKomma[i] = zwischenspeicher + uebertrag;
			uebertrag= 0;
		}
	}

	// Zusammenfuehren, nullterminieren und Vorzeichen anhaengen
	// +1 Nullterminierung, +1 Vorzeichen, +1 Ueberlauf, +1 Komma
	int vorKommaLaenge = stringLenght(ergebnisVorKomma);
	int nachKommaLaenge = stringLenght(ergebnisNachKomma);
	char *ergebnis = (char *)malloc(vorKommaLaenge + nachKommaLaenge + 4);

	ergebnis[0] = vorzeichen;
	for (int i = 0; i <= vorKommaLaenge; i++){
		ergebnis[i + 1] = ergebnisVorKomma[i];
	}
	ergebnis[vorKommaLaenge + 2] = '\0';
	for (int i = 0; i <= nachKommaLaenge; i++){
		ergebnis[vorKommaLaenge + 3 + i] = ergebnisNachKomma[i];
	}
	ergebnis[vorKommaLaenge + nachKommaLaenge + 4] = '\0';

	// Speicher aufraumen
	free(ergebnisNachKomma);
	free(ergebnisVorKomma);

	printf("%c\n", operation);
	// Ergebnis der Rechnung zuruekgeben
	return ergebnis;
}

int main(int argCounter, char *argv[])
{
	printf("%d\n", argCounter);
	// TODO: Anwendung fuer mehrere Parameter schreiben
	// Konzept: Fuer jeden ungeraden Parameter (= neue Zahl) verrechne die Zahl im Zwischenspeicher mit der aktuellen Zahl
	// a + b = c --> c + d = e

	//for (int i = 1; i < argCounter; i ++)
	char zahl1VZ = getVZ(argv[1]);
	char zahl2VZ = getVZ(argv[3]);

	char vz = '0';
	char operation = argv[2][0];

	if ((zahl1VZ == '+' && zahl2VZ == '+' && operation == '+') || (zahl1VZ == '+' && zahl2VZ == '-' && operation == '-')){
		vz = '+';
		operation = '+';
		printf("%s\n", calculate(argv[1], argv[3], operation, vz));
	}
	else if ((zahl1VZ == '-' && zahl2VZ == '+' && operation == '-') || (zahl1VZ == '-' && zahl2VZ == '-' && operation == '+')){
		vz = '-';
		operation = '+';
		printf("%s\n", calculate(argv[1], argv[3], operation, vz));
	}
	else if ((zahl1VZ == '+' && zahl2VZ == '+' && operation == '-') || (zahl1VZ == '+' && zahl2VZ == '-' && operation == '+')){
		operation = '-';
		// TODO: Wie vergleiche ich die Zahlen, die als Char Array gegeben sind?
		/*if (zahl1 > zahl2){
			vz = '+';
		}
		else{
			vz = '-';
		}*/
	}
	else if ((zahl1VZ == '-' && zahl2VZ == '-' && operation == '-') || (zahl1VZ == '-' && zahl2VZ == '+' && operation == '+')){
		operation = '+';
		/*if (zahl1 > zahl2){
			vz = '-';
		}
		else{
			vz = '+';
		}*/
	}
	return 0;
}
