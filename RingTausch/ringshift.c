#include "stdaup.h"

unsigned long ringshift(unsigned long v, unsigned short b, unsigned short k);
unsigned long maxringshift(unsigned long v, unsigned short b, unsigned short l);

// Exponentialfunktion
unsigned long expon(unsigned long base, unsigned long exp){
	unsigned long c = 1;
	if (exp == 0){
		return 1;
	}
	for (unsigned long i = 0; i < exp; i++){
		c *= base;
	}
	return c;
}

// Gibt Stellen einer Zahl zuruek
int getDigits(unsigned long number){
	int digits = 0;
	while (number) {
		number /= 10;
		digits++;
	}
	return digits;
}

// Das O Kalkuel berechnet sich aus der Anzahl fixer Zeiten (+1) pro Schritt in der Funktion und
// den dynamischen Zeiten, wie Schleifen, die je nach Laenge der Eingabedaten variieren.
// Dennoch haben Schleifen einen statischen Teil (initialisierung der Indexvariable)
// 1 + 1 + 5 * n + 1 + 1 + 1 + 7 * n + 1 + 1 + 1 + 4 * n + 1 + 1 = 10 + 16n = O(n)

// Ringtauschfunktion
unsigned long ringshift(unsigned long v, unsigned short b, unsigned short k){
	// Kein Fehlerabfang fuer k <= 0 usw in der Funktion aufgrund der Aufgabenstellung
	// Umrechnen der Zahl in das Zielsystem
	int *converted = (int *) malloc(sizeof(int) * (v / b + 1));

	int counter = 0;
	while (v > 0){
		*converted = v % b;
		converted++;
		v /= b;
		counter++;
	}

	// Spiegeln und tauschen der Zahlen
	int *flipped = (int *) malloc(sizeof(int) * counter);
	int cache = 0;
	for (int i = 0; i < counter; i++){
		converted--;
		// Sobald die jeweilige Stelle erreicht wird, wird statt der regulaeren Zahl eine andere eingefuegt
		if (i == counter - (k + 2)){
			cache = *converted;
			*flipped = *(converted - 1);
		}else if (i == counter - (k + 1)){
			*flipped = *(converted - 1);
		}else if (i == counter - k){
			*flipped = cache;
		}else{
			*flipped = *converted;
		}
		flipped++;
	}
	free(converted);

	// Zurueckkonvertierung in das Dezimalsystem
	unsigned long result = 0;
	for (int i = 0; i < counter; i++){
		result += *(flipped - 1) * expon(b, i);
		flipped--;
	}
	free(flipped);
	return result;
}

unsigned long maxringshift(unsigned long v, unsigned short b, unsigned short l){
	int digits = getDigits(v);
	unsigned long maximum = ringshift(v, b, 1);

	for (int j = 1; j < l + 1; j++){
		unsigned long l_maximum = 0;
		for (int i = 1; i < digits + 1; i++){
			if (ringshift(maximum, b, i) > l_maximum){
				l_maximum = ringshift(maximum, b, i);
			}
		}
		if (l_maximum > maximum){
			maximum = l_maximum;
		}
	}
	return maximum;
}

int main()
{
	printf("%lu\n", ringshift(1234,10,2));
	printf("%lu\n", ringshift(1234,2,3));
	printf("%lu\n", ringshift(1000,23,1));
	printf("%lu\n", maxringshift(1234,10,5));
	printf("%lu\n", maxringshift(5,2,8));
	printf("%lu\n", maxringshift(5,10,5));
	printf("%lu\n", maxringshift(15,3,3));
	return 0;
}
