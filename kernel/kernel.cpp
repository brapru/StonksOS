#include "mini_uart.hpp"

/*  StonksOS kernel entry point */
extern "C" [[noreturn]] void kernel_main(){
	
	MiniUart mu;
	mu.uart_send_string("\r\nWelcome to StonksOS.\r\n");

	while(1){
		mu.uart_send(mu.uart_recv());
	}
}
