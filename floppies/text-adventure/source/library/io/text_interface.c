#include <io/text_interface.h>
#include <stdio.h>
#include <stdarg.h>

void clear_screen()
{
    printf("\e[1;1H\e[2J");
}

void put_text(const char * text, ...)
{
    va_list args;
    va_start (args, text);
    put_color_text(BLACK, text, args);
    va_end (args);
}

void put_color_text(Color color, const char * text, ...)
{
    va_list args;
    va_start (args, text);
    vprintf(text, args);
    va_end (args);
}

void get_text(char * buffer)
{
    scanf("%99[^\n]", buffer);
    getchar();
}