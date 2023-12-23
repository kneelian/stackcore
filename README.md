# stackcore
A tiny toy fantasy CPU core/ISA built around the stack as the main storage unit.

The stackcore is a ternary toy CPU. It is a simple stack machine that is centred around an 81-word (3⁴ word) stack. Each word is 3 trytes (18 trits) wide, holding approximately 28.5 bits of information. There are also two general registers A and B, both 3 trytes wide and mostly used for address resolution, and general memory is structured into pages, each 3^12 trytes long (page addresses are two trytes wide). 

# Building

`./build.sh` for now. The stackcore depends on SDL2 in path (`#include <SDL2/SDL2.h>`) and FMT in the project directory (headers in `include/fmt` and shared library object files in `lib`).

# Internals

Apart from the A/B registers, there is also a number of other internal registers:

* `SR` -- stack depth register, keeping track of how many items are on the stack
* `IP` -- instruction pointer, holding the address of the next instruction to decode
* `FR` -- flags register, holding things like results of conditional checks and carry/borrow status
* `ZR` -- zero register, all reads are always zero and all writes are discarded

As physical memory addresses are two trytes, but address registers are three trytes wide, the most significant tryte can be considered to be wired to zero, and can be used as signalling (for example, to mark the memory address in some way).