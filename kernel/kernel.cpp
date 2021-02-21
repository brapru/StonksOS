#include "mini_uart.hpp"
#include "utils.hpp"
#include "stonksos/stdio.hpp"
#include "irq.hpp"

/*  StonksOS kernel entry point */
extern "C" [[noreturn]] void kernel_main(){
	
	Stdio stdio;
	MiniUart mu;

	irq_init_vectors();
	IRQ::enable_interrupt_controller();
	irq_enable();
	
	stdio.printf("\nValue of mu lcr is: %x\n", mu.get_aux_object()->get_aux_regs_ptr()->mu_lcr);
	stdio.printf("\nValue of mu mcr is: %x\n", mu.get_aux_object()->get_aux_regs_ptr()->mu_mcr);
	stdio.printf("\nValue of mu ier is: %x\n", mu.get_aux_object()->get_aux_regs_ptr()->mu_ier);
	stdio.printf("\nValue of mu iir is: %x\n", mu.get_aux_object()->get_aux_regs_ptr()->mu_iir);
	stdio.printf("\nValue of mu enables is: %x\n", mu.get_aux_object()->get_aux_regs_ptr()->enables);
	stdio.printf("\nValue of mu control is: %x\n", mu.get_aux_object()->get_aux_regs_ptr()->mu_control);
	stdio.printf("\nValue of mu baud is: %x\n", mu.get_aux_object()->get_aux_regs_ptr()->mu_baud_rate);
	
	stdio.puts("\n\nWelcome to StonksOS.\n");
	stdio.printf("Working at exception level: %d\n", kernel::get_el());

	while(1){
		//char c = mu.uart_recv();
		//stdio.putchar(c);
	}
}
