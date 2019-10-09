#include <emulator/opcodes.h>
#include <string.h>
#include <stdlib.h>

void call_subroutine(System * system, uint16_t op_code)
{
    system->stack[system->stack_pointer] = system->program_counter;
    system->stack_pointer++;
    system->program_counter = op_code & 0x0FFF;
}

void exit_subroutine(System * system, uint16_t op_code)
{
    system->stack_pointer--;
    system->program_counter = system->stack[system->stack_pointer];
    system->program_counter += 2;
}

void clear_video_memory(System * system, uint16_t op_code)
{
    memset(system->video_memory, 0, sizeof(system->video_memory));
    system->video_changed = true;
    system->program_counter += 2;
}

void jump(System * system, uint16_t op_code)
{
    system->program_counter = op_code & 0x0FFF;
}

void jump_with_register_offset(System * system, uint16_t op_code)
{
    system->program_counter = (op_code & 0x0FFF) + system->v_registers[0];
}

void skip_if_equal_value(System * system, uint16_t op_code)
{
    uint8_t index_x = (op_code & 0x0F00) >> 8;
    uint8_t value = op_code & 0x00FF;
    if (system->v_registers[index_x] == value)
        system->program_counter += 2;
    system->program_counter += 2;
}

void skip_if_not_equal_value(System * system, uint16_t op_code)
{
    uint8_t index_x = (op_code & 0x0F00) >> 8;
    uint8_t value = op_code & 0x00FF;
    if (system->v_registers[index_x] != value)
        system->program_counter += 2;
    system->program_counter += 2;
}

void skip_if_equal_registers(System * system, uint16_t op_code)
{
    uint8_t index_x = (op_code & 0x0F00) >> 8;
    uint8_t index_y = (op_code & 0x00F0) >> 4;
    if (system->v_registers[index_x] == system->v_registers[index_y])
        system->program_counter += 2;
    system->program_counter += 2;
}

void skip_if_not_equal_registers(System * system, uint16_t op_code)
{
    uint8_t index_x = (op_code & 0x0F00) >> 8;
    uint8_t index_y = (op_code & 0x00F0) >> 4;
    if (system->v_registers[index_x] != system->v_registers[index_y])
        system->program_counter += 2;
    system->program_counter += 2;
}

void store_value_in_register(System * system, uint16_t op_code)
{
    uint8_t index_x = (op_code & 0x0F00) >> 8;
    system->v_registers[index_x] = op_code & 0x00FF;
    system->program_counter += 2;
}

void add_value_to_register(System * system, uint16_t op_code)
{
    uint8_t index_x = (op_code & 0x0F00) >> 8;
    system->v_registers[index_x] += op_code & 0x00FF;
    system->program_counter += 2;
}

void store_register_in_register(System * system, uint16_t op_code)
{
    uint8_t index_x = (op_code & 0x0F00) >> 8;
    uint8_t index_y = (op_code & 0x00F0) >> 4;
    system->v_registers[index_x] = system->v_registers[index_y];
    system->program_counter += 2;
}

void logical_or_registers(System * system, uint16_t op_code)
{
    uint8_t index_x = (op_code & 0x0F00) >> 8;
    uint8_t index_y = (op_code & 0x00F0) >> 4;
    system->v_registers[index_x] |= system->v_registers[index_y];
    system->program_counter += 2;
}

void logical_and_registers(System * system, uint16_t op_code)
{
    uint8_t index_x = (op_code & 0x0F00) >> 8;
    uint8_t index_y = (op_code & 0x00F0) >> 4;
    system->v_registers[index_x] &= system->v_registers[index_y];
    system->program_counter += 2;
}

void logical_xor_registers(System * system, uint16_t op_code)
{
    uint8_t index_x = (op_code & 0x0F00) >> 8;
    uint8_t index_y = (op_code & 0x00F0) >> 4;
    system->v_registers[index_x] ^= system->v_registers[index_y];
    system->program_counter += 2;
}

void add_register_to_register(System * system, uint16_t op_code)
{
    uint8_t index_x = (op_code & 0x0F00) >> 8;
    uint8_t index_y = (op_code & 0x00F0) >> 4;
    uint8_t value_x = system->v_registers[index_x];
    uint8_t value_y = system->v_registers[index_y];
    uint16_t value = value_x + value_y;
    system->v_registers[NUM_V_REGISTERS-1] = value > 0xFF;
    system->v_registers[index_x] = (uint8_t) value;
    system->program_counter += 2;
}

void subtract_registers(System * system, uint16_t op_code)
{
    uint8_t index_x = (op_code & 0x0F00) >> 8;
    uint8_t index_y = (op_code & 0x00F0) >> 4;
    uint8_t value_x = system->v_registers[index_x];
    uint8_t value_y = system->v_registers[index_y];
    system->v_registers[NUM_V_REGISTERS-1] = (value_y > value_x) ? 0 : 1;
    system->v_registers[index_x] -= value_y;
    system->program_counter += 2;
}

void reverse_subtract_registers(System * system, uint16_t op_code)
{
    uint8_t index_x = (op_code & 0x0F00) >> 8;
    uint8_t index_y = (op_code & 0x00F0) >> 4;
    uint8_t value_x = system->v_registers[index_x];
    uint8_t value_y = system->v_registers[index_y];
    system->v_registers[NUM_V_REGISTERS-1] = (value_x > value_y) ? 0 : 1;
    system->v_registers[index_x] = abs((int)value_y - (int)value_x) & 0xFF;
    system->program_counter += 2;
}

