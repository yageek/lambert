/*
 *	Source des algorithmes : http://geodesie.ign.fr/contenu/fichiers/documentation/algorithmes/notice/NTG_71.pdf
 *  
*/

#include "lambert.h"

#include <math.h>
#include <stdio.h>

#define RAD_TO_DEG(x) x*180/M_PI
#define DISPLAY_POINT(point) printf(#point" X:%f | Y:%f | Z:%f\n",point.x,point.y,point.z);
#define DISPLAY_POINT_REF(point) printf(#point" X:%f | Y:%f | Z:%f\n",point->x,point->y,point->z);

static double lambert_n[6] = {0.7604059656, 0.7289686274, 0.6959127966, 0.6712679322, 0.7289686274, 0.7256077650};
static double lambert_c[6] = {11603796.98, 11745793.39, 11947992.52, 12136281.99, 11745793.39, 11754255.426};
static double lambert_xs[6]= {600000.0, 600000.0, 600000.0, 234.358, 600000.0, 700000.0};
static double lambert_ys[6]= {5657616.674, 6199695.768, 6791905.085, 7239161.542, 8199695.768, 12655612.050};


/* 
 * ALGO0002
 */

double lat_from_lat_iso(double lat_iso, double e,double eps)
{

	double phi_0 =  2*atan(exp(lat_iso)) - M_PI_2;
	double phi_i = 2*atan(pow((1+e*sin(phi_0))/(1-e*sin(phi_0)),e/2.0)*exp(lat_iso)) - M_PI_2;
	double delta ; 
	while(delta = fabs(phi_i - phi_0),delta > eps)
	{	
		phi_0 = phi_i;
		phi_i = 2*atan(pow((1+e*sin(phi_0))/(1-e*sin(phi_0)),e/2.0)*exp(lat_iso)) - M_PI_2;
	}

	return phi_i;

}
/*
*	ALGO0004 - Lambert vers geographiques
*/

void lambert_to_geographic(const Point * org,Point *dest, LambertZone zone, double lon_merid, double e, double eps)
{
	double n = lambert_n[zone];
	double C = lambert_c[zone];
	double x_s = lambert_xs[zone];
	double y_s = lambert_ys[zone];

	double x = org->x;
	double y = org->y;

	double lon, gamma, R, lat_iso;

	R = sqrt((x-x_s)*(x-x_s)+(y-y_s)*(y-y_s));

	gamma = atan((x-x_s)/(y_s-y));

	lon = lon_merid + gamma/n;

	lat_iso = -1/n*log(fabs(R/C));

	double lat = lat_from_lat_iso(lat_iso,e,eps);

	dest->x = lon;
	dest->y = lat;
}


/*
 * ALGO0021 - Calcul de la grande Normale 
 *
*/

double lambert_normal(double lat, double a, double e)
{

	return a/sqrt(1-e*e*sin(lat)*sin(lat));
}

/**
 * ALGO0009 - Transformations geographiques -> cartésiennes
 *
 *
 */

 Point geographic_to_cartesian(double lon, double lat, double he, double a, double e)
 {
 	double N = lambert_normal(lat,a,e);
 	
 	Point pt = {0,0,0};
 	pt.x = (N+he)*cos(lat)*cos(lon);

 	pt.y = (N+he)*cos(lat)*sin(lon);

 	pt.z = (N*(1-e*e)+he)*sin(lat);

 	return pt;

 }

/*
 * ALGO0012 - Passage des coordonnées cartésiennes aux coordonnées géographiques
 */

 Point cartesian_to_geographic(Point org, double meridien, double a, double e , double eps)
 {
 	double x = org.x, y = org.y, z = org.z;

 	double lon = meridien + atan(y/x);

 	double module = sqrt(x*x + y*y);

 	double phi_0 = atan(z/(module*(1-(a*e*e)/sqrt(x*x+y*y+z*z))));
 	double phi_i = atan(z/module/(1-a*e*e*cos(phi_0)/(module * sqrt(1-e*e*sin(phi_0)*sin(phi_0)))));
 	double delta;
 	while(delta = fabs(phi_i - phi_0),delta > eps)
 	{
 		phi_0 = phi_i;
 		phi_i = atan(z/module/(1-a*e*e*cos(phi_0)/(module * sqrt(1-e*e*sin(phi_0)*sin(phi_0)))));

 	}
 	
 	double he = module/cos(phi_i) - a/sqrt(1-e*e*sin(phi_i)*sin(phi_i));
 	
 	Point pt;
 	pt.x = lon;
 	pt.y = phi_i;
 	pt.z = he;

 	return pt;
 }



/*
 * Convert Lambert -> WGS84
 * http://geodesie.ign.fr/contenu/fichiers/documentation/pedagogiques/transfo.pdf
 *
 */

void lambert_to_wgs84(const Point * org, Point *dest,LambertZone zone){

	lambert_to_geographic(org,dest,zone,LON_MERID_PARIS,E_CLARK_IGN,DEFAULT_EPS);

	 DISPLAY_POINT_REF(dest);

	 Point temp = geographic_to_cartesian(dest->x,dest->y,dest->z,A_CLARK_IGN,E_CLARK_IGN);

	 temp.x= temp.x - 168;
	 temp.y= temp.y - 60;
	 temp.z= temp.z + 320;
	 
	 DISPLAY_POINT(temp);

	 //WGS84 refers to greenwich
	 temp = cartesian_to_geographic(temp, LON_MERID_GREENWICH, A_WGS84,E_WGS84,DEFAULT_EPS);

	 DISPLAY_POINT(temp);

	 dest->x = temp.x;
	 dest->y = temp.y;

	 printf("(RAD)Lon:%.11f - Lat:%.11f | (DEG)Lon:%.11f - Lat:%.11f\n",dest->x,dest->y,RAD_TO_DEG(dest->x),RAD_TO_DEG(dest->y));

}