#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "job.h"

Job parse_args_to_job(int argc, char ** argv)
{
    Job job = { "", "", -1, 100, 100, false};
    for (size_t index = 0; index < argc; index++)
    {
        // Check if we have an option in the form of '--arg_name'
        char * argument = argv[index];
        if (!string_starts_with(argument, "--"))
            continue;
        argument += 2;

        // Check for value-less options.
        if (strcmp(argument, "help") == 0)
        {
            print_usage();
            exit(EXIT_SUCCESS);
        }
        else if (strcmp(argument, "symbols") == 0)
        {
            job.save_symbols = true;
            continue;
        }

        // Check if the option has an invalid next value.
        if (index+1 == argc || string_starts_with(argv[index+1], "--"))
        {
            printf("Please provide a value for option '%s'.\n", argument);
            continue;
        }

        // Check for options that make sense and assign values.
        if (strcmp(argument, "input") == 0)
        {
            job.input_path = argv[index+1];
        }
        else if (strcmp(argument, "output") == 0)
        {
            job.output_path = argv[index+1];
        }
        else if (strcmp(argument, "iterations") == 0)
        {
            char * end_ptr;
            long value = strtol(argv[index+1], &end_ptr, 10);
            job.num_iterations = value;
        }
        else if (strcmp(argument, "height") == 0)
        {
            char * end_ptr;
            long value = strtol(argv[index+1], &end_ptr, 10);
            job.height = value;
        }
        else if (strcmp(argument, "width") == 0)
        {
            char * end_ptr;
            long value = strtol(argv[index+1], &end_ptr, 10);
            job.width = value;
        }
        else
        {
            printf("Did not understand option '%s'.\n", argument);
            print_usage();
            exit(EXIT_FAILURE);
        }
    }

    validate_job(job);
    return job;
}

void print_usage()
{
    printf("Usage: lindengen --input <filename> --output <filename> --num_iterations <number> {--symbols}\n");
}

bool string_starts_with(const char * string, const char * check_string)
{
    size_t length_string = strlen(string);
    size_t length_check = strlen(check_string);
    if (length_string < length_check)
        return false;
    return memcmp(string, check_string, length_check) == 0;
}

void validate_job(Job job)
{
    if (strlen(job.input_path) == 0)
    {
        printf("No valid input path provided.\n");
        exit(EXIT_FAILURE);
    }
    if (strlen(job.output_path) == 0)
    {
        printf("No valid output path provided.\n");
        exit(EXIT_FAILURE);
    }
    if (job.height < 1)
    {
        printf("Height cannot be less than 1.\n");
        exit(EXIT_FAILURE);
    }
    if (job.width < 1)
    {
        printf("Width cannot be less than 1.\n");
        exit(EXIT_FAILURE);
    }
    if (job.num_iterations < 1)
    {
        printf("No valid number of iterations provided (must be above 0).\n");
        exit(EXIT_FAILURE);
    }
}