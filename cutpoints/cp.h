/* cp.h - Headerdatei */

typedef enum{SHAPE_CIRCLE, SHAPE_RECTANGLE, SHAPE_TRIANGLE} shape_t;

// Kartesische Koordinaten
typedef struct { 
  double x;
  double y;
} point_t;

typedef struct {
  shape_t     type;         // welche Art von geometrischer Figur?
  point_t     points[3];    // Punkte
} sprite_t;
  
point_t *cutpoints(sprite_t sprite_a, sprite_t sprite_b, int *num)
;
