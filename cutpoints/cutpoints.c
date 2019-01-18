#include <math.h>
#include <stdlib.h>
#include "cp.h"

extern int printf(const char *restrict __format, ...);

typedef struct {
	point_t		points[4];
	double		max_betrag;
} viereck;

typedef struct {
	point_t		points[3];
	double		radius;
	point_t		mittelpunkt;
} kreis;

int is_duplicate(point_t point, point_t *array, int elements){
	for (int i = 0; i < elements; i++){
		if (array[i].x == point.x && array[i].y == point.y){
			return 1;
		}
	}
	return 0;
}

// Berechnet den Schnittpunkt zweier Strecken (gibt 0 zuruek wenn keine gefunden wurde)
int get_hitpoint(point_t a, point_t b, point_t c, point_t d, point_t *results, int counter){
	double determ = (d.y - c.y) * (b.x - a.x) - (d.x - c.x) * (b.y - a.y);
	if (fabs(determ) == 0){
		return 0; 
	}
	double ua = ((d.x - c.x) * (a.y - c.y) - (d.y - c.y) * (a.x - c.x)) / determ;
	double ub = ((b.x - a.x) * (a.y - c.y) - (b.y - a.y) * (a.x - c.x)) / determ;

	if (ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1){
		double x = a.x + ua * (b.x - a.x);
		double y = a.y + ua * (b.y - a.y);
		point_t schnittpunkt = {x, y};
		if (is_duplicate(schnittpunkt, results, counter) != 1){
			results[counter] = schnittpunkt;
			return 1;
		}
	}
	return 0;
}

