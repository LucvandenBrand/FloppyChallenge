#include <rendering/render_context.h>
#include <io/cmd_interface.h>

RenderContext create_render_context(const char * title, unsigned int screen_width, unsigned int screen_height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        log_message(ERROR, "Could not initialise SDL.");
        exit(EXIT_FAILURE);
    }

    SDL_Window * window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                           (int) screen_width, (int) screen_height, SDL_WINDOW_SHOWN);
    if (!window)
    {
        log_message(ERROR, "Could not create SDL window.");
        exit(EXIT_FAILURE);
    }

    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        log_message(ERROR, "Could not create SDL renderer.");
        exit(EXIT_FAILURE);
    }

    RenderContext context = {
        window,
        renderer,
        screen_width,
        screen_height,
        title
    };

    return context;
}

void free_render_context(RenderContext * renderContext)
{
    SDL_DestroyRenderer(renderContext->renderer);
    SDL_DestroyWindow(renderContext->window);
    SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
    SDL_Quit();
}