#include <CUnit/Basic.h>
#include <CUnit/Console.h>
#include <CUnit/Automated.h>
#include <math.h>
#include <stdlib.h>
#include "../src/lambert.h"
#include "../src/ntv2.h"

#define DISPLAY_POINT(point) printf(#point" X:%f | Y:%f | Z:%f\n",point.x,point.y,point.z);

int init_suite_success(void) { return 0; }
int init_suite_failure(void) { return -1; }
int clean_suite_success(void) { return 0; }
int clean_suite_failure(void) { return -1; }

char buffer[20];
char format[20];

double truncate(double val, int n)
{
	sprintf(format,"%%.%df",n);
	sprintf(buffer,format,val);
	return atof(buffer);

}

double rounded_down(double val,int n){
	double p = pow(10,n);
	return floorf(val*p)/p;
}

void test_lambert_deg(void)
{
	YGPoint org = {999534.581,112186.569,0};
	YGPoint dest = {0,0,0};
	YGLambertZone zone = LAMBERT_I;

	lambert_to_wgs84_deg(&org, &dest, zone);
	printf("(Deg)Lon:%.11f - Lat:%.11f - H:%.11f\n",dest.x,dest.y,dest.z);
}

void test_lambert(void)
{

	YGPoint org = {999534.581,112186.569,0};
	YGPoint dest = {0,0,0};
	YGLambertZone zone = LAMBERT_I;

	lambert_to_wgs84(&org, &dest, zone);

}

void test_algo009(void)
{	
	double lon[3] = {0.01745329248 ,0.00290888212 ,0.00581776423};
	double lat[3] = {0.02036217457,0.00000000000 ,-0.03199770300};
	double he[3] = {100.0000,10.0000 ,2000.0000};
	double a[3] = {6378249.2000 ,6378249.2000 ,6378249.2000};
	double e[3] = {0.08248325679 ,0.08248325679 ,0.08248325679};


	unsigned int i;
	for (i =0; i < 3;++i)
	{
		YGPoint pt  = geographic_to_cartesian(lon[i],lat[i],he[i],a[i],e[i]);
		DISPLAY_POINT(pt);
	}

}

void test_algo0021 (void)

{
	double n = 6393174.9755;
	double lat = 0.97738438100;
	double a = 6378388.0000;
	double e = 0.081991890;

	double calc = lambert_normal(lat,a,e);
	printf("Expected:%.4f | Computed:%.4f\n",n,calc);
	CU_ASSERT(n == truncate(calc,4));

}
void test_algo0002(void)
{

	/*
	* See IGN "Jeux d'essai"
	*/

	double lat_iso[3] = {1.00552653648,-0.30261690060 ,0.2000000000};
	double e[3] = {0.08199188998,0.08199188998,0.08199188998};
	double eps[3] = {1.0e-11,1.0e-11,1.0e-11};

	double phi[3] = {0.87266462600, -0.29999999997 ,0.19998903369};

	unsigned int index;

		for(index = 0;index < 3;index++)
		{
			double result = lat_from_lat_iso(lat_iso[index], e[index], eps[index]);
			result = truncate(result,11);
			CU_ASSERT(result == phi[index]);
		}
}


