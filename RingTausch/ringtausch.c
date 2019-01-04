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

unsigned long ringshift(unsigned long v, unsigned short b, unsigned short k){
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
	k++;
	return result;
}

int main()
{
	printf("%lu\n", ringshift(1234,10,2));
	return 0;
}
