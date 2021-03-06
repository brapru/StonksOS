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

inline unsigned int get_el(void)
{
	unsigned int level;
	asm volatile("mrs x0, CurrentEL;"
		     "lsr %0, %0, #2;"
		     : "=r" (level));
	return level;
}

inline void mmio_write(i64 reg, u32 val) { *(volatile u32 *)reg = val; }
inline u32 mmio_read(i64 reg) { return *(volatile u32 *)reg; }

}
