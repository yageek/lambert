#include<stdio.h>
#include<check.h>
#include "../lib/lambert.h"

START_TEST (test_lambert)
{

Point org = {1029705.083,272723.849};
Point dest = {0,0};
LambertZone zone = LAMBERT_I;

lambert_to_wgs84(&org, zone, &dest);
ck_assert_msg(dest.x == 0.145512099,"Failed: Expect 0.145512099 E- Found:%d",dest.x);
ck_assert_msg(dest.y == 0.872664626,"Failed: Expect 0.872664626 N - Found:%d",dest.y);

}

END_TEST

Suite* str_suite (void) {
        Suite *suite = suite_create("test_lambert");
        TCase *tcase = tcase_create("Basic");
        tcase_add_test(tcase, test_lambert);
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
