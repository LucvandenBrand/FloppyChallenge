#include <check.h>
#include <stdlib.h>

#define NUM_SUITES 9

Suite * makeItemSuite();
Suite * makeRoomSuite();
Suite * makePlayerSuite();
Suite * makeTextGeneratorSuite();
Suite * makeParserSuite();
Suite * makeTokenSuite();
Suite * makeMemorySuite();
Suite * makeStringOpsSuite();
Suite * makeDoorSuite();

SRunner * createSuiteRunner(Suite** suites, int numSuites)
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
            makeItemSuite(),
            makeRoomSuite(),
            makePlayerSuite(),
            makeTextGeneratorSuite(),
            makeParserSuite(),
            makeTokenSuite(),
            makeMemorySuite(),
            makeStringOpsSuite(),
            makeDoorSuite()
    };

    SRunner * suiteRunner = createSuiteRunner(suites, NUM_SUITES);
    srunner_run_all(suiteRunner, CK_VERBOSE);

    int numberFailed = srunner_ntests_failed(suiteRunner);
    srunner_free(suiteRunner);
    return (numberFailed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}