#include "stdaup.h"

unsigned long ringshift(unsigned long v, unsigned short b, unsigned short k);
unsigned long maxringshift(unsigned long v, unsigned short b, unsigned short l);
unsigned long convert(unsigned v, unsigned short b);
unsigned long shift(unsigned long number, unsigned short k);
unsigned long convertToDecimal(unsigned long number, unsigned short b);
unsigned long expon(unsigned long base, unsigned long exp);

unsigned long convert(unsigned v, unsigned short b){
	unsigned long converted = 0, remaining = v, counter = 1;
	while (remaining > 0){
		converted += (remaining % b) * counter;
		remaining /= b;
		counter *= 10;
	}
	return converted;
}

unsigned long shift(unsigned long number, unsigned short k){
	if (k <= 0){
		
	}else{
		
	}
	return 1;
}

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

unsigned long convertToDecimal(unsigned long number, unsigned short b){
	unsigned long decimal = 0, counter = 0;
	while (number > 0){
		decimal += number % 10 * expon(b, counter);
		number /= 10;
		counter++;
	}
	return decimal;
}


unsigned long ringshift(unsigned long v, unsigned short b, unsigned short k){
	unsigned long converted = convert(v, b);
	unsigned long shifted = shift(converted, k);
	unsigned long result = convertToDecimal(shifted, b);
	return result;
}

int main()
{
	printf("%lu\n", ringshift(1234, 2, 1));
	return 0;
}