void test_algo0012(void)
{

	double a[3] = {6378249.2000, 6378249.2000 ,6378249.2000};
	double e[3] = {0.08248325679, 0.08248325679, 0.08248325679};
	double x[3] = {6376064.6950, 6378232.2150, 6376897.5370};
	double y[3] = {111294.6230, 18553.5780, 37099.7050};
	double z[3] = {128984.7250, 0.0000, -202730.9070};
	double eps[3] = {1e-11,1e-11,1e-11};

	double lon[3] = {0.01745329248, 0.00290888212, 0.00581776423};
	double lat[3] = {0.02036217457, 0.00000000000, -0.03199770301};
	double he[3] = {99.9995, 10.0001, 2000.0001};

	unsigned int i;
	 double ign_eps = 1e-11;
	for(i=0; i < 3;++i)
	{
		YGPoint sample = {x[i],y[i],z[i]};
		YGPoint val ;
		val = cartesian_to_geographic(sample,LON_MERID_PARIS,a[i],e[i],eps[i]);
		
		// printf("X Computed:%.11f - Expected:%.11f\n",val.x,lon[i]);
		CU_ASSERT(fabs(val.x - lon[i]) <= ign_eps);
		// printf("Y Computed:%.11f - Expected:%.11f\n",val.y,lat[i]);
		CU_ASSERT(fabs(val.y - lat[i]) <= ign_eps);
		// printf("Z Computed:%.11f - Expected:%.11f\n",val.z,he[i]);
		CU_ASSERT(truncate(val.z,4) == he[i] ) ;
	}


}
void test_algo004(void)
{

	YGPoint org = {1029705.083,272723.849,0};
	YGPoint dest = {0,0,0};
	YGPoint expected = {0.145512099,0.872664626};


	lambert_to_geographic(&org,&dest, LAMBERT_I, LON_MERID_GREENWICH,E_CLARK_IGN,1e-9);
	printf("Lat:%.9f - Lon:%.9f - Expected:Lat:%.9f - Lon:%.9f\n",dest.x,dest.y,expected.x,expected.y);
	CU_ASSERT(fabs(dest.x - expected.x) <= 1e-9);
	CU_ASSERT(fabs(dest.y - expected.y) <= 1e-9);
}


void testBug2(void)
{
	YGPoint org = {668832.5384,6950138.7285,0};
	YGPoint dest = {0,0,0};
	YGLambertZone zone= LAMBERT_93;

	lambert_to_wgs84_deg(&org,&dest,zone);
	printf("Lat:%.9f - Lon:%.9f",dest.y,dest.x);

}
void testOpenGrid(void)
{	
	YGPoint org = {.x=2.424971108, .y=48.844445839,.z=0,.unit=DEGREE};
    YGPoint dest = {0,0,0,DEGREE};
    
   YGTransform tr = rgf93_to_ntf(org);
    YGPoint t = {-tr.tx,-tr.ty,-tr.tz};
    YGPoint null= {0,0,0};
    
    org = pointToRadian(org);
    org =  geographic_to_cartesian(org.x,org.y,org.z,A_WGS84,E_WGS84);
    
    org =  switch_geodesic_system(org, t, 0, null);
    org = cartesian_to_geographic(org, LON_MERID_PARIS, A_CLARK_IGN, E_CLARK_IGN, DEFAULT_EPS);
    
    org = pointToDegree(org);
}

int main(int argc, char **argv){

	CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

  /* add a suite to the registry */
   pSuite = CU_add_suite("Suite_success", init_suite_success, clean_suite_success);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   if ( NULL == CU_add_test(pSuite, "Test Algo0002", test_algo0002) ||
        NULL == CU_add_test(pSuite, "Test Algo0012", test_algo0012) ||
        NULL == CU_add_test(pSuite,"Test Algo004",test_algo004)     ||
        NULL == CU_add_test(pSuite,"Test algo0021",test_algo0021)   ||
        NULL == CU_add_test(pSuite,"test_algo009",test_algo009)     ||
        NULL == CU_add_test(pSuite,"test_algo009",test_lambert_deg)     ||
        NULL == CU_add_test(pSuite,"testBug2",testBug2)     ||
        NULL == CU_add_test(pSuite,"testNTFRGF93",testOpenGrid)     ||
        NULL == CU_add_test(pSuite, "Test lambert", test_lambert)
      ) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

     CU_basic_set_mode(CU_BRM_VERBOSE);
 	 CU_basic_run_tests();
     // CU_automated_run_tests();
  
     CU_list_tests_to_file();


      /* Clean up registry and return */
   CU_cleanup_registry();
   return CU_get_error();
	
        return 0;

}
