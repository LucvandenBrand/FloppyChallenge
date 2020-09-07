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
    // Load the L-system into memory
    long input_size = get_file_size(job.input_path);
    if (input_size < 1)
    {
        printf("Could not read input file.\n");
        return EXIT_FAILURE;
    }
    char * input_buffer = safe_malloc(sizeof(char) * input_size);
    load_file(job.input_path, input_buffer, input_size);

    LSystem system = alloc_empty_system();
    bool load_success = try_load_system_from_json_string(&system, input_buffer);
    free(input_buffer);
    if (!load_success)
    {
        printf("Invalid input file.\n");
        free_system(&system);
        return EXIT_FAILURE;
    }

    // Load successful, start generating the system.
    generate_system(&system, job.num_iterations);
    free_system(&system);

    // TODO: Render the system.

    return EXIT_SUCCESS;
}
