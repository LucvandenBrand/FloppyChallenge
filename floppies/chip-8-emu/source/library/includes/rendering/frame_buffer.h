#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include <SDL2/SDL.h>
#include "render_context.h"

typedef struct {
    SDL_Texture * sdl_texture;
    void * pixels;
    int pitch;
    const unsigned int frame_width;
    const unsigned int frame_height;
} FrameBuffer;

FrameBuffer create_frame_buffer(RenderContext context, unsigned int width, unsigned int height);
void free_frame_buffer(FrameBuffer * frame_buffer);
void present_frame_buffer(RenderContext context, FrameBuffer frame_buffer);
int lock_frame_buffer(FrameBuffer * frame_buffer);
void unlock_frame_buffer(FrameBuffer * frame_buffer);

#endif