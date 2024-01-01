#pragma once

#include <fstream>
#include <string>
#include "defines.hpp"

bool read_code_file(std::string path, std::array<BYTE, 1<<16>& ROM_page)
{
	std::ifstream input_file (path, std::ios::in | std::ios::binary);
	
	if(!input_file.is_open() || !input_file.good())
	{
		if(DEBUG)
		{	
			fmt::print(
				"{} to open file \"{}\"\n", 
				fmt::styled("Failed", fmt::fg(fmt::color::crimson)),
				fmt::styled(path, fmt::fg(fmt::color::light_steel_blue)) 
			); 
		}
		return false;
	}

	input_file.read(reinterpret_cast<char*>(ROM_page.data()), 1<<16);
	return true;
}