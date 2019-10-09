#include <io/binary_blob.h>
#include <io/cmd_interface.h>
#include <emulator/emulator.h>
#include <stdlib.h>
#include <rendering/render_context.h>
#include <rendering/frame_buffer.h>
#include <audio/mixer.h>
#include <emulator/opcodes.h>

void emulate_rom(const BinaryBlob * rom)
{
    RenderContext render_context = create_render_context("CHIP-8-emu",
            VIDEO_WIDTH*VIDEO_SCALE, VIDEO_HEIGHT * VIDEO_SCALE);
    FrameBuffer frame_buffer = create_frame_buffer(render_context, VIDEO_WIDTH, VIDEO_HEIGHT);
    if (init_mixer())
    {
        log_message(ERROR, "Could not init audio mixer.");
        exit(EXIT_FAILURE);
    }
    Audio beep_audio = load_audio(BEEP_PATH);
    if (beep_audio.mix_chunk == NULL)
    {
        log_message(ERROR, "Could not load beep audio!");
        exit(EXIT_FAILURE);
    }

    System system = init_system(rom);
    while (system.is_running)
    {
        uint32_t start_time = SDL_GetTicks();
        for (int step = 0; step < 10; step++)
            step_system_cpu(&system);
        step_timers(&system);
        update_system_key_states(&system);
        if (system.video_changed)
        {
            copy_system_video_memory(system, &frame_buffer);
            present_frame_buffer(render_context, frame_buffer);
        }
        if (system.audio_triggered)
            play_audio(beep_audio);

        uint32_t frame_ticks = SDL_GetTicks() - start_time;
        if (frame_ticks < VIDEO_TICKS_PER_FRAME)
            SDL_Delay(VIDEO_TICKS_PER_FRAME - frame_ticks);
    }
    free_audio(beep_audio);
    close_mixer();
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
}

void process_op_code(System * system, uint16_t op_code)
{
    unsigned int index_x, index_y, value_x, value_y, value;
    switch (op_code & 0xF000)
    {
        case 0x0000:
            switch (op_code)
            {
                case 0x00EE: // Return from a subroutine, restore from stack.
                    exit_subroutine(system, op_code);
                    break;
                case 0x00E0: // Clear video memory.
                    clear_video_memory(system, op_code);
                    break;
                default:
                    log_message(ERROR, "Unknown op code: 0x%04X.", op_code);
                    exit(EXIT_FAILURE);
            }
            break;
        case 0x1000: // 1NNN Jump to location NNN.
            jump(system, op_code);
            break;
        case 0x2000: // 2NNN: Call the subroutine at address NNN.
            call_subroutine(system, op_code);
            break;
        case 0x3000: // 3XKK: Skip instruction if V[X] == KK.
            skip_if_equal_value(system, op_code);
            break;
        case 0x4000: // 4XKK: Skip instruction if V[X] != KK.
            skip_if_not_equal_value(system, op_code);
            break;
        case 0x5000: // 5XY0: Skip instruction if V[X] == V[Y].
            skip_if_equal_registers(system, op_code);
            break;
        case 0x6000: // 6XKK: Put the value KK into register X.
            store_value_in_register(system, op_code);
            break;
        case 0x7000: // 7XKK: Add the value KK to register X.
            add_value_to_register(system, op_code);
            break;
        case 0x8000:
            switch (op_code & 0x000F)
            {
                case 0x0000: // 8XY0: Store V[Y] in V[X].
                    store_register_in_register(system, op_code);
                    break;
                case 0x0001: // 8XY1: Set V[X] to v[X] or'ed with V[Y]
                    logical_or_registers(system, op_code);
                    break;
                case 0x0002: // 8XY2: Set V[X] to v[X] and'ed with V[Y]
                    logical_and_registers(system, op_code);
                    break;
                case 0x0003: // 8XY3: Set V[X] to v[X] xor'ed with V[Y]
                    logical_xor_registers(system, op_code);
                    break;
                case 0x0004: // 8XY4: Set V[X] to V[X] added to V[Y]
                    add_register_to_register(system, op_code);
                    break;
                case 0x0005: // 8XY5: Set V[X] to V[Y] subtracted from V[X]
                    subtract_registers(system, op_code);
                    break;
                case 0x0006: // 8XY6: Shift V[X] right.
                    right_shift_register(system, op_code);
                    break;
                case 0x0007: // 8XY7: Set V[X] to V[X] subtracted from V[Y]
                    reverse_subtract_registers(system, op_code);
                    break;
                case 0x000E: // 8XYE: Shift V[X] left.
                    left_shift_register(system, op_code);
                    break;
                default:
                    log_message(ERROR, "Unknown op code: 0x%04X.", op_code);
                    exit(EXIT_FAILURE);
            }
            break;
        case 0x9000: // 9XY0: Skip instruction if V[X] != V[Y].
            skip_if_not_equal_registers(system, op_code);
            break;
        case 0xA000: // ANNN: Sets index register to address NNN.
            set_index(system, op_code);
            break;
        case 0xB000: // BNNN: Jump to location NNN + V0.
            jump_with_register_offset(system, op_code);
            break;
        case 0xC000: // CXKK: Set V[X] to a random byte and'ed with KK.
            set_register_to_random_value(system, op_code);
            break;
        case 0xD000: // DXYN: Draw N-byte sprite starting at location I at (V[X], V[Y]), set VF to collision.
            draw_sprite(system, op_code);
            break;
        case 0xE000:
            switch (op_code & 0x00FF)
            {
                case 0x009E: // EX9E: Skip instruction if key V[X] is pressed.
                    skip_if_key_pressed(system, op_code);
                    break;
                case 0x00A1: // EX9E: Skip instruction if key V[X] is not pressed.
                    skip_if_key_not_pressed(system, op_code);
                    break;
                default:
                    log_message(ERROR, "Unknown op code: 0x%04X.", op_code);
                    exit(EXIT_FAILURE);
            }
            break;
        case 0xF000:
            switch (op_code & 0x00FF)
            {
                case 0x0007: // FX07: Set V[X] to delay timer value.
                    set_register_to_delay_timer(system, op_code);
                    break;
                case 0x000A: // FX0A: Wait for a key to be pressed, then put that key in V[X].
                    wait_for_key_pressed(system, op_code);
                    break;
                case 0x0015: // FX15: Set the delay timer to V[X].
                    set_delay_timer_to_register(system, op_code);
                    break;
                case 0x0018: // FX18: Set the sound timer to V[X].
                    set_sound_timer_to_register(system, op_code);
                    break;
                case 0x001E: // FX1E: Add the value of V[X] to the index register.
                    add_register_to_index(system, op_code);
                    break;
                case 0x0029: // FX29: Set the index location to the sprite for digit V[X].
                    set_index_to_digit_sprite(system, op_code);
                    break;
                case 0x0033: // FX33: Store the BCD representation of V[X] to the memory starting at the index register.
                    store_register_as_bcd_at_index(system, op_code);
                    break;
                case 0x0055: // FX55: Store the registers in memory starting at the index register.
                    store_registers(system, op_code);
                    break;
                case 0x0065: // FX65: Load the registers from memory starting at the index register.
                    load_registers(system, op_code);
                    break;
                default:
                    log_message(ERROR, "Unknown op code: 0x%04X.", op_code);
                    exit(EXIT_FAILURE);
            }
            break;
        default:
            log_message(ERROR, "Unknown op code: 0x%04X.", op_code);
            exit(EXIT_FAILURE);
    }
}

