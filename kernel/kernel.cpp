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

	stdio.puts("\n\nWelcome to StonksOS.\n");
	stdio.printf("Working at exception level: %d\n", kernel::get_el());

	while(1){
		//char c = mu.uart_recv();
		//stdio.putchar(c);
	}
}
