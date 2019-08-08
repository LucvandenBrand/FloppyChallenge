#include <emulator/system.h>
#include <string.h>
#include <emulator/font.h>

System init_system(const BinaryBlob *  rom)
{
    System system;
    system.is_running = true;
    system.video_changed = true;
    system.audio_triggered = false;
    system.program_counter = ADDRESS_ROM;
    system.index_register = 0;
    system.stack_pointer = 0;
    system.delay_timer = 0;
    system.sound_timer = 0;

    memset(system.main_memory, 0, sizeof(system.main_memory));
    memset(system.video_memory, 0, sizeof(system.video_memory));
    memset(system.stack, 0, sizeof(system.stack));
    memset(system.v_registers, 0, sizeof(system.v_registers));
    memset(system.key_states, 0, sizeof(system.key_states));

    memcpy(system.main_memory, chip8_font, sizeof(chip8_font));
    memcpy(&(system.main_memory[ADDRESS_ROM]), rom->data, rom->num_bytes);

    return system;
}