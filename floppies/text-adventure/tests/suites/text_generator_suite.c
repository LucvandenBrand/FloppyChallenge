#include <check.h>
#include <game/text_generator.h>

START_TEST(test_is_char_in_array)
{
    const char * alphabet = "abcdefghijklmnopqrstuvwxyz";
    const char * exceptions = "1234567890<>,.;:'-_=+|`~!@";
    for (int i=0; i<26; i++)
    {
        ck_assert(is_char_in_array(alphabet[i], alphabet));
        ck_assert(!is_char_in_array(exceptions[i], alphabet));
    }
}
END_TEST

Suite * makeTextGeneratorSuite()
{
    Suite *suite = suite_create("Text Generator Test Suite");

    TCase * test_case = tcase_create("Text Generator");
    tcase_add_test(test_case, test_is_char_in_array);
    suite_add_tcase(suite, test_case);

    return suite;
}