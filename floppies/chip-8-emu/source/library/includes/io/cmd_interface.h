#ifndef CMD_INTERFACE_H
#define CMD_INTERFACE_H

typedef enum {
    INFO,
    WARN,
    ERROR
} LogLevel;

void print_help();
void log_message(LogLevel level, const char * message, ...);

#endif