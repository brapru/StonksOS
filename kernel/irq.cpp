#include "utils.hpp"
#include "entry.hpp"
#include "peripherals/aux.hpp"
#include "irq.h"
#include "mini_uart.hpp"
#include "stonksos/stdio.hpp"

static Stdio stdio;

const char entry_error_messages[16][32] = {
	"SYNC_INVALID_EL1t",
	"IRQ_INVALID_EL1t",		
	"FIQ_INVALID_EL1t",		
	"ERROR_INVALID_EL1T",		

	"SYNC_INVALID_EL1h",
	"IRQ_INVALID_EL1h",		
	"FIQ_INVALID_EL1h",		
	"ERROR_INVALID_EL1h",		

	"SYNC_INVALID_EL0_64",		
	"IRQ_INVALID_EL0_64",		
	"FIQ_INVALID_EL0_64",		
	"ERROR_INVALID_EL0_64",	

	"SYNC_INVALID_EL0_32",		
	"IRQ_INVALID_EL0_32",		
	"FIQ_INVALID_EL0_32",		
	"ERROR_INVALID_EL0_32"	
};

void show_invalid_entry_message(u32 type, u64 esr, u64 address){
	/* will printf eventually */
	stdio::printf("Interrupt Error: %s - %d, ESR: %X, Address: %X\n", 
		entry_error_messages[type], type, esr, address);	
}

void IRQ::enable_interrupt_controller(void){
#if RPI_VERSION == 4
	put32(get_itq_regs_ptr->irq0_enable_0, (1<<1));	
#endif

#if RPI_VERSION == 3
	put32(get_itq_regs_ptr->irq0_enable_0, (1<<1));	
#endif
} 
