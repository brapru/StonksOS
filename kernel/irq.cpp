#include "entry.hpp"
#include "peripherals/aux.hpp"
#include "irq.hpp"
#include "mini_uart.hpp"
#include "stonksos/stdio.hpp"

static Aux aux;
static MiniUart s_mu;
static IRQ<IRQRegs> s_irq(IRQ_ADDRESS);

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
	Stdio::printf("Interrupt Error: %s - %d, ESR: %X, Address: %X\n", 
		entry_error_messages[type], type, esr, address);	
}

extern "C" void handle_irq(){
	u32 irq;

#if RPI_VERSION == 4
	irq = s_irq.get_as_ptr()->irq0_pending_0;
	//irq = s_irq.get_as_ptr()->irq0_pending_0;
#endif

#if RPI_VERSION == 3
	irq = s_irq.get_as_ptr()->irq0_pending_1;
	//irq = IRQ::get_irq_regs_ptr()->irq0_pending_1;
#endif

	if (irq & AUX_IRQ){
		irq &= ~AUX_IRQ;
		while((aux.get_aux_regs_ptr()->mu_iir & 4) == 4){
			s_mu.uart_send(s_mu.uart_recv());
		}
	}
	else {
		Stdio::printf("Unknown pending irq: %x\r\n", irq);	
	}
}

template <class T>
void IRQ<T>::enable_interrupt_controller(void){
#if RPI_VERSION == 4
	//s_irq.get_irq_regs_ptr()->irq0_enable_0 = AUX_IRQ;	
	s_irq.get_as_ptr()->irq0_enable_0 = AUX_IRQ;
#endif

#if RPI_VERSION == 3
	//s_irq.get_irq_regs_ptr()->irq0_enable_1 = AUX_IRQ;	
	s_irq.get_as_ptr()->irq0_enable_1 = AUX_IRQ;
#endif
}

template <class T>
void IRQ<T>::init_vectors(void){
	asm volatile("adr x0, vectors; "
		     "msr vbar_el1, x0");
}

template <class T>
void IRQ<T>::irq_enable(void){
	asm volatile("msr daifclr, #2");
}

template <class T>
void IRQ<T>::irq_disable(void){
	asm volatile("msr daifset, #2");
}

template <class T>
void IRQ<T>::initialize(void){
	s_irq.init_vectors();
	s_irq.enable_interrupt_controller();
	s_irq.irq_enable();
}

template class IRQ<IRQRegs>;
