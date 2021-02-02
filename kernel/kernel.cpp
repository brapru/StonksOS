#include "mini_uart.hpp"

/*  StonksOS kernel entry point */
extern "C" [[noreturn]] void kernel_main(){
	uart_init();
	uart_send_string("\r\nWelcome to StonksOS.\r\n");

	while(1){
		uart_send(uart_recv());
	}
}
