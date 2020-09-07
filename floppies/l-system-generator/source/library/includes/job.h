#ifndef JOB_H
#define JOB_H

#include "stdbool.h"

typedef struct {
   const char * input_path;
   const char * output_path;
   long num_iterations;
   bool save_symbols;
} Job;

Job parse_args_to_job(int argc, char ** argv);
void print_usage();
bool string_starts_with(const char * string, const char * check_string);
void validate_job(Job job);

#endif
