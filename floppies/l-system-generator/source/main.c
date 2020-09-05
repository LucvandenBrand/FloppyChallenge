#include <stdio.h>
#include <stdlib.h>
#include "generator.h"
#include "memory/safe_alloc.h"
#include "main.h"
#include "io/files.h"
#include "system.h"
#define JSMN_HEADER
#include "loader.h"

int main(int argc, char ** argv)
{
    Job job = parse_args_to_job(argc, argv);
    return handle_job(job);
}

int handle_job(Job job)
{
    long input_size = get_file_size(job.input_path);
    if (input_size < 1)
    {
        printf("Could not read input file.\n");
        return EXIT_FAILURE;
    }
    char * input_buffer = safe_malloc(sizeof(char) * input_size);
    load_file(job.input_path, input_buffer, input_size);

    LSystem system;
    if (!try_load_system_from_json_string(&system, input_buffer))
    {
        printf("Invalid input file.\n");
        return EXIT_FAILURE;
    }

    generate_system(&system, job.num_iterations);

    free(input_buffer);
    return EXIT_SUCCESS;
}
