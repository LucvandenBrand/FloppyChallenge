#include <io/binary_blob.h>
#include <io/cmd_interface.h>
#include <emulator/emulator.h>
#include <stdlib.h>
#include <rendering/render_context.h>
#include <rendering/frame_buffer.h>

void emulate_rom(const BinaryBlob * rom)
{
    RenderContext render_context = create_render_context("CHIP-8-emu",
            VIDEO_WIDTH*VIDEO_SCALE, VIDEO_HEIGHT * VIDEO_SCALE);
    FrameBuffer frame_buffer = create_frame_buffer(render_context, VIDEO_WIDTH, VIDEO_HEIGHT);
    System system = init_system(rom);
    uint64_t time_last = 0;
    uint64_t time_now = SDL_GetPerformanceCounter();
    while (system.is_running)
    {
        step_system_cpu(&system);
        if (system.video_changed)
        {
            copy_system_video_memory(system, frame_buffer);
            present_frame_buffer(render_context, frame_buffer);
        }
        update_system_key_states(&system);

        time_last = time_now;
        time_now = SDL_GetPerformanceCounter();
        double delta_time = (double)((time_now - time_last)*1000 / (double)SDL_GetPerformanceFrequency());
        double wait_time = 100.0/6.0 - delta_time;
        if (wait_time > 0)
            SDL_Delay(wait_time);
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
    unsigned int index_x, index_y, value_x, value_y, value;
    switch (op_code & 0xF000)
    {
        case 0x0000:
            switch (op_code)
            {
                case 0x00EE: // Return from a subroutine, restore from stack.
                    system->program_counter = system->stack[system->stack_pointer - 1] + 2;
                    system->stack_pointer--;
                    break;
                case 0x00E0: // Clear video memory.
                    memset(system->video_memory, 0, sizeof(system->video_memory));
                    system->video_changed = true;
                    system->program_counter += 2;
                    break;
                default:
                    log_message(ERROR, "Unknown op code: 0x%04X.", op_code);
                    exit(EXIT_FAILURE);
            }
            break;
        case 0x1000: // 1NNN Jump to location NNN.
            system->program_counter = op_code & 0x0FFF;
            break;
        case 0x2000: // 2NNN: Call the subroutine at address NNN.
            system->stack[system->stack_pointer] = system->program_counter;
            system->stack_pointer++;
            system->program_counter = op_code & 0x0FFF;
            break;
        case 0x3000: // 3XKK: Skip instruction if V[X] == KK.
            index_x = (op_code & 0x0F00) >> 8;
            value = op_code & 0x00FF;
            if (system->v_registers[index_x] == value)
                system->program_counter += 2;
            system->program_counter += 2;
            break;
        case 0x4000: // 4XKK: Skip instruction if V[X] != KK.
            index_x = (op_code & 0x0F00) >> 8;
            value = op_code & 0x00FF;
            if (system->v_registers[index_x] != value)
                system->program_counter += 2;
            system->program_counter += 2;
            break;
        case 0x5000: // 5XY0: Skip instruction if V[X] == V[Y].
            index_x = (op_code & 0x0F00) >> 8;
            index_y = (op_code & 0x00F0) >> 4;
            if (system->v_registers[index_x] == system->v_registers[index_y])
                system->program_counter += 2;
            system->program_counter += 2;
            break;
        case 0x6000: // 6XKK: Put the value KK into register X.
            index_x = (op_code & 0x0F00) >> 8;
            system->v_registers[index_x] = op_code & 0x00FF;
            system->program_counter += 2;
            break;
        case 0x7000: // 7XKK: Add the value KK to register X.
            index_x = (op_code & 0x0F00) >> 8;
            system->v_registers[index_x] += op_code & 0x00FF;
            system->program_counter += 2;
            break;
        case 0x8000:
            switch (op_code & 0x000F)
            {
                case 0x0000: // 8XY0: Store V[Y] in V[X].
                    index_x = (op_code & 0x0F00) >> 8;
                    index_y = (op_code & 0x00F0) >> 4;
                    system->v_registers[index_x] = system->v_registers[index_y];
                    system->program_counter += 2;
                    break;
                case 0x0001: // 8XY1: Set V[X] to v[X] or'ed with V[Y}
                    index_x = (op_code & 0x0F00) >> 8;
                    index_y = (op_code & 0x00F0) >> 4;
                    system->v_registers[index_x] |= system->v_registers[index_y];
                    system->program_counter += 2;
                    break;
                case 0x0002: // 8XY2: Set V[X] to v[X] and'ed with V[Y}
                    index_x = (op_code & 0x0F00) >> 8;
                    index_y = (op_code & 0x00F0) >> 4;
                    system->v_registers[index_x] &= system->v_registers[index_y];
                    system->program_counter += 2;
                    break;
                case 0x0003: // 8XY3: Set V[X] to v[X] xor'ed with V[Y}
                    index_x = (op_code & 0x0F00) >> 8;
                    index_y = (op_code & 0x00F0) >> 4;
                    system->v_registers[index_x] ^= system->v_registers[index_y];
                    system->program_counter += 2;
                    break;
                case 0x0004: // 8XY4: Set V[X] to v[X] added to V[Y}
                    index_x = (op_code & 0x0F00) >> 8;
                    index_y = (op_code & 0x00F0) >> 4;
                    value_x = system->v_registers[index_x];
                    value_y = system->v_registers[index_y];
                    value = value_x + value_y;
                    system->v_registers[NUM_V_REGISTERS-1] = value > 255;
                    system->v_registers[index_x] = value & 0xFF;
                    system->program_counter += 2;
                    break;
                case 0x0005: // 8XY5: Set V[X] to V[Y] subtracted from V[X]
                    index_x = (op_code & 0x0F00) >> 8;
                    index_y = (op_code & 0x00F0) >> 4;
                    value_x = system->v_registers[index_x];
                    value_y = system->v_registers[index_y];
                    system->v_registers[NUM_V_REGISTERS-1] = value_x > value_y;
                    system->v_registers[index_x] = abs( value_x - value_y) & 0xFF;
                    system->program_counter += 2;
                    break;
                case 0x0006: // 8XY6: Shift V[X} right.
                    index_x = (op_code & 0x0F00) >> 8;
                    value_x = system->v_registers[index_x];
                    system->v_registers[NUM_V_REGISTERS-1] = value_x & 0x01;
                    system->v_registers[index_x] = value_x >> 1;
                    system->program_counter += 2;
                    break;
                case 0x0007: // 8XY7: Set V[X] to V[X] subtracted from V[Y}
                    index_x = (op_code & 0x0F00) >> 8;
                    index_y = (op_code & 0x00F0) >> 4;
                    value_x = system->v_registers[index_x];
                    value_y = system->v_registers[index_y];
                    system->v_registers[NUM_V_REGISTERS-1] = value_y > value_x;
                    system->v_registers[index_x] = abs(value_y - value_x) & 0xFF;
                    system->program_counter += 2;
                    break;
                case 0x000E: // 8XYE: Shift V[X} left.
                    index_x = (op_code & 0x0F00) >> 8;
                    value_x = system->v_registers[index_x];
                    system->v_registers[NUM_V_REGISTERS-1] = (value_x & 0x80) >> 7;
                    system->v_registers[index_x] = value_x << 1;
                    system->program_counter += 2;
                    break;
                default:
                    log_message(ERROR, "Unknown op code: 0x%04X.", op_code);
                    exit(EXIT_FAILURE);
            }
            break;
        case 0x9000: // 9XY0: Skip instruction if V[X] != V[Y].
            index_x = (op_code & 0x0F00) >> 8;
            index_y = (op_code & 0x00F0) >> 4;
            if (system->v_registers[index_x] != system->v_registers[index_y])
                system->program_counter += 2;
            system->program_counter += 2;
            break;
        case 0xA000: // ANNN: Sets index register to address NNN.
            system->index_register = op_code & 0x0FFF;
            system->program_counter += 2;
            break;
        case 0xB000: // BNNN: Jump to location NNN + V0.
            system->program_counter = (op_code & 0x0FFF) + system->v_registers[0];
            break;
        case 0xC000: // CXKK: Set V[X] to a random byte and'ed with KK.
            value = op_code & 0x00FF;
            index_x = (op_code & 0x0F00) >> 8;
            system->v_registers[index_x] = rand() & value;
            system->program_counter += 2;
            break;
        case 0xD000: // DXYN: Draw N-byte sprite starting at location I at (V[X], V[Y]), set VF to collision.
            index_x = (op_code & 0x0F00) >> 8;
            index_y = (op_code & 0x00F0) >> 4;
            value_x = system->v_registers[index_x];
            value_y = system->v_registers[index_y];
            value = op_code & 0x000F;
            uint8_t * sprite = &system->main_memory[system->index_register];
            system->v_registers[NUM_V_REGISTERS - 1] = 0;
            for (unsigned int byte_num = 0; byte_num < value; byte_num++)
            {
                uint8_t byte = sprite[byte_num];
                for (unsigned int bit_num = 0; bit_num < 8; bit_num++)
                {
                    uint8_t bit = (byte & 0x80) >> 7;
                    byte = byte << 1;
                    unsigned int video_index = (value_y + byte_num) * VIDEO_WIDTH + value_x + bit_num;
                    uint8_t video_bit = system->video_memory[video_index];
                    if (bit && video_bit)
                        system->v_registers[NUM_V_REGISTERS - 1] = 0x1;
                    system->video_memory[video_index] = bit^video_bit;
                }
            }
            system->video_changed = true;
            system->program_counter += 2;
            break;
        case 0xE000:
            switch (op_code & 0x00FF)
            {
                case 0x009E: // EX9E: Skip instruction if key V[X] is pressed.
                    index_x = (op_code & 0x0F00) >> 8;
                    value_x = system->v_registers[index_x];
                    if (system->key_states[value_x])
                        system->program_counter += 2;
                    system->program_counter += 2;
                    break;
                case 0x00A1: // EX9E: Skip instruction if key V[X] is pressed.
                    index_x = (op_code & 0x0F00) >> 8;
                    value_x = system->v_registers[index_x];
                    if (!system->key_states[value_x])
                        system->program_counter += 2;
                    system->program_counter += 2;
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
                    index_x = (op_code & 0x0F00) >> 8;
                    system->v_registers[index_x] = system->delay_timer;
                    system->program_counter += 2;
                    break;
                case 0x000A: // FX0A: Wait for a key to be pressed, then put that key in V[X].
                    index_x = (op_code & 0x0F00) >> 8;
                    for (uint8_t key=0; key < NUM_KEYS; key++)
                    {
                        if (system->key_states[key])
                        {
                            system->v_registers[index_x] = key;
                            system->program_counter += 2;
                            break;
                        }
                    }
                    break;
                case 0x0015: // FX15: Set the delay timer to V[X].
                    index_x = (op_code & 0x0F00) >> 8;
                    system->delay_timer = system->v_registers[index_x];
                    system->program_counter += 2;
                    break;
                case 0x0018: // FX18: Set the sound timer to V[X].
                    index_x = (op_code & 0x0F00) >> 8;
                    system->sound_timer = system->v_registers[index_x];
                    system->program_counter += 2;
                    break;
                case 0x001E: // FX1E: Add the value of V[X] to the index register.
                    index_x = (op_code & 0x0F00) >> 8;
                    system->index_register += system->v_registers[index_x];
                    system->program_counter += 2;
                    break;
                case 0x0029: // FX29: Set the index location to the sprite for digit V[X].
                    index_x = (op_code & 0x0F00) >> 8;
                    value_x = system->v_registers[index_x];
                    system->index_register = value_x * 0x05;
                    system->program_counter += 2;
                    break;
                case 0x0033: // FX33: Store the BCD representation of V[X] to the memory starting at the index register.
                    index_x = (op_code & 0x0F00) >> 8;
                    value_x = system->v_registers[index_x];
                    uint8_t hundreds = (value_x/100) % 10;
                    system->main_memory[system->index_register] = hundreds;
                    uint8_t tens = (value_x/10) % 10;
                    system->main_memory[system->index_register+1] = tens;
                    uint8_t ones = value_x % 10;
                    system->main_memory[system->index_register+2] = ones;
                    system->program_counter += 2;
                    break;
                case 0x0055: // FX55: Store the registers in memory starting at the index register.
                    for (uint8_t reg_index = 0; reg_index < NUM_V_REGISTERS; reg_index++)
                    {
                        system->main_memory[system->index_register + reg_index] = system->v_registers[reg_index];
                    }
                    system->program_counter += 2;
                    break;
                case 0x0065: // FX65: Load the registers from memory starting at the index register.
                    for (uint8_t reg_index = 0; reg_index < NUM_V_REGISTERS; reg_index++)
                    {
                        system->v_registers[reg_index] = system->main_memory[system->index_register + reg_index];
                    }
                    system->program_counter += 2;
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
        --system->delay_timer;
    if (system->sound_timer <= 0)
        return;

    if (system->sound_timer == 1)
        system->audio_triggered = true;
    --system->sound_timer;
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

void copy_system_video_memory(System system, FrameBuffer frame_buffer)
{
    if (!lock_frame_buffer(frame_buffer))
        log_message(WARN, "Could not lock frame buffer.");

    for (int hor_index = 0; hor_index < VIDEO_WIDTH; hor_index++)
    {
        for (int ver_index = 0; ver_index < VIDEO_HEIGHT; ver_index++)
        {
            uint8_t pixel = system.video_memory[ver_index * VIDEO_WIDTH + hor_index];
            frame_buffer.pixels[ver_index * frame_buffer.frame_width + hor_index] = (uint32_t) pixel * 0xFFFFFF;
        }
    }
    unlock_frame_buffer(frame_buffer);
}