#include "mbox.hpp"
#include "mini_uart.hpp"
#include "utils.hpp"
#include "stonksos/stdio.hpp"

/*  StonksOS kernel entry point */
extern "C" [[noreturn]] void kernel_main(){
	
	MiniUart mu;
	Stdio::init_miniuart(&mu);
    
	Stdio::puts("\n\nWelcome to StonksOS.\n");
	Stdio::printf("Working at exception level: %d\n", kernel::get_el());

	Mailbox::mbox_get_mac();

	while(1){
		char c = Stdio::getchar();
		Stdio::putchar(c);
	}
}
