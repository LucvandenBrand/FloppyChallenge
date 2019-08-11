#include <rendering/frame_buffer.h>
#include <stdlib.h>

FrameBuffer create_frame_buffer(RenderContext context, unsigned int width, unsigned int height)
{
    SDL_Texture * texture = SDL_CreateTexture(context.renderer, SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STATIC, (int) width, (int) height);
    uint32_t * pixels = calloc(width * height, sizeof(uint32_t));
    FrameBuffer buffer = {
            texture,
            pixels,
            width,
            height
    };
    return buffer;
}

void free_frame_buffer(FrameBuffer * frame_buffer)
{
    free(frame_buffer->pixels);
    SDL_DestroyTexture(frame_buffer->sdl_texture);
}

void present_frame_buffer(RenderContext context, FrameBuffer frame_buffer)
{
    SDL_UpdateTexture(frame_buffer.sdl_texture, NULL, frame_buffer.pixels, frame_buffer.frame_width * sizeof(uint32_t));
    SDL_RenderClear(context.renderer);
    SDL_RenderCopy(context.renderer, frame_buffer.sdl_texture, NULL, NULL);
    SDL_RenderPresent(context.renderer);
}