#include <check.h>
#include <stdlib.h>

#define NUM_SUITES 2

Suite * make_rule_suite();
Suite * make_symbol_suite();

SRunner * create_suite_runner(Suite** suites, int num_suites)
{
    if (num_suites < 1)
        return NULL;
    SRunner *suite_runner = srunner_create(suites[0]);
    for (int index = 1; index < num_suites; ++index)
        srunner_add_suite(suite_runner, suites[index]);

    srunner_set_fork_status(suite_runner, CK_NOFORK);
    srunner_set_log(suite_runner, "test.log");
    srunner_set_xml(suite_runner, "test.xml");

    return suite_runner;
}

int main()
{
    Suite * suites[NUM_SUITES] = {
            make_rule_suite(),
            make_symbol_suite()
    };

    SRunner * suite_runner = create_suite_runner(suites, NUM_SUITES);
    srunner_run_all(suite_runner, CK_VERBOSE);

    int number_failed = srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}