// Berechnet die Strecke zwischen 2 Punkten
double get_distance(point_t a, point_t b){
	return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

point_t add_vectors(point_t a, point_t b){
	point_t test = {a.x + b.x, a.y + b.y};
	return test;
}

point_t span_vectors(point_t a, point_t b){
	point_t result = {b.x - a.x, b.y - a.y};
	return result;
}

viereck get_viereck(sprite_t a){
	double max_betrag = 0.0;
	point_t basis, punkt_a, b, d;
	for (int i = 0; i <= 2; i++){
		double temp_a = get_distance(a.points[i/2], a.points[(int)round(i * 0.7) + 1]);
		if (temp_a > max_betrag){
			basis = a.points[(int) 3 - (i/2) - ((int)round(i * 0.7) + 1)];
			punkt_a = a.points[i/2];
			b = a.points[(int)round(i * 0.7) + 1];
			d = add_vectors(add_vectors(span_vectors(basis, a.points[i/2]), span_vectors(basis, a.points[(int)round(i * 0.7) + 1])), basis);
			max_betrag = temp_a;
		}
	}
	viereck new_viereck = {.points = {basis, punkt_a, b, d}, .max_betrag = max_betrag};
	return new_viereck;
}

kreis get_kreis(sprite_t a){
	// Determinante vom Gesamtsystem ausrechnen
	double determ = a.points[1].x * a.points[2].y + a.points[0].x * a.points[1].y + a.points[2].x * a.points[0].y - a.points[1].x * a.points[0].y - a.points[2].x * a.points[1].y - a.points[0].x * a.points[2].y;
	// Ergebnisvektor errechnen
	double c_one = -1 * (pow(a.points[0].x, 2) + pow(a.points[0].y, 2));
	double c_two = -1 * (pow(a.points[1].x, 2) + pow(a.points[1].y, 2));
	double c_three = -1 * (pow(a.points[2].x, 2) + pow(a.points[2].y, 2));

	double determ_a = (c_one * a.points[1].x * a.points[2].y + a.points[0].x * a.points[1].y * c_three + a.points[0].y * a.points[2].x * c_two - c_three * a.points[1].x * a.points[0].y - a.points[2].x * a.points[1].y * c_one - a.points[2].y * c_two * a.points[0].x )/ determ;
	double determ_b = -1 * (c_two * a.points[2].y + c_one * a.points[1].y + a.points[0].y * c_three - c_two * a.points[0].y - c_three * a.points[1].y - a.points[2].y * c_one) / determ;
	double determ_c = -1 * (a.points[1].x * c_three + a.points[0].x * c_two + c_one * a.points[2].x - a.points[1].x * c_one - a.points[2].x * c_two - c_three * a.points[0].x) / determ;
	// Negative 0 (-0) abfangen, da sie das Ergebnis beeinflusst
	if (determ_b == 0){
		determ_b = 0;
	}
	if (determ_c == 0){
		determ_c = 0;
	}
	// Radius anhand der Determinanten berechnen
	double radius = sqrt(pow(determ_b/2, 2) + pow(determ_c/2, 2) - determ_a);

	printf("Radius: %f xm: %f ym: %f\n", radius, determ_b/2, determ_c/2);
	kreis new_kreis = {.points = {{a.points[0].x,a.points[0].y},{a.points[1].x,a.points[1].y},{a.points[2].x,a.points[2].y}}, .mittelpunkt = {determ_b/2, determ_c/2}, .radius = radius};
	return new_kreis;
}

point_t *cutpoints(sprite_t sprite_a, sprite_t sprite_b, int *num){
	// Array fuer die Ergebnisse anlegen (max 8 Schnittpunkte)
	point_t *results = (point_t *)malloc(8 * sizeof(point_t));
	// Schnittpunkte auf 0 initiieren, um Fehlausgaben zu verhindern
	*num = 0;
	int array[6] = {0,0,0,1,1,2}, array2[6] = {1,2,3,2,3,3};
	if (sprite_a.type == SHAPE_CIRCLE || sprite_b.type == SHAPE_CIRCLE){
		printf("In Arbeit!\n");
	}else if (sprite_a.type == SHAPE_TRIANGLE && sprite_b.type == SHAPE_TRIANGLE){
		for (int i = 0; i <= 2; i++){
			for (int j = 0; j <= 2; j++){
				*num += get_hitpoint(sprite_a.points[i / 2], sprite_a.points[(int)round(i * 0.7) + 1], sprite_b.points[j / 2], sprite_b.points[(int)round(j * 0.7) + 1], results, *num);
			}
		}
	}else if (sprite_a.type == SHAPE_RECTANGLE && sprite_b.type == SHAPE_RECTANGLE){
		viereck a = get_viereck(sprite_a), b = get_viereck(sprite_b);
		for (int i = 0; i < 6; i++){
			for (int j = 0; j < 6; j++){
				if (!(a.max_betrag == get_distance(a.points[(int) array[i]], a.points[(int) array2[i]]) || b.max_betrag == get_distance(b.points[(int) array[j]], b.points[(int) array2[j]]))){
					*num += get_hitpoint(a.points[(int) array[i]], a.points[(int) array2[i]], b.points[(int) array[j]], b.points[(int) array2[j]], results, *num);
				}
			}
		}
	}else{
		// Viereck und Dreieck trennen und einheitlich in a und b betiteln
		viereck a;
		sprite_t b;
		if (sprite_a.type == SHAPE_RECTANGLE){
			a = get_viereck(sprite_a);
			b = sprite_b;
		}else{
			a = get_viereck(sprite_b);
			b = sprite_a;
		}
		for (int i = 0; i < 6; i++){
			for (int j = 0; j <= 2; j++){
				if (!(a.max_betrag == get_distance(a.points[(int) array[i]], a.points[(int) array2[i]]))){
					*num += get_hitpoint(a.points[(int) array[i]], a.points[(int) array2[i]], b.points[j / 2], b.points[(int)round(j * 0.7) + 1], results, *num);
				}
			}
		}
	}

	if (*num == 0){
		results = NULL;
	}else{
		results = (point_t *) realloc(results, sizeof(point_t) * *num);
	}
	return results;
}

int main()
{
	sprite_t sprite_a={.type=SHAPE_CIRCLE, .points = {{5.0, 0.0}, {3.0, 2.0}, {3.0, -2.0}}};
	get_kreis(sprite_a);
	/*sprite_t sprite_a={.type=SHAPE_TRIANGLE, .points = {{-1.0, -2.0},{0.0, 1.0},{1.0, -2.0}}};
	sprite_t sprite_b={.type=SHAPE_RECTANGLE, .points = {{-1.0, 0.0},{-1.0, -1.0}, {1.0, -1.0}}};
	int *number = (int *)malloc(10);
	point_t *test = cutpoints(sprite_a, sprite_b, number);

	for (int i = 0; i < *number; i++){
		printf("Schnittpunkt %i: %f | %f\n", i + 1, test[i].x, test[i].y);
	}*/
	return 0;
}
