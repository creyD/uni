// Programm zur Wurzelberechnung nach Heron
unsigned long int squareroot(unsigned long int val);

// NO LIBARIES, LOOPS, GLOBAL VARIABLES, ONLY LONG INT

// Heron Test (REMOVE BEFORE DEPLOYMENT)
int printf(const char *, ...);

int main (){
	printf("Wurzel aus %lu ist %lu",(unsigned long)9, squareroot((unsigned long)9)); return 0;
}

unsigned long int iterator(unsigned long int val, unsigned long int a) {
	if (a * a == val + 1 || a * a == val - 1 || a * a == val){
		return a;
	}
	else {
		return iterator(0.5 * (a + val / a));
	}
}

// Heron Squareroot Function
unsigned long int squareroot(unsigned long int val) {
	int startwert = val + 1 / 2;
	return iterator(val, startwert);
}
