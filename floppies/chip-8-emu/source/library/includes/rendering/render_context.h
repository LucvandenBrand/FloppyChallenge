#ifndef RENDER_CONTEXT_H
#define RENDER_CONTEXT_H

#include <SDL2/SDL.h>

typedef struct
{
    SDL_Window * window;
    SDL_Renderer * renderer;
    const unsigned int screen_width;
    const unsigned int screen_height;
    const char * title;
} RenderContext;

RenderContext create_render_context(const char * title, unsigned int screen_width, unsigned int screen_height);
void free_render_context(RenderContext * renderContext);

#endif