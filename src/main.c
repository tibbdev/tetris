#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "graphics.h"

SDL_Window      *window     = NULL;
SDL_Renderer    *renderer   = NULL;

uint8_t NOISE_BUFFER[(SCREEN_PIXEL_COUNT * 3) + (SCREEN_PIXEL_COUNT >> 2) + (SCREEN_PIXEL_COUNT >> 8) + (SCREEN_HEIGHT / 3)];

bool run_game(void);
bool run_game(void)
{
    SDL_Event e;
    bool quit = false;
    uint8_t colour;
    uint16_t noise_idx = 0;
    while (!quit){
        // Poll for events
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                quit = true;
            }
            if (e.type == SDL_KEYDOWN){
                quit = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN){
                quit = true;
            }
        }

        for (uint16_t y = 0; y < SCREEN_HEIGHT; y++)
        {
            for (uint16_t x = 0; x < SCREEN_WIDTH; x++)
            {
                colour = NOISE_BUFFER[noise_idx % (sizeof(NOISE_BUFFER) / sizeof(NOISE_BUFFER[0]))];
                noise_idx++;
                
                graphics_setPixelRGB(x, y, colour, colour, colour);
            }
        }

        graphics_render();
    }

    return true;
}

int main()
{
    printf("graphics initialisation...\r\n");
    if(graphics_init(SCREEN_WIDTH, SCREEN_HEIGHT) == 0)
    {
        printf("...done.\r\n");

        printf("loading noise...\r\n");
        for(uint32_t idx = 0; idx < (sizeof(NOISE_BUFFER) / sizeof(NOISE_BUFFER[0])); idx++)
        {
            NOISE_BUFFER[idx] = rand() % UINT8_MAX;
        }
        printf("...done.\r\n");

        printf("running game...\r\n");
        run_game();

        printf("...game quit\r\n");

        graphics_kill();

    }
    else
    {
        printf("initialisation error : %s\r\n", SDL_GetError());
    }
    printf("exiting...\r\n");
    
    return 0;
}