#include "stonksos/stdio.hpp"
#include "stonksos/stdlib.hpp"

__attribute__((__noreturn__))
void Stdlib::abort(void)
{
#if defined(__is_libk)
	//TODO: add proper kernel panic
	g_stdio.printf("kernel: panic: abort()\n");
#else
	//TODO: abnormally terminate process as if by SIGABRT
	g_stdio.printf("abort()\n");
#endif
	while (1) { };
	__builtin_unreachable();
}
