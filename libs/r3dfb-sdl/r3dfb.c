/*****************************************************
* r3dfb -- 3D rendering library framebuffer for SDL  *
* author: rene-dev, Andreas Mantler (ands)           *
*****************************************************/

#include <string.h>
#include <SDL2/SDL.h>
#include "r3d.h"
#include "r3dfb.h"

static SDL_Window* window;
static SDL_Surface* surface;
static float depthbuffer[R3DFB_PIXEL_WIDTH * R3DFB_PIXEL_HEIGHT];
static uint32_t *colorbuffer;

void r3dfb_init(void)
{
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("r3dfb-sdl", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, R3DFB_PIXEL_WIDTH, R3DFB_PIXEL_HEIGHT, SDL_WINDOW_SHOWN);
	surface = SDL_GetWindowSurface(window);
	colorbuffer = (uint32_t*)surface->pixels;
}

void r3dfb_clear(void)
{
	memset(depthbuffer, 0x00, R3DFB_DEPTH_BUFFER_SIZE);
	memset(colorbuffer, 0xff, R3DFB_COLOR_BUFFER_SIZE);
}

void r3dfb_swap_buffers(void)
{
	SDL_UpdateWindowSurface(window);
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
		{
			SDL_Quit();
			exit(0);
		}
	}
}

// r3d interface
void r3d_set_pixel(uint16_t x, uint16_t y, float z, vec3_t color)
{
	depthbuffer[y * R3DFB_PIXEL_WIDTH + x] = z;
	colorbuffer[y * R3DFB_PIXEL_WIDTH + x] = 0xff000000 | (int)(color.r * 255) << 16 | (int)(color.g * 255) << 8 | (int)(color.b * 255); // ARGB
}

float r3d_get_depth(uint16_t x, uint16_t y)
{
	return depthbuffer[y * R3DFB_PIXEL_WIDTH + x];
}
