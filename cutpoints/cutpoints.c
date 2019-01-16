#include "cp.h"
#include "stdaup.h"
#include "math.h"

// Berechnet den Schnittpunkt zweier Strecken (gibt 0 zuruek wenn keine gefunden wurde)
int get_hitpoint(point_t a, point_t b, point_t c, point_t d, point_t *results, int counter){
	double denom = (d.y - c.y) * (b.x - a.x) - (d.x - c.x) * (b.y - a.y);
	if (fabs(denom) == 0){
		return 0; 
	}
	double ua = ((d.x - c.x) * (a.y - c.y) - (d.y - c.y) * (a.x - c.x)) / denom;
	double ub = ((b.x - a.x) * (a.y - c.y) - (b.y - a.y) * (a.x - c.x)) / denom;
	if (ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1){
		point_t schnittpunkt = {a.x + ua * (b.x - a.x), a.y + ua * (b.y - a.y)};
		// Duplicate Check Pending
		//printf("Gefundener Schnittpunkt: %f | %f\n", schnittpunkt.x, schnittpunkt.y);
		results[counter] = schnittpunkt;
		return 1;
	} else {
		return 0;
	}
}

point_t *cutpoints(sprite_t sprite_a, sprite_t sprite_b, int *num){
	// Array fuer die Ergebnisse anlegen (max 8 Schnittpunkte)
	point_t *results = (point_t *)malloc(8 * sizeof(point_t));
	// Schnittpunkte auf 0 setzen, um Fehlausgaben zu verhindern
	*num = 0;
	if (sprite_a.type == SHAPE_CIRCLE || sprite_b.type == SHAPE_CIRCLE){
		return results;
	}else{
		for (int i = 1; i <= 2; i++){
			for (int j = 1; j <= 2; j++){
				*num = get_hitpoint(sprite_a.points[0], sprite_a.points[i], sprite_b.points[0], sprite_b.points[j], results, *num);
			}
			if (sprite_b.type == SHAPE_TRIANGLE){
				*num = get_hitpoint(sprite_a.points[0], sprite_a.points[i], sprite_b.points[1], sprite_b.points[2], results, *num);
			} else if (sprite_b.type == SHAPE_RECTANGLE){
				point_t d = {.x = sprite_b.points[1].x, .y = sprite_b.points[2].y};
				*num = get_hitpoint(sprite_a.points[0], sprite_a.points[i], sprite_b.points[1], d, results, *num);
				*num = get_hitpoint(sprite_a.points[0], sprite_a.points[i], sprite_b.points[2], d, results, *num);
			}
		}
		/*for (int i = 0; i <= 2; i++){
			for (int j = 0; j <= 2; j++){
				*num += get_hitpoint(sprite_a.points[i / 2], sprite_a.points[(int)round(i * 0.7) + 1], sprite_b.points[j / 2], sprite_b.points[(int)round(j * 0.7) + 1], results, *num);
			}
		}*/
	}
	return results;
}

int main()
{
	sprite_t name = { .type = SHAPE_TRIANGLE, .points = {{-1,-2},{0,1},{1,-2}}};
	sprite_t nametwo = { .type = SHAPE_TRIANGLE, .points = {{-1,0},{-1,1},{1,1}}};
	int *number = (int *)malloc(10);
	point_t *test = cutpoints(name, nametwo, number);

	for (int i = 0; i < *number; i++){
		printf("Schnittpunkt %i: %f | %f\n", i, test[i].x, test[i].y);
	}
	printf("Anzahl Schnittpunkte: %i\n", *number);
	return 0;
}
