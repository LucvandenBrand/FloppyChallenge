#ifndef EMULATOR_H
#define EMULATOR_H

#include <emulator/system.h>
#include <rendering/frame_buffer.h>

void emulate_rom(const BinaryBlob * rom);
void step_system_cpu(System * system);
void process_op_code(System * system, uint16_t op_code);
void step_timers(System * system);
void copy_system_video_memory(System system, FrameBuffer frame_buffer);

#endif