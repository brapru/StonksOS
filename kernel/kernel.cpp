#include "mini_uart.hpp"
#include "utils.hpp"
#include "stonksos/stdio.hpp"
#include "irq.hpp"

/*  StonksOS kernel entry point */
extern "C" [[noreturn]] void kernel_main(){
	
	//Stdio stdio;
	MiniUart mu;
	Stdio::init_miniuart(&mu);

	irq_init_vectors();
	IRQ::enable_interrupt_controller();
	irq_enable();
	
	Stdio::printf("\nValue of mu lcr is: %x\n", mu.get_aux_object()->get_aux_regs_ptr()->mu_lcr);
	Stdio::printf("\nValue of mu mcr is: %x\n", mu.get_aux_object()->get_aux_regs_ptr()->mu_mcr);
	Stdio::printf("\nValue of mu ier is: %x\n", mu.get_aux_object()->get_aux_regs_ptr()->mu_ier);
	Stdio::printf("\nValue of mu iir is: %x\n", mu.get_aux_object()->get_aux_regs_ptr()->mu_iir);
	Stdio::printf("\nValue of mu enables is: %x\n", mu.get_aux_object()->get_aux_regs_ptr()->enables);
	Stdio::printf("\nValue of mu control is: %x\n", mu.get_aux_object()->get_aux_regs_ptr()->mu_control);
	Stdio::printf("\nValue of mu baud is: %x\n", mu.get_aux_object()->get_aux_regs_ptr()->mu_baud_rate);
	
	Stdio::puts("\n\nWelcome to StonksOS.\n");
	Stdio::printf("Working at exception level: %d\n", kernel::get_el());

	while(1){
		//char c = mu.uart_recv();
		//stdio.putchar(c);
	}
}
