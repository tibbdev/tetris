#pragma once
#include "SDL2/SDL.h"

#define SCREEN_WIDTH        (320)
#define SCREEN_HEIGHT       (240)
#define SCREEN_PIXEL_COUNT  (SCREEN_WIDTH * SCREEN_HEIGHT)

#include <stdint.h>

int8_t graphics_init(uint16_t width, uint16_t height);
int8_t graphics_setPixelRGB(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b);
int8_t graphics_setPixelRGBA(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
int8_t graphics_render(void);
void graphics_kill(void);