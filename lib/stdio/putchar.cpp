#include "stonksos/stdio.hpp"
#include "types.hpp"

#if defined(__is_libk)
#include "mini_uart.hpp"
#endif

i32 Stdio::putchar(i32 ic)
{
	#if defined(__is_libk)
	char c = static_cast<char>(ic);
	get_miniuart_object()->uart_send_string(&c);
	#else
	//TODO: implement write system call here
	#endif

	return ic;
}
