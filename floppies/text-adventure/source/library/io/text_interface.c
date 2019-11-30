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
    vprintf(text, args);
    va_end (args);
}

void put_color_text(Color color, const char * text, ...)
{
    set_text_color(color);
    va_list args;
    va_start (args, text);
    vprintf(text, args);
    va_end (args);
    set_text_color(NORMAL);
}

void set_text_color(Color color)
{
    switch (color)
    {
        case RED:
            printf("\x1B[31m");
            break;
        case GREEN:
            printf("\x1B[32m");
            break;
        case BLUE:
            printf("\x1B[34m");
            break;
        case WHITE:
            printf("\x1B[36m");
            break;
        default:
            printf("\x1B[0m");
            break;
    }
}

void get_text(char * buffer)
{
    scanf("%99[^\n]", buffer);
    getchar();
}