#ifndef __LAMBERT_H
#define __LAMBERT_H

#define DEFAULT_EPS 1e-10
#define E_CLARK_IGN 0.08248325676
#define E_WGS84 0.08181919106

#define A_CLARK_IGN 6378249.2
#define A_WGS84 6378137.0

#define LON_MERID_PARIS 0
#define LON_MERID_GREENWICH 0.04079234433

#define DISPLAY_YGLambertPoint(YGLambertPoint) printf(#YGLambertPoint" X:%f | Y:%f | Z:%f\n",YGLambertPoint.x,YGLambertPoint.y,YGLambertPoint.z);
#define DISPLAY_YGLambertPoint_REF(YGLambertPoint) printf(#YGLambertPoint" X:%f | Y:%f | Z:%f\n",YGLambertPoint->x,YGLambertPoint->y,YGLambertPoint->z);

typedef enum {
	LAMBERT_I=0,
	LAMBERT_II=1,
	LAMBERT_III=2,
	LAMBERT_IV=3,
	LAMBERT_II_E=4,
	LAMBERT_93= 5
} LambertZone;

typedef struct {
	double x;
	double y;
	double z;
} YGLambertPoint;

typedef YGLambertPoint Vector;


/*
 * ALGO0021 - Calcul de la grande Normale 
 *
*/
double lambert_normal(double lat, double a, double e);

/*
 * Convert a YGLambertPoint struct from one lambert zone to WGS84 (Rad)
 *
 */
void lambert_to_wgs84(const YGLambertPoint * org, YGLambertPoint *dest, LambertZone zone);

/*
 * Convert a YGLambertPoint struct from one lambert zone to WGS84 (Deg)
 *
 */
void lambert_to_wgs84_deg(const YGLambertPoint * org, YGLambertPoint *dest, LambertZone zone);

/*
 * ALGO0002
 */

double lat_from_lat_iso(double lat_iso, double e, double eps);

/*
* ALGO0012
*/

YGLambertPoint cartesian_to_geographic(YGLambertPoint org, double meridien, double a, double e , double eps);

/*
 * ALGO004
 */
void lambert_to_geographic(const YGLambertPoint * org,YGLambertPoint *dest, LambertZone zone, double lon_merid, double e, double eps);

/**
 * ALGO0009 - Transformations geographiques -> cartésiennes
 *
 *
 */

 YGLambertPoint geographic_to_cartesian(double lon, double lat, double he, double a, double e);

 /**
 * ALGO13 Transformation de Coordonnées à 7 paramètres entre deux systèmes géodésiques
 */
 
 YGLambertPoint switch_geodesic_system(YGLambertPoint u, Vector t, double d, Vector r);
 
 /**
 * Algo0001  Calcul de la latitude isomérique
 */
double lat_iso(double lat, double e);
 #endif