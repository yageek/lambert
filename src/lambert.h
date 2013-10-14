#ifndef __LAMBERT_H
#define __LAMBERT_H


#define DEFAULT_EPS 1e-10
#define E_CLARK_IGN 0.08248325676
#define E_WGS84 0.08181919106

#define A_CLARK_IGN 6378249.2
#define A_WGS84 6378137.0

#define LON_MERID_PARIS 0
#define LON_MERID_GREENWICH 0.04079234433
#define LON_MERID_IERS (LON_MERID_GREENWICH + (0.9/3600.0)*M_PI/180)
#define AUTOCOMEIQUE_FIRST 44*M_PI/180
#define AUTOCOMEIQUE_SECOND 49*M_PI/180
#define LAT_ORIG 46.5*M_PI/180
#define ct_x0 700000.0
#define ct_y0 6600000.0

#define DISPLAY_YGPoint(YGPoint) printf(#YGPoint" X:%f | Y:%f | Z:%f\n",YGPoint.x,YGPoint.y,YGPoint.z);
#define DISPLAY_YGPoint_REF(YGPoint) printf(#YGPoint" X:%f | Y:%f | Z:%f\n",YGPoint->x,YGPoint->y,YGPoint->z);

typedef enum {
	LAMBERT_I=0,
	LAMBERT_II=1,
	LAMBERT_III=2,
	LAMBERT_IV=3,
	LAMBERT_II_E=4,
	LAMBERT_93= 5
} YGLambertZone;

typedef enum {
    DEGREE,
    GRAD,
    RADIAN
} CoordUnit;

typedef struct {
	double x;
	double y;
	double z;
    CoordUnit unit;
} YGPoint;

typedef struct
{
    double tx;
    double ty;
    double tz;
} YGTransform;

typedef YGPoint Vector;

YGPoint pointToRadian(YGPoint p);
YGPoint pointToDegree(YGPoint p);

/*
 * ALGO0021 - Calcul de la grande Normale 
 *
*/
double lambert_normal(double lat, double a, double e);

/*
 * Convert a YGPoint struct from one lambert zone to WGS84 (Rad)
 *
 */
void lambert_to_wgs84(const YGPoint * org, YGPoint *dest, YGLambertZone zone);

/*
 * Convert a YGPoint struct from one lambert zone to WGS84 (Deg)
 *
 */
void lambert_to_wgs84_deg(const YGPoint * org, YGPoint *dest, YGLambertZone zone);

/*
 * ALGO0002
 */

double lat_from_lat_iso(double lat_iso, double e, double eps);

/*
* ALGO0012
*/

YGPoint cartesian_to_geographic(YGPoint org, double meridien, double a, double e , double eps);

/*
 * ALGO004
 */
void lambert_to_geographic(const YGPoint * org,YGPoint *dest, YGLambertZone zone, double lon_merid, double e, double eps);

/**
 * ALGO0009 - Transformations geographiques -> cartésiennes
 *
 *
 */

 YGPoint geographic_to_cartesian(double lon, double lat, double he, double a, double e);

 /**
 * ALGO13 Transformation de Coordonnées à 7 paramètres entre deux systèmes géodésiques
 */
 
 YGPoint switch_geodesic_system(YGPoint u, Vector t, double d, Vector r);
 
 /**
 * Algo0001  Calcul de la latitude isomérique
 */
double lat_iso(double lat, double e);

/** 
* Algo003 
*/
YGPoint coord_transform(double e, double n, double c, double lambda_c, double x_s, double y_s , double lon, double lat);

/**
 * Algo 01
 */
double latitude_iso_from_lat(double lat, double e);
 #endif