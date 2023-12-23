# stackcore
A tiny toy fantasy CPU core/ISA built around the stack as the main storage unit.

The stackcore is a ternary toy CPU. It is a simple stack machine that is centred around an 81-word (3⁴ word) stack. Each word is 3 trytes (18 trits) wide, holding approximately 28.5 bits of information. There are also two general registers A and B, both 3 trytes wide and mostly used for address resolution, and general memory is structured into pages, each 3^12 trytes long (page addresses are two trytes wide). 

# Building

`./build.sh` for now
