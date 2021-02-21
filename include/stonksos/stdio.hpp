#pragma once
#include <stdbool.h>
#include <stdarg.h>
#include "stonksos/string.hpp"
#include "mini_uart.hpp"
#include "types.hpp"

class Stdio 
{
private:
	bool print(const char *, size_t);
	i32 vsprintf(char *, const char *, va_list);

public:
	MiniUart *mu;
	static void init_miniuart(MiniUart *);

	static i32 printf(const char *, ...);
	static i32 sprintf(char *buf, const char *fmt, ...);

	static char getchar(void);
	static char *gets(char *, i32);

	static char putchar(char);
	static i32 puts(const char *);	
};
