#pragma once
#define DEBUG true

#define WORD uint16_t
#define BYTE uint8_t

#define WORD_S int16_t
#define BYTE_s int8_t

// CPU syndromes and errors

#define FAIL 		 1<<31 // the fallback error
#define HALT 		 1<<30 // CPU requested a non-pause halt; execution is basically done-for
#define BAD_INSN 	 -3
#define STK_OVFLW	 -4
#define DIV_ZERO	 -5
#define BAD_PAGE	 -6

#define UNKNOWN		  0

#define PRINT_REQUEST 1
#define PAGE_REQUEST  2
#define BREAKPOINT	  3
#define PAUSE         4
#define TICK_OVFLW    5 // how??
#define ROM_RAM_SWAP  6 // if we want to execute from RAM