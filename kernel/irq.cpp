#include "entry.hpp"
#include "peripherals/aux.hpp"
#include "irq.hpp"
#include "mini_uart.hpp"
#include "stonksos/stdio.hpp"

static Aux aux;
static MiniUart s_mu;

void IRQ::initialize(void){
	IRQ::instance().init_vectors();
	IRQ::instance().enable_interrupt_controller();
	IRQ::instance().irq_enable();
}

void IRQ::enable_interrupt_controller(void){
	IRQ::instance().get_regmap()->irq0_enable_0 = AUX_IRQ;
}

void IRQ::init_vectors(void){
	asm volatile("adr x0, vectors; "
		     "msr vbar_el1, x0");
}

void IRQ::irq_enable(void){
	asm volatile("msr daifclr, #2");
}

void IRQ::irq_disable(void){
	asm volatile("msr daifset, #2");
}

extern "C" void show_invalid_entry_message(u32 type, u64 esr, u64 address){
	Stdio::printf("Interrupt Error: %s - %d, ESR: %X, Address: %X\n", 
		entry_error_messages[type], type, esr, address);	
}

extern "C" void handle_irq(){
	u32 irq = IRQ::instance().get_regmap()->irq0_pending_0;

	if (irq & AUX_IRQ){
		irq &= ~AUX_IRQ;
		while((aux.get_aux_regs_ptr()->mu_iir & 4) == 4){
			char c = Stdio::getchar();
			Stdio::putchar(c);
		}
	}
	else {
		Stdio::printf("Unknown pending irq: %x\r\n", irq);	
	}
}