void step_timers(System * system)
{
    if (system->delay_timer > 0)
        system->delay_timer -= 1;
    system->audio_triggered = system->sound_timer == 1;
    if (system->sound_timer <= 0)
        return;
    system->sound_timer -= 1;
}

void update_system_key_states(System * system)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
        process_event(event, system);
}

void process_event(SDL_Event event, System * system)
{
    switch(event.type)
    {
        case SDL_KEYDOWN:
            process_key_event(event.key, system);
            break;
        case SDL_KEYUP:
            process_key_event(event.key, system);
            break;
        case SDL_WINDOWEVENT:
            process_window_event(event.window, system);
            break;
        default:
            break;
    }
}

void process_key_event(SDL_KeyboardEvent key, System * system)
{
    int index = map_key_to_index(key.keysym.sym);
    if (index > 0)
        system->key_states[index] = key.type == SDL_KEYDOWN;
}

int map_key_to_index(SDL_Keycode key_code)
{
    switch (key_code)
    {
        case SDLK_0:
            return 0;
        case SDLK_1:
            return 1;
        case SDLK_2:
            return 2;
        case SDLK_3:
            return 3;
        case SDLK_4:
            return 4;
        case SDLK_5:
            return 5;
        case SDLK_6:
            return 6;
        case SDLK_7:
            return 7;
        case SDLK_8:
            return 8;
        case SDLK_9:
            return 9;
        case SDLK_q:
            return 10;
        case SDLK_w:
            return 11;
        case SDLK_e:
            return 12;
        case SDLK_r:
            return 13;
        case SDLK_t:
            return 14;
        case SDLK_y:
            return 15;
        default:
            return -1;
    }
}

void process_window_event(SDL_WindowEvent window, System * system)
{
    switch (window.event)
    {
        case SDL_WINDOWEVENT_CLOSE:
            system->is_running = false;
            break;
        default:
            break;
    }
}

void copy_system_video_memory(System system, FrameBuffer * frame_buffer)
{
    int failure = lock_frame_buffer(frame_buffer);
    if (failure) {
        log_message(WARN, "Could not lock frame buffer: %s.", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    uint32_t * pixels = frame_buffer->pixels;
    for (int hor_index = 0; hor_index < VIDEO_WIDTH; hor_index++)
    {
        for (int ver_index = 0; ver_index < VIDEO_HEIGHT; ver_index++)
        {
            uint8_t pixel = system.video_memory[ver_index * VIDEO_WIDTH + hor_index];
            pixels[ver_index * VIDEO_WIDTH + hor_index] = (uint32_t) pixel * VIDEO_COLOR;
        }
    }

    unlock_frame_buffer(frame_buffer);
}