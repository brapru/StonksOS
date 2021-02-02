#pragma once

namespace kernel {

inline void delay(unsigned long ticks){
	asm volatile("delay:; "
		     "subs %0, %0, #1;"
		     "bne delay"
		     : :"r" (ticks));
}

inline unsigned int get32(unsigned long address){
	unsigned int retval;	
	asm volatile("ldr %0, [%1]" 
			: "=r" (retval)
			: "r" (address));
	return retval;
}

inline void put32(unsigned long address, unsigned int value){
	asm volatile("str w1, [x0]" : : "r" (address), "r" (value));
}

}
