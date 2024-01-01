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

	TODO:
		* read file from filesystem into memory and copy into ROM page
		* figure out the ISA!!
		* figure out the screen and graphics!

	the CPU API works so that you will have only very limited interaction with it: 
		you only do some minor initial set-up that it won't do automatically (such
		as populating the ROM page) and then hit .tick() to advance it and then kill
		at some unspecified interval

		the CPU can tell you something happened that requires your attention because
		the .tick() function returns a boolean; it will return false whenever it wants
		the caller to pay attention to something, which will be signalled either in
		an external signaller whose pointer is provided by the caller, so that 
		it can persist even after the CPU object is destroyed, or an internal duplicate
		in the event that this kind of behaviour is undesirable.
*/