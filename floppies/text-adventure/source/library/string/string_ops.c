#include <ctype.h>

void string_to_lowercase(char * upper_case_string, unsigned length)
{
    for (unsigned index = 0; index < length; index++)
    {
        upper_case_string[index] = (char) tolower(upper_case_string[index]);
    }
}