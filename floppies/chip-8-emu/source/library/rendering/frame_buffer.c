#include <rendering/frame_buffer.h>
#include <stdlib.h>

FrameBuffer create_frame_buffer(RenderContext context, unsigned int width, unsigned int height)
{
    SDL_Texture * texture = SDL_CreateTexture(context.renderer, SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING, (int) width, (int) height);
    FrameBuffer buffer = {
            texture,
            NULL,
            width,
            height
    };
    return buffer;
}

void free_frame_buffer(FrameBuffer * frame_buffer)
{
    SDL_DestroyTexture(frame_buffer->sdl_texture);
}

void present_frame_buffer(RenderContext context, FrameBuffer frame_buffer)
{
    SDL_RenderCopy(context.renderer, frame_buffer.sdl_texture, NULL, NULL);
    SDL_RenderPresent(context.renderer);
}

int lock_frame_buffer(FrameBuffer * frame_buffer)
{
    if (frame_buffer->pixels != NULL)
        return -1;
    return SDL_LockTexture(frame_buffer->sdl_texture, NULL, &frame_buffer->pixels, &frame_buffer->pitch);
}

void unlock_frame_buffer(FrameBuffer * frame_buffer)
{
    frame_buffer->pixels = NULL;
    return SDL_UnlockTexture(frame_buffer->sdl_texture);
}