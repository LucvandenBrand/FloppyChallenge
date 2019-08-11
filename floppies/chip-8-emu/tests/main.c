#include <check.h>
#include <stdlib.h>

#define NUM_SUITES 6

Suite * make_file_system_suite();
Suite * make_binary_blob_suite();
Suite * make_system_suite();
Suite * make_emulator_suite();
Suite * make_render_context_suite();
Suite * make_frame_buffer_suite();

SRunner * create_suite_runner(Suite** suites, int numSuites)
{
    if (numSuites < 1)
        return NULL;
    SRunner *suiteRunner = srunner_create(suites[0]);
    for (int index = 1; index < numSuites; ++index)
        srunner_add_suite(suiteRunner, suites[index]);

    srunner_set_fork_status(suiteRunner, CK_NOFORK);
    srunner_set_log(suiteRunner, "test.log");
    srunner_set_xml(suiteRunner, "test.xml");

    return suiteRunner;
}

int main()
{
    Suite * suites[NUM_SUITES] = {
            make_file_system_suite(),
            make_binary_blob_suite(),
            make_system_suite(),
            make_emulator_suite(),
            make_render_context_suite(),
            make_frame_buffer_suite()
    };

    SRunner * suiteRunner = create_suite_runner(suites, NUM_SUITES);
    srunner_run_all(suiteRunner, CK_VERBOSE);

    int numberFailed = srunner_ntests_failed(suiteRunner);
    srunner_free(suiteRunner);
    return (numberFailed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}