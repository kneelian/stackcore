#include <vector>
#include "fmt/core.h"
#include "fmt/color.h"
#include <SDL2/SDL.h>

#include "screen.hpp"

int main()
{
	SCREEN _newscreen;

	fmt::print("SDL initialisation {}\n",
    	fmt::styled
        (
        	"successful", 
           	fmt::fg(fmt::color::lime_green) | 
           	fmt::emphasis::italic | 
           	fmt::emphasis::bold
		)
    );
	
	_newscreen.clear();

	for(int a = 40; a < 80; a++)
	{
		for(int b = 320; b < 340; b++)
		{
			_newscreen.write(a, b, 0x00abbcff);
		}
	}
	_newscreen.upd();

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

	int j = 0;
	for(int i = 0; i < _newscreen.h * _newscreen.w; i++)
	{
		_newscreen.write(i, j);
		j += (131 << 24) + (0 << 16) + (251 << 8);
	}
	_newscreen.upd();
	SDL_Delay(50);
	for(int i = 0; i < _newscreen.h * _newscreen.w; i++)
	{
		_newscreen.write(i, j);
		j += (151 << 24) + (14 << 16) + (221 << 8);
	}
	_newscreen.upd();
	SDL_Delay(50);

	return 0;
}