#include "mini_uart.hpp"
#include "stonksos/stdio.hpp"

/*  StonksOS kernel entry point */
extern "C" [[noreturn]] void kernel_main(){
	
	Stdio stdio;
	MiniUart mu;

	stdio.printf("\r\n\r\n\r\nWelcome to StonksOS.");
	stdio.puts("\r\n\r\n\r\nWelcome to StonksOS.\r\n");

	while(1){
		char c = mu.uart_recv();
		stdio.puts(&c);
	}
}
