// Programm zur Wurzelberechnung nach Heron
unsigned long int squareroot(unsigned long int val);

// NO LIBARIES, LOOPS, GLOBAL VARIABLES, ONLY LONG INT

// Heron Test (REMOVE BEFORE DEPLOYMENT)
int printf(const char *, ...);

// The iterator is called for recusively using the heron sheme
unsigned long int iterator(unsigned long int val, unsigned long int a){
	a = (a+val/a)/2;
	if (a*a <= val) {
		return a;
	}
	else
	{
		return iterator(val,a);
	}
}

// Squareroot main function
unsigned long int squareroot(unsigned long int val){
	unsigned long int startwert = (1 + val) / 2;
	if (val == 0){
		return 0;
	}
	else
	{
		return iterator(val, startwert);
	}
}

int main (){
	printf("Wurzel aus %lu ist %lu\n",(unsigned long)12345, squareroot((unsigned long)12345));
	printf("Wurzel aus %lu ist %lu\n",(unsigned long)81, squareroot((unsigned long)81));
	printf("Wurzel aus %lu ist %lu\n",(unsigned long)0, squareroot((unsigned long)0));
	printf("Wurzel aus %lu ist %lu\n",(unsigned long)9999, squareroot((unsigned long)9999));
	printf("Wurzel aus %lu ist %lu\n",(unsigned long)9, squareroot((unsigned long)9));
	return 0;
}
