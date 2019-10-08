#ifndef EMULATOR_H
#define EMULATOR_H

#include <emulator/system.h>
#include <rendering/frame_buffer.h>

#define VIDEO_SCALE 16
#define VIDEO_FPS 60
#define VIDEO_TICKS_PER_FRAME (1000 / VIDEO_FPS)
#define VIDEO_COLOR 0xE0A500

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