#pragma once

#include <stack>
#include <array>
#include <memory>

#include "fmt/core.h"
#include "fmt/color.h"

#include "defines.hpp"

#include "insn_decode.hpp"
#include "readfile.hpp"

class cpu_t { 

public:
	uint64_t  i_ticks    = 0;
	uint32_t  i_syndrome = 0;

	cpu_t(uint64_t*);
	cpu_t();
	~cpu_t();

	bool tick();
	bool reset();

	bool add_extra_page()
	{
		for(int i = 0; i < i_data_extra.size(); i++)
		{
			if(i_data_extra[i] != nullptr) { continue; }
			i_data_extra[i] = new std::array<BYTE, (1<<16)>;

			if(DEBUG)
			{	fmt::print("{} new memory page\n", fmt::styled("Added", fmt::fg(fmt::color::lime_green)) ); }

			return true;
		}
		if(DEBUG)
		{	fmt::print("{} to add new memory page\n", fmt::styled("Failed", fmt::fg(fmt::color::crimson)) ); }
		return false;
	}

private:

	BYTE fetch_b();
	WORD fetch_i();

	bool push(WORD);
	bool pop(WORD&);

	bool load_insn_page(std::string);

	std::stack<WORD, std::array<WORD, 64>> i_stack;

	std::unique_ptr<std::array<BYTE, (1<<16)>> i_insn_page;	// aka ROM page
	std::unique_ptr<std::array<BYTE, (1<<16)>> i_zero_page; // aka zeropage

	std::array< std::array<BYTE, (1<<16)>*, 4> i_data_extra = { nullptr, nullptr, nullptr, nullptr };

	BYTE i_stack_depth = 0;  // SR

	BYTE i_fetched_insn = 0;
	WORD i_fetched_immd = 0;

	WORD i_insn_pointer = 0; // IP
	WORD i_flags_info_r = 0; // FR

	// const WORD i_zero_r = 0; // ZR; but not implemented because it's not a 'real' register

	WORD i_reg_a = 0; // A
	WORD i_reb_b = 0; // B
};

cpu_t::cpu_t()
{
	if(DEBUG)
	{	fmt::print("Default CPU constructor reached\n"); }
	i_insn_page = std::make_unique<std::array<BYTE, (1<<16)>>();
	if(DEBUG)
	{	fmt::print("{} instruction page\n", fmt::styled("Allocated", fmt::fg(fmt::color::lime_green)) ); }
	i_zero_page = std::make_unique<std::array<BYTE, (1<<16)>>();
	if(DEBUG)
	{	fmt::print("{} zero page\n", fmt::styled("Allocated", fmt::fg(fmt::color::lime_green)) ); }
}

cpu_t::cpu_t(uint64_t* external_signaller)
{
	if(DEBUG)
	{	fmt::print("Parametrised CPU constructor reached. {}: this is currently unimplemented\n", 
		fmt::styled("Warning", fmt::fg(fmt::color::orange))); }
	/*i_signaller = external_signaller;*/
	i_insn_page = std::make_unique<std::array<BYTE, (1<<16)>>();
	if(DEBUG)
	{	fmt::print("{} instruction page\n", fmt::styled("Allocated", fmt::fg(fmt::color::lime_green)) ); }
	i_zero_page = std::make_unique<std::array<BYTE, (1<<16)>>();
	if(DEBUG)
	{	fmt::print("{} zero page\n", fmt::styled("Allocated", fmt::fg(fmt::color::lime_green)) ); }
}

cpu_t::~cpu_t()
{
/*
	delete i_insn_page;
	delete i_zero_page;
	// no need for this since they're smart pointers now
*/
	for(int i = 0; i < i_data_extra.size(); i++)
	{
		if(i_data_extra.at(i) != nullptr) 
		{ 
			delete i_data_extra.at(i);
			if(DEBUG)
			{	fmt::print("{} extra memory page #{}\n", fmt::styled("Deleted", fmt::fg(fmt::color::lime_green)), i); }
		} 
	}
	if(DEBUG)
		fmt::print("CPU destructor reached\n"); 
}