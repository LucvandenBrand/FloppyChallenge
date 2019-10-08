#ifndef EMULATOR_H
#define EMULATOR_H

#include <emulator/system.h>
#include <rendering/frame_buffer.h>

#define VIDEO_SCALE 12

void emulate_rom(const BinaryBlob * rom);
void step_system_cpu(System * system);
void process_op_code(System * system, uint16_t op_code);
void step_timers(System * system);
void update_system_key_states(System * system);
void process_event(SDL_Event event, System * system);
void process_key_event(SDL_KeyboardEvent key, System * system);
int map_key_to_index(SDL_Keycode key_code);
void process_window_event(SDL_WindowEvent window, System * system);
void copy_system_video_memory(System system, FrameBuffer * frame_buffer);

#endif