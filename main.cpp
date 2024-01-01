#include <vector>
#include "fmt/core.h"
#include "fmt/color.h"
#include <SDL2/SDL.h>
#include <random>

#include "defines.hpp"

#include "screen.hpp"
#include "cpu.hpp"

void enn_sdl_demo();
int main()
{
	enn_sdl_demo();
}

/*
	basically there's no real ISA or even implementation 

	and the cpu is now binary

*/


void enn_sdl_demo()
{
	SCREEN _newscreen;
	if(DEBUG) {
	fmt::print("SDL initialisation {}\n",
    	fmt::styled
        (
        	"successful", 
           	fmt::fg(fmt::color::lime_green) | 
           	fmt::emphasis::bold
		)
    ); }
	
	_newscreen.clear();

	for(int a = 40; a < 80; a++)
	{
		for(int b = 320; b < 340; b++)
		{
			_newscreen.write(a, b, 0x00abbcff);
		}
	}
	_newscreen.update();

	SDL_Event e; 
	bool quit = false; 
	while( quit == false )
	{
		while( SDL_PollEvent( &e ) )
		{ 
			if( e.type == SDL_QUIT )
			{
				quit = true;
			} 
		} 
	}

	if(DEBUG) 
	{ fmt::print("Quit signal received\n"); }

	std::random_device rd;
	std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 255);

    int32_t j = 0;

    for(int i = 20; i; i--)
    {
		for(int i = 0; i < _newscreen.h * _newscreen.w; i++)
		{
			_newscreen.write(i, j);
			j += (distrib(gen) << 16) + (distrib(gen) << 8) + ( 0);
		}
		_newscreen.update();
		SDL_Delay(10);
    }

	SDL_Delay(50);

	if(DEBUG) 
	{ fmt::print("End of demo reached\n"); }

	return;
}