#include "mbox.hpp"
#include "mini_uart.hpp"
#include "utils.hpp"
#include "stonksos/stdio.hpp"
#include "irq.hpp"

/*  StonksOS kernel entry point */
extern "C" [[noreturn]] void kernel_main(){
	
	MiniUart mu;
	Stdio::init_miniuart(&mu);

	IRQ::initialize();
	
	Stdio::puts("\n\nWelcome to StonksOS.\n");
	Stdio::printf("Working at exception level: %d\n", kernel::get_el());
	
	Mailbox::mbox_get_mac();

	while(1){}
}
