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
	int i = 0;
	// Konvertieren in das jeweilige Zahlensystem
	int *converted = (int *) malloc(sizeof(int) * (v / b + 1));
	while (v > 0){
		*converted = v % b;
		v /= b;
		converted++;
		i++;
	}
	
	// Spiegeln der Zahl
	int *flipped = (int *) malloc(sizeof(int) * i);
	for (int f = 0; f < i; f++){
		*flipped = *converted;
		converted--;
		flipped++;
	}
	free(converted);

	// Zurueckkonvertierung in das Dezimalsystem
	unsigned long result = 0;
	for (int f = i; f > 0; f--){
		result += *(flipped - 1) * expon(b, f);
		flipped--;
	}
	k++;
	free(flipped);
	return result;
}

int main()
{
	printf("%lu\n", ringshift(123456789, 10, 2));
	return 0;
}
