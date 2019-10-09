#ifndef OP_CODES_H
#define OP_CODES_H

#include "system.h"

void call_subroutine(System * system, uint16_t op_code);
void exit_subroutine(System * system, uint16_t op_code);
void clear_video_memory(System * system, uint16_t op_code);
void jump(System * system, uint16_t op_code);
void jump_with_register_offset(System * system, uint16_t op_code);
void skip_if_equal_value(System * system, uint16_t op_code);
void skip_if_not_equal_value(System * system, uint16_t op_code);
void skip_if_equal_registers(System * system, uint16_t op_code);
void skip_if_not_equal_registers(System * system, uint16_t op_code);
void store_value_in_register(System * system, uint16_t op_code);
void add_value_to_register(System * system, uint16_t op_code);
void store_register_in_register(System * system, uint16_t op_code);
void logical_or_registers(System * system, uint16_t op_code);
void logical_and_registers(System * system, uint16_t op_code);
void logical_xor_registers(System * system, uint16_t op_code);
void add_register_to_register(System * system, uint16_t op_code);
void subtract_registers(System * system, uint16_t op_code);
void reverse_subtract_registers(System * system, uint16_t op_code);
void right_shift_register(System * system, uint16_t op_code);
void left_shift_register(System * system, uint16_t op_code);
void set_index(System * system, uint16_t op_code);
void set_register_to_random_value(System * system, uint16_t op_code);
void draw_sprite(System * system, uint16_t op_code);
void skip_if_key_pressed(System * system, uint16_t op_code);
void skip_if_key_not_pressed(System * system, uint16_t op_code);
void wait_for_key_pressed(System * system, uint16_t op_code);
void set_register_to_delay_timer(System * system, uint16_t op_code);
void set_delay_timer_to_register(System * system, uint16_t op_code);
void set_sound_timer_to_register(System * system, uint16_t op_code);
void add_register_to_index(System * system, uint16_t op_code);
void set_index_to_digit_sprite(System * system, uint16_t op_code);
void store_register_as_bcd_at_index(System * system, uint16_t op_code);
void store_registers(System * system, uint16_t op_code);
void load_registers(System * system, uint16_t op_code);

#endif