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

// Pointer muss an linkster Stelle sein
unsigned long convertToDecimal(int * number, unsigned short b, int i){
	unsigned long decimal = 0;
	for (int f = i; f >= 0; f--){
		decimal += *number * expon(b, f);
		number--;
	}
	return decimal;
}

unsigned long ringshift(unsigned long v, unsigned short b, unsigned short k){
	unsigned long remaining = v;
	int i = 0;
	int *converted = (int *) malloc((sizeof(int) * (v / (b + 1))));

	while (remaining > 0){
		*converted = remaining % b;
		remaining /= b;
		converted++;
		i++;
	}

	int *flipped = (int *) malloc(sizeof(int) * i);
	for (int f = i; f >= 0; f--){
		*flipped = *converted;
		converted--;
		flipped++;
	}
	free(converted);

	// Ringtausch
	for (int f = i; f >= 0; f--){
		if (f == k){
			*flipped = 0;
		}
		flipped--;
	}

	unsigned long result = convertToDecimal(flipped, b, i);
	free(flipped);
	return result;
}

int main()
{
	printf("%lu\n", ringshift(1234, 2, 1));
	return 0;
}
