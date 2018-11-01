// Programm zur Wurzelberechnung nach Heron
unsigned long int squareroot(unsigned long int val);

// NO LIBARIES, LOOPS, GLOBAL VARIABLES, ONLY LONG INT

// Heron Test (REMOVE BEFORE DEPLOYMENT)
int printf(const char *, ...);

int main (){
	printf("Wurzel aus %lu ist %lu\n",(unsigned long)12345, squareroot((unsigned long)12345));
	printf("Wurzel aus %lu ist %lu\n",(unsigned long)81, squareroot((unsigned long)81));
	printf("Wurzel aus %lu ist %lu\n",(unsigned long)0, squareroot((unsigned long)0));
	printf("Wurzel aus %lu ist %lu\n",(unsigned long)9999, squareroot((unsigned long)9999));
	return 0;
}

unsigned long int iterator(unsigned long int val, unsigned long int a) {
	if (a * a == val + 1 || a * a == val - 1 || a * a == val){
		return val;
	}
	else {
		return iterator(a, 0.5 * (a + val / a));
	}
}

// Heron Squareroot Function
unsigned long int squareroot(unsigned long int val) {
	unsigned long int startwert = val + 1 / 2;
	if (val == 0){
		return 0;
	}
	else {
		return iterator(val, startwert);
	}
}
