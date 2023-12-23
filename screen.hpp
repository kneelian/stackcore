#include<SDL2/SDL.h>
#include "fmt/core.h"
#include "fmt/color.h"

#define _WIDTH  640
#define _HEIGHT 480

struct SCREEN
{
	SDL_Window*  window  = nullptr;
	SDL_Surface* surface = nullptr;

	uint32_t* pixptr = nullptr;

	const int WIDTH  = 640;
	const int HEIGHT = 480;

	const int w = WIDTH;
	const int h = HEIGHT;

	SCREEN()
	{
		if(SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			fmt::print(
				"{}: SDL failed to initialise\n",
				fmt::styled("ERROR", fmt::fg(fmt::color::crimson) | fmt::emphasis::bold)
			);
			throw;
		}
		window = 
			SDL_CreateWindow
			(
				"SDL Window", 
				SDL_WINDOWPOS_UNDEFINED, 
				SDL_WINDOWPOS_UNDEFINED,
				WIDTH,
				HEIGHT,
				SDL_WINDOW_SHOWN
			);
		if(window == NULL)
		{
			fmt::print(
				"{}: SDL window failed on creation\n",
				fmt::styled("ERROR", fmt::fg(fmt::color::crimson) | fmt::emphasis::bold)
			);
			throw;
		}
		SDL_Surface* surface = SDL_GetWindowSurface(window);
		SDL_FillRect
		(
			surface,
			NULL,
			SDL_MapRGB( surface->format, 0xFF, 0xFF, 0xFF )
		);

		pixptr = (uint32_t*)surface->pixels;
	}

	~SCREEN()
	{
		SDL_DestroyWindow(window);
		SDL_FreeSurface(surface);
    	SDL_Quit();
	}

	bool clear()
	{
		for(int i = 0; i < WIDTH * HEIGHT; i++)
		{
			pixptr[i] = 0xffffffff;
		}
		upd();
		return true;
	}
	bool write(int x, int y, uint32_t colour)	// column and row
	{
		if(x >= WIDTH or y >= HEIGHT) { return false; }
		pixptr[x + (y * WIDTH)] = colour;
		return true;
	}
	bool write(int a, uint32_t colour)
	{
		if (a >= (WIDTH * HEIGHT)) { return false; }
		pixptr[a] = colour;
		return true;
	}
	bool upd()
	{
		return SDL_UpdateWindowSurface(window);
	}
};