#include <CUnit/Basic.h>
#include <CUnit/Console.h>
#include <CUnit/Automated.h>
#include <math.h>
#include "../lib/lambert.h"

int init_suite_success(void) { return 0; }
int init_suite_failure(void) { return -1; }
int clean_suite_success(void) { return 0; }
int clean_suite_failure(void) { return -1; }

void test_lambert(void)
{

	Point org = {1029705.083,272723.849};
	Point dest = {0,0};
	LambertZone zone = LAMBERT_I;

	lambert_to_wgs84(&org, &dest, zone);
	// ck_assert_msg(dest.x == 0.145512099,"Failed: Expect 0.145512099 E- Found:%d",dest.x);
	// ck_assert_msg(dest.y == 0.872664626,"Failed: Expect 0.872664626 N - Found:%d",dest.y);

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

	double ign_eps = 1e-10;
	unsigned int index;

		for(index = 0;index < 3;index++)
		{
			double result = lat_from_lat_iso(lat_iso[index], e[index], eps[index]);
			double diff = abs(result - phi[index]);
			// ck_assert_msg(diff <= ign_eps,"Expected: %.15f - Compute: %.15f - Diff:%.15f",phi[index], result,diff);
			CU_ASSERT(diff <= ign_eps);
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
	double ign_eps = 1e-10;
	for(i=0; i < 3;++i)
	{
		Point sample = {x[i],y[i],z[i]};
		Point val ;
		val = cartesian_to_geographic(sample,a[i],e[i],eps[i]);
		// ck_assert_msg(abs(val.x - lon[i]) < ign_eps,"Lon Error - Expected:%.10f - Computed:%.10f",val.x,lon[i]);
		// ck_assert_msg(abs(val.y - lat[i]) < ign_eps,"Lat Error - Expected:%.10f - Computed:%.10f",val.y,lat[i]);
		// ck_assert_msg(abs(val.z - he[i]) < ign_eps,"He Error - Expected:%.10f - Computed:%.10f",val.z,he[i]);
		CU_ASSERT(abs(val.x - lon[i]) < ign_eps);	
	}


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
   if (NULL == CU_add_test(pSuite, "successful_test_1", test_algo0002))
       // (NULL == CU_add_test(pSuite, "successful_test_2", test_success2)) ||
       // (NULL == CU_add_test(pSuite, "successful_test_3", test_success3)))
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
