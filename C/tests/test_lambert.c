#include <stdio.h>
#include <check.h>
#include <math.h>
#include "../lib/lambert.h"

START_TEST (test_lambert)
{

	Point org = {1029705.083,272723.849};
	Point dest = {0,0};
	LambertZone zone = LAMBERT_I;

	lambert_to_wgs84(&org, &dest, zone);
	ck_assert_msg(dest.x == 0.145512099,"Failed: Expect 0.145512099 E- Found:%d",dest.x);
	ck_assert_msg(dest.y == 0.872664626,"Failed: Expect 0.872664626 N - Found:%d",dest.y);

}

END_TEST

START_TEST (test_algo0002)
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
			ck_assert_msg(diff <= ign_eps,"Expected: %.15f - Compute: %.15f - Diff:%.15f",phi[index], result,diff);
		}
}

END_TEST

Suite* str_suite (void) {
        Suite *suite = suite_create("test_lambert");
        TCase *tcase = tcase_create("Basic");
        tcase_add_test(tcase, test_lambert);
        tcase_add_test(tcase, test_algo0002);
        suite_add_tcase(suite, tcase);
        return suite;
}

int main(int argc, char **argv){

		int number_failed;
        Suite *suite = str_suite();
        SRunner *runner = srunner_create(suite);
        srunner_run_all(runner, CK_NORMAL);
        number_failed = srunner_ntests_failed(runner);
        srunner_free(runner);
        return number_failed;

}
