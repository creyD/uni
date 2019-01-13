#include "cp.h"
#include "stdaup.h"
#include "math.h"

// Berechnet den Schnittpunkt zweier Strecken (gibt 0 zuruek wenn keine gefunden wurde)
int hitpoint(point_t a, point_t b, point_t c, point_t d, point_t *results){
	double denom = (d.y - c.y) * (b.x - a.x) - (d.x - c.x) * (b.y - a.y);
	if (fabs(denom) == 0){
		return 0; 
	}
	double ua = ((d.x - c.x) * (a.y - c.y) - (d.y - c.y) * (a.x - c.x)) / denom;
	double ub = ((b.x - a.x) * (a.y - c.y) - (b.y - a.y) * (a.x - c.x)) / denom;
	if (ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1){
		point_t schnittpunkt;
		schnittpunkt.x = a.x + ua * (b.x - a.x);
		schnittpunkt.y = a.y + ua * (b.y - a.y);
		results = schnittpunkt;
		results ++;
		return 1;
	} else {
		return 0;
	}
}

point_t *cutpoints(sprite_t sprite_a, sprite_t shape_b, int *num){
	point_t *results = (point_t *)malloc(7);
	return results;
}

int main()
{
	return 0;
}
