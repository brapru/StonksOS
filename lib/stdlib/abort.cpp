#include "stonksos/stdio.hpp"
#include "stonksos/stdlib.hpp"

__attribute__((__noreturn__))
void Stdlib::abort(void)
{
#if defined(__is_libk)
	//TODO: add proper kernel panic
	get_stdio_object()->printf("kernel: panic: abort()\n");
#else
	//TODO: abnormally terminate process as if by SIGABRT
	get_stdio_object()->printf("abort()\n");
#endif
	while (1) { };
	__builtin_unreachable();
}
