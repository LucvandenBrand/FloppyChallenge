#include <binary_blob.h>
#include <cmd_interface.h>
#include <emulator/system.h>

void emulate_rom(const BinaryBlob * rom)
{
    System system = init_system(rom);
}