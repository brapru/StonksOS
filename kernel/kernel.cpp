#include "mini_uart.hpp"
#include "utils.hpp"
#include "stonksos/stdio.hpp"
#include "irq.hpp"

/*  StonksOS kernel entry point */
extern "C" [[noreturn]] void kernel_main(){
	
	Stdio stdio;
	MiniUart mu;
	IRQ irq;

	irq_init_vectors();
	irq.enable_interrupt_controller();
	irq_enable();

	stdio.puts("\n\nWelcome to StonksOS.\n");
	stdio.puts("Working at exception level: ");
	mu.uart_hex(kernel::get_el());
	stdio.puts("\n");

	while(1){
		char c = mu.uart_recv();
		stdio.putchar(c);
	}
}
