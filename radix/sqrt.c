// Programm zur Wurzelberechnung nach Heron
unsigned long int squareroot(unsigned long int val);

// NO LIBARIES, LOOPS, GLOBAL VARIABLES, ONLY LONG INT

// Heron Test (REMOVE BEFORE DEPLOYMENT)
int printf(const char *, ...);

int main (){
	printf("Wurzel aus %lu ist %lu",(unsigned long)81, squareroot((unsigned long)81)); return 0;
}

// Heron Squareroot Function
unsigned long int squareroot(unsigned long int val) {
	int a = (val + 1) / 2;
	int c = 0.5 * a + val/a;
	return c;
}
