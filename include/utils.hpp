#pragma once

namespace kernel {

inline void delay(unsigned long ticks){
	asm volatile("delay:; "
		     "subs %[ticks], %[ticks], #1;"
		     "bne delay"
		     :[ticks] "=r" (ticks));
}

inline unsigned int get32(unsigned long address){
	unsigned int retval;	
	asm volatile("ldr %0, [%1]" 
			: "=r" (retval)
			: "r" (address));
	return retval;
}

}

extern "C" void put32(unsigned long address, unsigned int value);

