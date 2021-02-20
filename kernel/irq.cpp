#include "utils.hpp"
#include "entry.hpp"
#include "peripherals/aux.hpp"
#include "irq.hpp"
#include "mini_uart.hpp"
#include "stonksos/stdio.hpp"

static Stdio stdio;
static MiniUart s_mu;
//static IRQ s_irq;

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
	stdio.printf("Interrupt Error: %s - %d, ESR: %X, Address: %X\n", 
		entry_error_messages[type], type, esr, address);	
}

extern "C" void handle_irq(){
	u32 irq;

	stdio.puts("INSIDE HANDLE IRQ");
#if RPI_VERSION == 4
	irq = IRQ::get_irq_regs_ptr()->irq0_pending_0;
#endif

#if RPI_VERSION == 3
	irq = IRQ::get_irq_regs_ptr()->irq0_pending_1;
#endif

	while(irq) {
		if (irq & AUX_IRQ){
			irq &= ~AUX_IRQ;
		
			while((s_mu.get_aux_object()->get_aux_regs_ptr()->mu_ier & 4) == 4){
				stdio.puts("UART Recv: ");
				s_mu.uart_send(s_mu.uart_recv());
				stdio.printf("\n");
			}
		}
	}


}

void IRQ::enable_interrupt_controller(void){
	stdio.puts("INSIDE IRQ ENABLE INTERRUPT CONTROLLER");
#if RPI_VERSION == 4
	IRQ::get_irq_regs_ptr()->irq0_enable_0 = AUX_IRQ;	
#endif

#if RPI_VERSION == 3
	IRQ::get_irq_regs_ptr()->irq0_enable_1 = AUX_IRQ;	
	stdio.printf("Value of AUX_REG is: %ld", IRQ::get_irq_regs_ptr()->irq0_enable_1);
#endif
}
