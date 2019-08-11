#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include <SDL2/SDL.h>
#include "render_context.h"

typedef struct {
    SDL_Texture * sdl_texture;
    uint32_t * pixels;
    const unsigned int frame_width;
    const unsigned int frame_height;
} FrameBuffer;

FrameBuffer create_frame_buffer(RenderContext context, unsigned int width, unsigned int height);
void free_frame_buffer(FrameBuffer * frame_buffer);
void present_frame_buffer(RenderContext context, FrameBuffer frame_buffer);

#endif