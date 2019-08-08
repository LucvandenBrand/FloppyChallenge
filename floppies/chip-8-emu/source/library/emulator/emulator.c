#include <binary_blob.h>
#include <cmd_interface.h>
#include <emulator/emulator.h>
#include <stdlib.h>

void emulate_rom(const BinaryBlob * rom)
{
    System system = init_system(rom);
    while (system.is_running)
    {
        step_system_cpu(&system);
        //render_system_video_memory(system.video_memory);
        //update_system_key_states(system.key_states);
    }
}

void step_system_cpu(System * system)
{
    if (system->program_counter + 1 >= MAIN_MEMORY_SIZE)
    {
        log_message(ERROR, "Program counter exceeds main memory.");
        exit(EXIT_FAILURE);
    }

    uint16_t op_code = system->main_memory[system->program_counter] |
                       system->main_memory[system->program_counter + 1];

    process_op_code(system, op_code);
    step_timers(system);
}

void process_op_code(System * system, uint16_t op_code)
{
    switch (op_code & 0xF000)
    {
        case 0xA000: // ANNN: Sets index register to address NNN.
            system->index_register = op_code & 0x0FFF;
            system->program_counter += 2;
            break;
        default:
            log_message(ERROR, "Unknown op code: 0x%X.", op_code);
            exit(EXIT_FAILURE);
    }
}

void step_timers(System * system)
{
    if (system->delay_timer > 0)
        --system->delay_timer;
    if (system->sound_timer <= 0)
        return;

    if (system->sound_timer == 1)
        system->audio_triggered = true;
    --system->sound_timer;
}