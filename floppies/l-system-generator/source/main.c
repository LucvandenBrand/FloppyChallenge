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

bool handle_job(Job job) {
    LSystem system = alloc_empty_system();
    if (!try_load_job(job, &system)) {
        free_system(&system);
        return false;
    }

    generate_system(&system, job.num_iterations);

    if (!try_save_job(job, system))
    {
        free_system(&system);
        return false;
    }

    free_system(&system);
    return true;
}

bool try_load_job(Job job, LSystem * system)
{
    long input_size = get_file_size(job.input_path);
    if (input_size < 1)
    {
        printf("Could not read input file.\n");
        return false;
    }
    char * input_buffer = safe_malloc(sizeof(char) * input_size);
    try_load_file(job.input_path, input_buffer, input_size);
    bool load_success = try_load_system_from_json_string(system, input_buffer);
    free(input_buffer);
    if (!load_success)
    {
        printf("Invalid input file.\n");
        return false;
    }
    return true;
}

bool try_save_job(Job job, LSystem system)
{
    printf("Writing to output...\n");

    if (job.save_symbols)
    {
        if (!try_write_file(job.output_path, system.axiom.symbols, system.axiom.length))
        {
            printf("Could not write to output file.\n");
            return false;
        }
    }
    else {
        // TODO: Render the system.
    }

    printf("Success!\n");
    return true;
}