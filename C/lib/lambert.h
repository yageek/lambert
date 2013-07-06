#include "basic.h"

typedef enum {
	LAMBERT_I,
	LABERT_II
} LambertZone;

/*
 * Convert a Point struct from one lambert zone to WGS84 
 *
 */

void lambert_to_wgs84(const Point * org, LambertZone zone, Point *dest);
