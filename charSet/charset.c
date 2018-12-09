extern int printf(const char *restrict __format, ...);
extern void *malloc(size_t);
extern void *calloc(size_t, size_t);
extern void *realloc (void *, size_t);
extern void free (void *);

typedef struct charset { 
	unsigned char bits[7];
} charset_t;

charset_t *charset_new(const char* elements);

int main(int argc, char const *argv[])
{
	charset_new(argv);
	return 0;
}

int stringLength(const char* string){
	int j = 0;

	while 1{
		if (string[j] == '\0'){
			return j;
		}
		j++;
	}
}

charset_t *charset_new(const char* elements){
	*new_charset = charset;
	inputLaenge = stringLength(elements);

	for (int i = 0; i <= inputLaenge; i++){
		// Großbuchstaben 65 - 90
		if (elements[i] >= 65 && elements[i] <= 72){

		}
		// Kleinbuchstaben 97 - 122
		else if (elements[i] >= 97 && elements <= 122){

		}
	}
}
