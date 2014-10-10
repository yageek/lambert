/*
 *	Source des algorithmes : http://geodesie.ign.fr/contenu/fichiers/documentation/algorithmes/notice/NTG_71.pdf
 *  
*/

#include "lambert.h"
 
#ifdef _WIN32
 #define _USE_MATH_DEFINES
#endif

#include <math.h>
#include <stdio.h>


static double lambert_n[6] = {0.7604059656, 0.7289686274, 0.6959127966, 0.6712679322, 0.7289686274, 0.7256077650};
static double lambert_c[6] = {11603796.98, 11745793.39, 11947992.52, 12136281.99, 11745793.39, 11754255.426};
static double lambert_xs[6]= {600000.0, 600000.0, 600000.0, 234.358, 600000.0, 700000.0};
static double lambert_ys[6]= {5657616.674, 6199695.768, 6791905.085, 7239161.542, 8199695.768, 12655612.050};

YGPoint __YGDegreeToRadian(YGPoint pt)
{
    pt.x = pt.x * M_PI / 180.0;
    pt.y = pt.y * M_PI / 180.0;
    pt.z = pt.z * M_PI / 180.0;
    
    pt.unit = RADIAN;
    
    return pt;
}

YGPoint __YGRadianToDegree(YGPoint pt)
{
        pt.x = pt.x * 180/ M_PI;
        pt.y = pt.y * 180/ M_PI;
        pt.z = pt.z * 180/ M_PI;
    
        pt.unit = DEGREE;
    
        return pt;
}

YGPoint __YGGradToRadian(YGPoint pt)
{
        pt.x = pt.x * M_PI/200.0;
        pt.y = pt.y * M_PI/200.0;
        pt.z = pt.z * M_PI/200.0;
    
        pt.unit = RADIAN;
    
        return pt;
}
YGPoint __YGRadianToGrad(YGPoint pt)
{
    pt.x = pt.x * 200.0/M_PI;
    pt.y = pt.y * 200.0/M_PI;
    pt.z = pt.z * 200.0/M_PI;
    
    pt.unit = GRAD;
    
    return pt;
}

YGPoint __YGGradToDegree(YGPoint pt)
{
    pt.x = pt.x * 180.0/200.0;
    pt.y = pt.y * 180.0/200.0;
    pt.z = pt.z * 180.0/200.0;
    
    pt.unit = DEGREE;
    
    return pt;
    
}

YGPoint __YGDegreeToGrad(YGPoint pt)
{
    pt.x = pt.x * 200.0/180.0;
    pt.y = pt.y * 200.0/180.0;
    pt.z = pt.z * 200.0/180.0;
    
    pt.unit = GRAD;
    
    return pt;
}


YGPoint YGPointToDegree(YGPoint pt)
{
    
    switch (pt.unit)
    {
        case RADIAN :
        {
            pt = __YGRadianToDegree(pt);
        }
            break;
        case GRAD :
        {
            pt = __YGGradToDegree(pt);
        }
            break;
       default:
            break;
    }
        
            return  pt;
    
}


YGPoint YGPointToRadian(YGPoint pt)
{
    switch (pt.unit)
    {
        case DEGREE :
        {
            pt = __YGDegreeToRadian(pt);
        }
            break;
        case GRAD :
        {
            pt = __YGGradToRadian(pt);
        }
            break;
        default:
            break;
    }
    
    return  pt;
}

YGPoint YGPointToGrad(YGPoint pt)
{
    switch (pt.unit)
    {
        case RADIAN :
        {
            pt = __YGRadianToGrad(pt);
        }
            break;
        case DEGREE :
        {
            pt = __YGDegreeToGrad(pt);
        }
            break;
        default:
            break;
    }

    return  pt;
}

YGPoint YGPointToUnit(YGPoint point, CoordUnit unit)
{
    switch (unit) {
        case DEGREE:
            return YGPointToDegree(point);
            break;
        case GRAD:
            return YGPointToGrad(point);
        case RADIAN :
            return YGPointToDegree(point);
            break;
        default:
            return point;
            break;
    }
}

/*****************
 ** IGN algorithms
*****************/

double __YGLatitudeISOFromLatitude(double lat, double e)
{
    return log(tan(M_PI_4+lat/2)*pow((1-e*sin(lat))/(1+e*sin(lat)),e/2));
}

/*
 * ALGO0002
 */

