#include "stonksos/stdio.hpp"
#include "types.hpp"

#if defined(__is_libk)
#include "mini_uart.hpp"
#endif

char Stdio::putchar(char ic)
{
	#if defined(__is_libk)
	if (ic == '\n')
	    g_miniuart.uart_send('\r');
	g_miniuart.uart_send(ic);
	#else
	//TODO: implement write system call here
	#endif

	return ic;
}
