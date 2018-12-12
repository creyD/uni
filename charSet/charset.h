typedef struct charset {
  unsigned char bits[7];
} charset_t;

typedef enum { CS_UNION,  // Vereinigung
	       CS_CUT,    // Schnitt
	       CS_SYMDIFF // Symmetrische Differenz 
} csopt_t;

charset_t *charset_new(const char* elements);
int charset_op(charset_t* s1, const charset_t *s2, csopt_t op);
char charset_tos(const charset_t* s);