double __YGLatitudeFromLatitudeISO(double lat_iso, double e,double eps)
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

YGPoint __YGLambertToGeographic(YGPoint org, YGLambertZone zone, double lon_merid, double e, double eps)
{
	double n = lambert_n[zone];
	double C = lambert_c[zone];
	double x_s = lambert_xs[zone];
	double y_s = lambert_ys[zone];

	double x = org.x;
	double y = org.y;

	double lon, gamma, R, lat_iso;

	R = sqrt((x-x_s)*(x-x_s)+(y-y_s)*(y-y_s));

	gamma = atan((x-x_s)/(y_s-y));

	lon = lon_merid + gamma/n;

	lat_iso = -1/n*log(fabs(R/C));

	double lat = __YGLatitudeFromLatitudeISO(lat_iso,e,eps);

	org.x = lon;
	org.y = lat;
    
    return org;
}


/*
 * ALGO0021 - Calcul de la grande Normale 
 *
*/

double __YGLambertNormal(double lat, double a, double e)
{

	return a/sqrt(1-e*e*sin(lat)*sin(lat));
}

/**
 * ALGO0009 - Transformations geographiques -> cartésiennes
 *
 *
 */

 YGPoint __YGGeographicToCartesian(double lon, double lat, double he, double a, double e)
 {
 	double N = __YGLambertNormal(lat,a,e);
 	
 	YGPoint pt = {0,0,0};
 	pt.x = (N+he)*cos(lat)*cos(lon);

 	pt.y = (N+he)*cos(lat)*sin(lon);

 	pt.z = (N*(1-e*e)+he)*sin(lat);

 	return pt;

 }

/*
 * ALGO0012 - Passage des coordonnées cartésiennes aux coordonnées géographiques
 */

 YGPoint __YGCartesianToGeographic(YGPoint org, double meridien, double a, double e , double eps)
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
 	
 	YGPoint pt;
 	pt.x = lon;
 	pt.y = phi_i;
 	pt.z = he;     
    pt.unit = RADIAN;

 	return pt;
 }

/*
 * Convert Lambert -> WGS84
 * http://geodesie.ign.fr/contenu/fichiers/documentation/pedagogiques/transfo.pdf
 *
 */

YGPoint YGPointConvertWGS84(YGPoint point, YGLambertZone zone){
    
    if(point.unit != METER)
    {
            perror("Could not operate on a non METER based point!\n The points returned will be the same!\n");
            return  point;
    }
    
    if(LAMBERT_93 == zone)
    {
       point =  __YGLambertToGeographic(point,zone,LON_MERID_IERS,E_WGS84,DEFAULT_EPS);
    
    }
    else
    {
        point  = __YGLambertToGeographic(point,zone,LON_MERID_PARIS,E_CLARK_IGN,DEFAULT_EPS);
        point = __YGGeographicToCartesian(point.x,point.y,point.z,A_CLARK_IGN,E_CLARK_IGN);
    
        point.x-= 168;
        point.y-= 60;
        point.z+= 320;
    
        //WGS84 refers to greenwich
        point = __YGCartesianToGeographic(point, LON_MERID_GREENWICH, A_WGS84,E_WGS84,DEFAULT_EPS);
    }
    
    point.unit = RADIAN;
    return point;
}



double __YGLatitudeISO(double lat, double e)
{
	return log(tan(M_PI_4 + lat/2)*pow((1-e*sin(lat))/(1+e*sin(lat)),e/2));
}

YGPoint __YGCoordinatesTransform(double e, double n, double c, double lambda_c, double x_s, double y_s , double lon, double lat)
{
	YGPoint dest = {0,0,0};

	double latiso = __YGLatitudeISO(lat,e);
	dest.x = x_s + e*exp(-n*latiso)*sin(n*(lon-lambda_c));
	dest.y = y_s + e*exp(n*latiso)*cos(n*(lon-lambda_c));

	return dest;

}

YGPoint __YGSwitchGeodesicSystem(YGPoint u, Vector t, double d, Vector r)
{
	YGPoint v = {0,0,0};

	v.x = t.x + u.x*(1+d) + u.z * r.y - u.y * r.z;
	v.y = t.y + u.y*(1+d) + u.x * r.z - u.y * r.z;
	v.z = t.z +u.z*(1+d) + u.y*r.x -u.x*r.y;

	return v;

}