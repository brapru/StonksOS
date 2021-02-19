#include "utils.hpp"
#include "entry.hpp"
#include "peripherals/aux.hpp"
#include "irq.hpp"
#include "mini_uart.hpp"
#include "stonksos/stdio.hpp"

static Stdio stdio;
static MiniUart mu;

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

extern "C" void show_invalid_entry_message(u32 type, u64 esr, u64 address){
	/* will printf eventually */
	stdio.printf("Interrupt Error: %s - %d, ESR: %X, Address: %X\n", 
		entry_error_messages[type], type, esr, address);	
}

void IRQ::enable_interrupt_controller(void){
#if RPI_VERSION == 4
	get_irq_regs_ptr()->irq0_enable_0 = AUX_IRQ;	
#endif

#if RPI_VERSION == 3
	get_irq_regs_ptr()->irq0_enable_1 = AUX_IRQ;	
#endif
}

void IRQ::handle_irq(void){
	u32 irq;

#if RPI_VERSION == 4
	irq = get_irq_regs_ptr()->irq0_pending_0;
#endif

#if RPI_VERSION == 3
	irq = get_irq_regs_ptr()->irq0_pending_1;
#endif

	while(irq) {
		if (irq & AUX_IRQ){
			irq &= ~AUX_IRQ;
		
			while((mu.get_aux_object()->get_aux_regs_ptr()->mu_ier & 4) == 4){
				stdio.printf("UART Recv: ");
				mu.uart_send(mu.uart_recv());
				stdio.printf("\n");
			}
		}
	}


}
