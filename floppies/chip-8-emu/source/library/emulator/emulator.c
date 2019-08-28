#include <io/binary_blob.h>
#include <io/cmd_interface.h>
#include <emulator/emulator.h>
#include <stdlib.h>
#include <rendering/render_context.h>
#include <rendering/frame_buffer.h>

void emulate_rom(const BinaryBlob * rom)
{
    RenderContext render_context = create_render_context("CHIP-8-emu", VIDEO_WIDTH, VIDEO_HEIGHT);
    FrameBuffer frame_buffer = create_frame_buffer(render_context, VIDEO_WIDTH, VIDEO_HEIGHT);
    System system = init_system(rom);
    while (system.is_running)
    {
        step_system_cpu(&system);
        if (system.video_changed)
        {
            copy_system_video_memory(system, frame_buffer);
            present_frame_buffer(render_context, frame_buffer);
        }
        //update_system_key_states(system);
    }
    free_frame_buffer(&frame_buffer);
    free_render_context(&render_context);
}

void step_system_cpu(System * system)
{
    if (system->program_counter + 1 >= MAIN_MEMORY_SIZE)
    {
        log_message(ERROR, "Program counter exceeds main memory.");
        exit(EXIT_FAILURE);
    }

    uint16_t op_code = system->main_memory[system->program_counter] << 8 |
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
        case 0x2000: // 2NNN: Call the subroutine at address NNN.
            system->stack[system->stack_pointer] = system->program_counter;
            system->stack_pointer++;
            system->program_counter = op_code & 0x0FFF;
            break;
        case 0xB000: // BNNN: Jump to location NNN + V0.
            system->program_counter = op_code & 0x0FFF + system->v_registers[0];
            break;
        default:
            log_message(ERROR, "Unknown op code: 0x%04X.", op_code);
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

void copy_system_video_memory(System system, FrameBuffer frame_buffer)
{
    for (int hor_index = 0; hor_index < VIDEO_WIDTH; hor_index++)
    {
        for (int ver_index = 0; ver_index < VIDEO_HEIGHT; ver_index++)
        {
            uint8_t pixel = system.video_memory[ver_index * VIDEO_WIDTH + hor_index];
            frame_buffer.pixels[ver_index * frame_buffer.frame_width + hor_index] = (uint32_t) pixel;
        }
    }
}