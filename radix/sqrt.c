// Programm zur Wurzelberechnung nach Heron
unsigned long int squareroot(unsigned long int val);

// NO LIBARIES, LOOPS, GLOBAL VARIABLES, ONLY LONG INT

// Heron Test (REMOVE BEFORE DEPLOYMENT)
int printf(const char *, ...);

// The iterator is called for recusively using the heron sheme
unsigned long int iterator(unsigned long int a, unsigned long int val, int i){
	if (i == 100){
		return iterator(a, 0.5*(val+a/val), i++);
	}
	else{
		return val;
	}
}

// Squareroot main function
unsigned long int squareroot(unsigned long int val){
	unsigned long int startwert = 0.5 * (1 + val / 2);
	if (val == 0){
		return 0;
	}
	else{
		return iterator(val, startwert, 0);
	}
}

int main (){
	printf("Wurzel aus %lu ist %lu\n",(unsigned long)12345, squareroot((unsigned long)12345));
	printf("Wurzel aus %lu ist %lu\n",(unsigned long)81, squareroot((unsigned long)81));
	printf("Wurzel aus %lu ist %lu\n",(unsigned long)0, squareroot((unsigned long)0));
	printf("Wurzel aus %lu ist %lu\n",(unsigned long)9999, squareroot((unsigned long)9999));
	return 0;
}
