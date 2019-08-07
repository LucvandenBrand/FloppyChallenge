#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <cmd_interface.h>
#include <file_system.h>
#include <emulator/emulator.h>

int main(int argc, char ** argv)
{
    if (argc < 2 || !strcmp(argv[1], "--help") || !strcmp(argv[1], "-h"))
    {
        print_help();
        return EXIT_SUCCESS;
    }

    char rom_file_path[PATH_MAX];
    get_full_path(argv[1], rom_file_path);
    if (!file_path_exists(rom_file_path))
    {
        log_message(ERROR, "The given path does not exist or is not a file.");
        return EXIT_FAILURE;
    }

    int num_rom_bytes = get_file_size(rom_file_path);
    if (num_rom_bytes < 0)
    {
        log_message(ERROR, "Could not read the file.");
        return EXIT_FAILURE;
    }
    log_message(INFO, "Successfully read %d bytes of ROM file %s into memory.", num_rom_bytes, argv[1]);

    BinaryBlob rom = malloc_binary_blob(num_rom_bytes);
    read_binary_file(rom_file_path, &rom);
    emulate_rom(&rom);
    free_binary_blob(&rom);

    log_message(INFO, "Closing down, goodbye!");
    return EXIT_SUCCESS;
}
