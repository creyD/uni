#include <stdio.h>
#include <stdlib.h>

int euclid(int, int);

int main(const int c, const char* v[]){
	printf("GGT:");
	int e = euclid(atoi(v[1]), atoi(v[2]));
	printf("%d\n", e);
	return 0;
}

int euclid(int x, int y){
	if (x==y) return x;
	else if (x>y) return euclid(x-y,y);
	else return euclid(y-x,x);
}
