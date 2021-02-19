#include "mini_uart.hpp"
#include "utils.hpp"
#include "stonksos/stdio.hpp"

/*  StonksOS kernel entry point */
extern "C" [[noreturn]] void kernel_main(){
	
	//Stdio stdio;
	MiniUart mu;
    
	g_stdio.puts("\n\nWelcome to StonksOS.\n");
	g_stdio.printf("Working at exception level: %d\n", kernel::get_el());

	while(1){
		char c = mu.uart_recv();
		g_stdio.putchar(c);
	}
}
