#include <stdio.h>
#include <stdarg.h>
#include <io/cmd_interface.h>

void print_help()
{
    printf(" ----------------------------------------------------------------- \n");
    printf("| chip-8-emu : a tiny CHIP-8 emulator by Luc van den Brand.       |\n");
    printf("| Created as part of a challenge: https://www.floppychallenge.com |\n");
    printf(" ----------------------------------------------------------------- \n");
    printf("-> Usage: chip-8-emu path/to/rom/file\n");
}

void log_message(LogLevel level, const char * message, ...)
{
    switch (level)
    {
        case WARN:
            printf("WARN - ");
            break;
        case ERROR:
            printf("ERROR - ");
            break;
        default:
            printf("INFO - ");
            break;
    }

    va_list args;
    va_start (args, message);
    vprintf (message, args);
    va_end (args);
    putchar('\n');
}