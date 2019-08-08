#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>
#include <binary_blob.h>
#include <stdbool.h>

#define MAIN_MEMORY_SIZE 4096
#define VIDEO_WIDTH 64
#define VIDEO_HEIGHT 32
#define VIDEO_MEMORY_SIZE VIDEO_WIDTH * VIDEO_HEIGHT
#define NUM_V_REGISTERS 16
#define STACK_SIZE 16
#define NUM_KEYS 16

#define ADDRESS_ROM 0x200

typedef struct {
    bool is_running;
    bool video_changed;
    bool audio_triggered;
    uint8_t main_memory[MAIN_MEMORY_SIZE];
    uint8_t video_memory[VIDEO_MEMORY_SIZE];
    uint8_t v_registers[NUM_V_REGISTERS];

    uint16_t index_register;
    uint16_t program_counter;

    uint16_t stack[STACK_SIZE];
    uint16_t stack_pointer;

    uint8_t delay_timer;
    uint8_t sound_timer;

    uint8_t key_states[NUM_KEYS];
} System;


System init_system(const BinaryBlob * rom);

#endif