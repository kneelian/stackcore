#pragma once

enum opcode_t : uint8_t
{
	NOP = 0b0'000'0000, // skip
	PAU = 0b1'100'0000, // pause execution
	BRK = 0b1'100'0001, // breakpoint
	SYS = 0b1'100'0010, // request from host/syscall

	ADD = 0b0'000'0001, // add on stack
	SUB = 0b0'000'0010,
	DIV = 0b0'000'0011,
	MUL = 0b0'000'0100,

	POP = 0b0'000'1000, // pop to ZR aka delete
	POPA= 0b0'000'1001, // pop to A
	POPB= 0b0'000'1010,
	POPF= 0b0'000'1011, // pop to flags reg
	POPJ= 0b0'000'1100, // pop to IP reg AKA jump
	POPS= 0b0'000'1101, // pop to SP

	PSHA= 0b0'001'1001,
	PSHB= 0b0'001'1010,
	PSHF= 0b0'001'1011,
	PSHJ= 0b0'001'1100,
	PSHS= 0b0'001'1101,
	PSHI= 0b1'001'1110, // push immediate
	PSHZ= 0b0'001'1111, // push zero to stack

	PKK = 0b0'010'1000, // peek to ZR aka NOP
	PKKA= 0b0'010'1001, // peek to A
	PKKB= 0b0'010'1010,
	PKKF= 0b0'010'1011, // peek to flags reg
	PKKJ= 0b0'010'1100, // peek to IP reg AKA jump without pop
	PKKS= 0b0'010'1101, // peek to SP

	RDA = 0b0'011'0000, // push from address stored in A
	RDB = 0b0'011'0001,
	WTA = 0b0'011'0010, // peek to address stored in A
	WTB = 0b0'011'0011,
	RDX = 0b0'011'0100, // read from [a + b] offset
	WTX = 0b0'011'0101, // write to  [a + b] offset

	CEQ = 0b0'100'0000, // destructive sp0 = sp1, pops both, pushes -1 or 0 result
	CGT = 0b0'100'0001,
	CLT = 0b0'100'0010,
	CZR = 0b0'100'0011, // is eq to zero? single insn/nostack version of CEQ + zero
	CNG = 0b0'100'0100, // is negative?   single insn/nostack version of CLT + zero

	AND = 0b0'100'0101, // bitwise ANDs the top two
	XOR = 0b0'100'0110,
	ORR = 0b0'100'0111, 

	CEQP= 0b0'100'1000, // safe/preserving versions of above, no pops only pushes
	CGTP= 0b0'100'1001,
	CLTP= 0b0'100'1010,
	CZRP= 0b0'100'1011,
	CNGP= 0b0'100'1100,

	ANDP= 0b0'100'0101, // safely bitwise ANDs the top two
	XORP= 0b0'100'0110,
	ORRP= 0b0'100'0111, 

	JMPA= 0b0'101'0000, // unconditional jump to A
	JMPB= 0b0'101'0001,
	JMPX= 0b0'101'0010,
	JMPI= 0b1'101'0011, // unconditional jump to immediate
	JMCA= 0b0'101'1000, // conditional jump to A
	JMCB= 0b0'101'1001,
	JMCX= 0b0'101'1010,
	JMCI= 0b1'101'1011,
	// also see POPJ and PKKJ for unconditional jumps to stack

	SPLA= 0b0'111'0000, // spill all 64 words of stack to address in A
	SPLB= 0b0'111'0001,
	SPLX= 0b0'111'0010,

	SWPX= 0b0'111'0011, // swap A and B contents
	SWP = 0b0'111'0100, // swap top two stack members
	DUP = 0b0'111'0101, // duplicate top stack member
	INC = 0b0'111'0110, // increment top of stack
	DEC = 0b0'111'0111, // decrement 

	TAKA= 0b0'111'1000, // take back spilled 64 words from address in A
	TAKB= 0b0'111'1001,
	TAKX= 0b0'111'1010,

	SHR = 0b0'111'1011, // shift sp0 by sp1, pop both, push result
	SHL = 0b0'111'1100,
	NEG = 0b0'111'1101, // negate all the bits in the top stack member

	DIE = 0b1'111'1111  // halt and catch fire
};

struct insn_t
{
	uint16_t immed = 0;
	opcode_t opcod = NOP;
};