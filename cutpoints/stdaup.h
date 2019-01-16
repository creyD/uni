/* Functions of the C standard library that may be used in Algorithms and Programming */
typedef unsigned long size_t;
#define NULL 0L

extern int printf(const char *restrict __format, ...);
extern void *malloc(size_t);
extern void *calloc(size_t, size_t);
extern void *realloc (void *, size_t);
extern void free (void *);
