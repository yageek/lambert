#ifndef __LAMBERT_H
#define __LAMBERT_H


#define DEFAULT_EPS 1e-10
#define E_CLARK_IGN 0.08248325676
#define E_WGS84 0.08181919106

#define A_CLARK_IGN 6378249.2
#define A_WGS84 6378137.0

#define LON_MERID_PARIS 0
#define LON_MERID_GREENWICH 0.04079234433
#define LON_MERID_IERS (3*M_PI/180)
#define AUTOCOMEIQUE_FIRST 44*M_PI/180
#define AUTOCOMEIQUE_SECOND 49*M_PI/180
#define LAT_ORIG 46.5*M_PI/180
#define ct_x0 700000.0
#define ct_y0 6600000.0


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
    RADIAN,
    METER
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

#define __YGPointWithUnit(_x,_y,_z,_unit) {.x=_x, .y=_y,.z=_z,.unit=_unit};

#define YGDegreePoint(x,y,z) __YGPointWithUnit(x,y,z,DEGREE)
#define YGRadianPoint(x,y,z) __YGPointWithUnit(x,y,z,RADIAN)
#define YGGradPoint(x,y,z) __YGPointWithUnit(x,y,z,GRAD)
#define YGMeterPoint(x,y,z) __YGPointWithUnit(x,y,z,METER)
 

YGPoint YGPointToRadian(YGPoint p);
YGPoint YGPointToDegree(YGPoint p);
YGPoint YGPointToGrad(YGPoint p);
YGPoint YGPointToUnit(YGPoint point, CoordUnit unit);

/*
 * ALGO0021 - Calcul de la grande Normale 
 *
*/
double __YGLambertNormal(double lat, double a, double e);

/*
 * Convert a YGPoint struct from one lambert zone to WGS84 (Rad)
 *
 */


YGPoint YGPointConvertWGS84(YGPoint point, YGLambertZone zone);

/*
 * ALGO0002
 */

double __YGLatitudeFromLatitudeISO(double lat_iso, double e, double eps);

/*
* ALGO0012
*/

YGPoint __YGCartesianToGeographic(YGPoint org, double meridien, double a, double e , double eps);

/*
 * ALGO004
 */
YGPoint __YGLambertToGeographic(YGPoint org, YGLambertZone zone, double lon_merid, double e, double eps);

/**
 * ALGO0009 - Transformations geographiques -> cartésiennes
 *
 *
 */

 YGPoint __YGGeographicToCartesian(double lon, double lat, double he, double a, double e);

 /**
 * ALGO13 Transformation de Coordonnées à 7 paramètres entre deux systèmes géodésiques
 */
 
 YGPoint __YGSwitchGeodesicSystem(YGPoint u, Vector t, double d, Vector r);
 
 /**
 * Algo0001  Calcul de la latitude isomérique
 */
double __YGLatitudeISO(double lat, double e);

/** 
* Algo003 
*/
YGPoint __YGCoordinatesTransform(double e, double n, double c, double lambda_c, double x_s, double y_s , double lon, double lat);

/**
 * Algo 01
 */
double __YGLatitudeISOFromLatitude(double lat, double e);
 #endif