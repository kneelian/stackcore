# stackcore
A tiny toy fantasy CPU core/ISA built around a hardware stack as the main storage unit. 

Its main feature is ease of implementation and simple structure, with more focus on developer convenience than viability as a real CPU.

# Building

`./build.sh` for now. The stackcore depends on SDL2 in path (`#include <SDL2/SDL2.h>`) and FMT in the project directory (headers in `include/fmt` and shared library object files in `lib`). In the future, I might make an effort to divorce it from these dependencies or make them optional.

# Internals

The stackcore is a 16-bit toy CPU. It is a simple stack machine that is centred around a 64-word hardware stack as the main internal data structure, with two address registers (named `A` and `B`) used primarily for addressing the heap. The address registers themselves are 16 bits wide, and heap memory is divided into 64KB pages (theoretically, 2^16 of them, though in practice only 4 pages would be available to the programmer at best).

The ISA of the CPU is simple: instructions are all one byte wide, and optional immediates are all two bytes (so a single step might fetch either one or three bytes of code). 

The CPU itself functions on a hybrid Von Neumann-Harvard model: it can either read code from an internal ROM page inaccessible to heap access instructions, or from the first heap page. There are no privilege levels or isolation at all, so it is unsuitable, for example, for a Linux kernel implementation out of the box.

Apart from the A/B registers, there is also a number of other internal registers:

* `SR` -- stack depth register, keeping track of how many items are on the stack
* `IP` -- instruction pointer, holding the address of the next instruction to decode
* `FR` -- flags register, holding things like results of conditional checks and carry/borrow status, as well as some miscellanea (like whether the CPU is fetching instructions from the instruction page or the heap)
* `ZR` -- zero register, all reads are always zero and all writes are discarded 
