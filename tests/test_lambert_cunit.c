#include <CUnit/Basic.h>
#include <CUnit/Console.h>
#include <CUnit/Automated.h>
#include <math.h>
#include <stdlib.h>
#include "../src/lambert.h"
#include "../src/rgf93.h"


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

void test_algo009(void)
{	
	double lon[3] = {0.01745329248 ,0.00290888212 ,0.00581776423};
	double lat[3] = {0.02036217457,0.00000000000 ,-0.03199770300};
	double he[3] = {100.0000,10.0000 ,2000.0000};
	double a[3] = {6378249.2000 ,6378249.2000 ,6378249.2000};
	double e[3] = {0.08248325679 ,0.08248325679 ,0.08248325679};
    
    YGPoint expected[3] = {
        {6376064.6955,111294.6230,128984.7250, METER },
        {6378232.2149,18553.5780,0, METER },
        {6376897.5369,37099.7050,-202730.9070, METER }
    };


	unsigned int i;
	for (i =0; i < 3;++i)
	{
		YGPoint pt  = __YGGeographicToCartesian(lon[i],lat[i],he[i],a[i],e[i]);
        CU_ASSERT(fabs(pt.x - expected[i].x) <= 1e-4);
        CU_ASSERT(fabs(pt.y - expected[i].y) <= 1e-4);
        CU_ASSERT(fabs(pt.z - expected[i].z) <= 1e-4);
        
	}

}

void test_algo0021 (void)

{
	double n = 6393174.9755;
	double lat = 0.97738438100;
	double a = 6378388.0000;
	double e = 0.081991890;

	double calc = __YGLambertNormal(lat,a,e);
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
			double result = __YGLatitudeFromLatitudeISO(lat_iso[index], e[index], eps[index]);
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
		val = __YGCartesianToGeographic(sample,LON_MERID_PARIS,a[i],e[i],eps[i]);
		
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


	dest = __YGLambertToGeographic(org, LAMBERT_I, LON_MERID_GREENWICH,E_CLARK_IGN,1e-9);
 
	CU_ASSERT(fabs(dest.x - expected.x) <= 1e-9);
	CU_ASSERT(fabs(dest.y - expected.y) <= 1e-9);
}

void testBugLambert93(void)
{
	YGPoint org = YGMeterPoint(668832.5384,6950138.7285,0);
    YGPoint expected = YGDegreePoint(2.56865, 49.64961, 0);
	YGPoint dest;
	YGLambertZone zone = LAMBERT_93;

	dest = YGPointConvertWGS84(org,zone);
    dest = YGPointToDegree(dest);
    
	CU_ASSERT(fabs(dest.x - expected.x) <= 1e-5);
  	CU_ASSERT(fabs(dest.y - expected.y) <= 1e-5);

}


void testZenithStrasbourg(void)
{
    YGPoint org = YGMeterPoint(994300.623,113409.981,0);
    YGPoint expected = YGDegreePoint(7.68639475277068, 48.5953456709144, 0);
	YGPoint dest;
	YGLambertZone zone = LAMBERT_I;
    
	dest = YGPointConvertWGS84(org,zone);
    dest = YGPointToDegree(dest);
    
	CU_ASSERT(fabs(dest.x - expected.x) <= 1e-5);
  	CU_ASSERT(fabs(dest.y - expected.y) <= 1e-5);
}
void testBugLambertIIE(void)
{
    YGPoint org = YGMeterPoint(369419,1986498,0);
    YGPoint expected = YGDegreePoint( -0.579117201473994,44.84071560809383, 0);
	YGPoint dest;
	YGLambertZone zone = LAMBERT_II_E;
    
	dest = YGPointConvertWGS84(org,zone);
    dest = YGPointToDegree(dest);
    
	CU_ASSERT(fabs(dest.x - expected.x) <= 1e-4);
  	CU_ASSERT(fabs(dest.y - expected.y) <= 1e-4);
}
void testOpenGrid(void)
{	
	YGPoint org =  YGDegreePoint(2.424971108, 48.844445839,0);
    
    YGTransform tr = __YGTransformRGF93ToNTF(org);
    
    YGPoint t = {tr.tx,tr.ty,tr.tz};
    YGPoint null= {0,0,0,RADIAN};
    
    org = YGPointToRadian(org);
    org =  __YGGeographicToCartesian(org.x,org.y,org.z,A_WGS84,E_WGS84);
    
    org =  __YGSwitchGeodesicSystem(org, t, 0, null);
    org = __YGCartesianToGeographic(org, LON_MERID_PARIS, A_CLARK_IGN, E_CLARK_IGN, DEFAULT_EPS);
    
    org = YGPointToDegree(org);
    
    printf("Point value :\n");
}

void test_RGF93_NTF_degree(void)
{
    YGPoint org =  YGDegreePoint(2.424971108, 48.844445839,0);
    YGPoint expected = YGDegreePoint(2.42567186, 48.84451225, 0);
    
    
    YGPoint dest = YGPointConvertRGF93_NTF(org);
    CU_ASSERT(fabs(expected.x - dest.x) <= 1e-8);
    CU_ASSERT(fabs(expected.y - dest.y) <= 1e-8);
}

void test_RGF93_NTF_degree_to_cartesian(void)
{
    YGPoint org =  YGDegreePoint(2.424971108, 48.844445839,0);
    YGPoint expected = YGDegreePoint(606491.571, 127112.233, 0);
    
    
    YGPoint dest = YGPointConvertRGF93_NTF(org);
    dest = YGPointToRadian(dest);
    

    
    CU_ASSERT(fabs(expected.x - dest.x) <= 1e-3);
    CU_ASSERT(fabs(expected.y - dest.y) <= 1e-3);
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

   /* add the tests to the suite testProjectionsecant*/
   if ( NULL == CU_add_test(pSuite, "Test Algo0002", test_algo0002) ||
        NULL == CU_add_test(pSuite, "Test Algo0012", test_algo0012) ||
        NULL == CU_add_test(pSuite,"Test Algo004",test_algo004)     ||
        NULL == CU_add_test(pSuite,"Test algo0021",test_algo0021)   ||
        NULL == CU_add_test(pSuite,"test_algo009",test_algo009)     ||
       NULL == CU_add_test(pSuite,"Test Zenith Strasbourg",testZenithStrasbourg)             ||
        NULL == CU_add_test(pSuite,"Test Bug Lambert 93",testBugLambert93)             ||
       NULL == CU_add_test(pSuite,"Test Bug Lambert II E",testBugLambertIIE)             ||
        NULL == CU_add_test(pSuite,"testNTFRGF93",testOpenGrid)     ||
        NULL == CU_add_test(pSuite, "Test  (Degree)RGF93 ->NTF (Degree)", test_RGF93_NTF_degree) ||
        NULL == CU_add_test(pSuite, "Test  (Degree)RGF93 ->NTF (Meter)", test_RGF93_NTF_degree_to_cartesian)
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
