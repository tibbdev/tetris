#include "graphics.h"

typedef struct
{
    SDL_Window      *window;
    SDL_Renderer    *renderer;
} graphics_data_t;

graphics_data_t _graphics;

int8_t graphics_init(uint16_t width, uint16_t height)
{
    int rv = SDL_Init(SDL_INIT_VIDEO);
    if(0 == rv)
    {
        rv = SDL_CreateWindowAndRenderer(width, height, 0, &_graphics.window, &_graphics.renderer);
        if(0 == rv)
        {
            SDL_SetRenderDrawColor(_graphics.renderer, 0, 0, 0, 0);
            SDL_RenderClear(_graphics.renderer);
        }
    }

    return rv;
}


int8_t graphics_setPixelRGB(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b)
{
    return graphics_setPixelRGBA(x, y, r, g, b, 0xff);
}
int8_t graphics_setPixelRGBA(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    if (NULL != _graphics.renderer)
    {
        SDL_SetRenderDrawColor(_graphics.renderer, r, g, b, a);
        return SDL_RenderDrawPoint(_graphics.renderer, x, y);
    }
    else return -1;
}

int8_t graphics_render(void)
{
    if (NULL != _graphics.renderer)
    {
        SDL_RenderPresent(_graphics.renderer);
        return 0;
    }
    else return -1;
}


void graphics_kill(void)
{
    if(NULL != _graphics.renderer)
    {
        SDL_DestroyRenderer(_graphics.renderer);
    }
    if(NULL != _graphics.window)
    {
        SDL_DestroyWindow(_graphics.window);
    }

    SDL_Quit();
}