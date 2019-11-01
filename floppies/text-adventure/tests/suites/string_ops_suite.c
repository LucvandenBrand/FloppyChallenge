#include <check.h>
#include <string/string_ops.h>
#include <stdlib.h>
#include <ctype.h>

START_TEST(test_create_lower_text)
{
    const char * text = "HaLLo! Hoe gaat het Maat?!";
    unsigned long num_chars = strlen(text);
    char * lower_text = malloc((num_chars+1) * sizeof(char));
    strncpy(lower_text, text, num_chars+1);
    string_to_lowercase(lower_text, num_chars);
    for (unsigned long index = 0; index < num_chars; index++)
    {
        ck_assert_int_eq(lower_text[index], tolower(text[index]));
    }
    free(lower_text);
}
END_TEST

Suite * makeStringOpsSuite()
{
    Suite *suite = suite_create("StringOps Test Suite");

    TCase * test_case = tcase_create("StringOps");
    tcase_add_test(test_case, test_create_lower_text);
    suite_add_tcase(suite, test_case);

    return suite;
}