void right_shift_register(System * system, uint16_t op_code)
{
    uint8_t index_x = (op_code & 0x0F00) >> 8;
    uint8_t value_x = system->v_registers[index_x];
    system->v_registers[NUM_V_REGISTERS-1] = value_x & 0x01;
    system->v_registers[index_x] = value_x >> 1;
    system->program_counter += 2;
}

void left_shift_register(System * system, uint16_t op_code)
{
    uint8_t index_x = (op_code & 0x0F00) >> 8;
    uint8_t value_x = system->v_registers[index_x];
    system->v_registers[NUM_V_REGISTERS-1] = (value_x & 0x80) >> 7;
    system->v_registers[index_x] = value_x << 1;
    system->program_counter += 2;
}

void set_index(System * system, uint16_t op_code)
{
    system->index_register = op_code & 0x0FFF;
    system->program_counter += 2;
}

void set_register_to_random_value(System * system, uint16_t op_code)
{
    uint8_t value = op_code & 0x00FF;
    uint8_t index_x = (op_code & 0x0F00) >> 8;
    system->v_registers[index_x] = (rand() % 0xFF) & value;
    system->program_counter += 2;
}

void draw_sprite(System * system, uint16_t op_code)
{
    uint8_t index_x = (op_code & 0x0F00) >> 8;
    uint8_t index_y = (op_code & 0x00F0) >> 4;
    uint8_t value_x = system->v_registers[index_x];
    uint8_t value_y = system->v_registers[index_y];
    uint8_t num_bytes = op_code & 0x000F;
    uint8_t * sprite = &system->main_memory[system->index_register];
    system->v_registers[NUM_V_REGISTERS - 1] = 0;
    for (unsigned int byte_num = 0; byte_num < num_bytes; byte_num++)
    {
        uint8_t byte = sprite[byte_num];
        for (unsigned int bit_num = 0; bit_num < 8; bit_num++)
        {
            if ((byte & (0x80 >> bit_num)) == 0)
                continue;
            unsigned int video_index = (value_y + byte_num) * VIDEO_WIDTH + value_x + bit_num;
            if (system->video_memory[video_index] == 1)
                system->v_registers[NUM_V_REGISTERS - 1] = 1;
            system->video_memory[video_index] ^= 1;
        }
    }
    system->video_changed = true;
    system->program_counter += 2;
}

void skip_if_key_pressed(System * system, uint16_t op_code)
{
    uint8_t index_x = (op_code & 0x0F00) >> 8;
    uint8_t value_x = system->v_registers[index_x];
    if (system->key_states[value_x])
        system->program_counter += 2;
    system->program_counter += 2;
}

void skip_if_key_not_pressed(System * system, uint16_t op_code)
{
    uint8_t index_x = (op_code & 0x0F00) >> 8;
    uint8_t value_x = system->v_registers[index_x];
    if (!system->key_states[value_x])
        system->program_counter += 2;
    system->program_counter += 2;
}

void wait_for_key_pressed(System * system, uint16_t op_code)
{
    uint8_t index_x = (op_code & 0x0F00) >> 8;
    for (uint8_t key=0; key < NUM_KEYS; key++)
    {
        if (system->key_states[key])
        {
            system->v_registers[index_x] = key;
            system->program_counter += 2;
            break;
        }
    }
}

void set_register_to_delay_timer(System * system, uint16_t op_code)
{
    uint8_t index_x = (op_code & 0x0F00) >> 8;
    system->v_registers[index_x] = system->delay_timer;
    system->program_counter += 2;
}

void set_delay_timer_to_register(System * system, uint16_t op_code)
{
    uint8_t index_x = (op_code & 0x0F00) >> 8;
    system->delay_timer = system->v_registers[index_x];
    system->program_counter += 2;
}

void set_sound_timer_to_register(System * system, uint16_t op_code)
{
    uint8_t index_x = (op_code & 0x0F00) >> 8;
    system->sound_timer = system->v_registers[index_x];
    system->program_counter += 2;
}

void add_register_to_index(System * system, uint16_t op_code)
{
    uint8_t index_x = (op_code & 0x0F00) >> 8;
    uint16_t value = system->index_register + system->v_registers[index_x];
    system->v_registers[NUM_V_REGISTERS-1] = value > 0xFFF;
    system->index_register = value;
    system->program_counter += 2;
}

void set_index_to_digit_sprite(System * system, uint16_t op_code)
{
    uint8_t index_x = (op_code & 0x0F00) >> 8;
    uint8_t value_x = system->v_registers[index_x];
    system->index_register = value_x * 0x05;
    system->program_counter += 2;
}

void store_register_as_bcd_at_index(System * system, uint16_t op_code)
{
    uint8_t index_x = (op_code & 0x0F00) >> 8;
    uint8_t value_x = system->v_registers[index_x];
    uint8_t hundreds = (value_x/100) % 10;
    system->main_memory[system->index_register] = hundreds;
    uint8_t tens = (value_x/10) % 10;
    system->main_memory[system->index_register+1] = tens;
    uint8_t ones = value_x % 10;
    system->main_memory[system->index_register+2] = ones;
    system->program_counter += 2;
}

void store_registers(System * system, uint16_t op_code)
{
    uint8_t max_register = (op_code & 0x0F00) >> 8;
    for (unsigned int reg_index = 0; reg_index <= max_register; reg_index++)
    {
        system->main_memory[system->index_register + reg_index] = system->v_registers[reg_index];
    }
    system->program_counter += 2;
}

void load_registers(System * system, uint16_t op_code)
{
    uint8_t max_register = (op_code & 0x0F00) >> 8;
    for (unsigned int reg_index = 0; reg_index <= max_register; reg_index++)
    {
        system->v_registers[reg_index] = system->main_memory[system->index_register + reg_index];
    }
    system->program_counter += 2;
}
