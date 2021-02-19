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
	i32 printf(const char *, ...);
	i32 sprintf(char *buf, const char *fmt, ...);
	char putchar(char);
	i32 puts(const char *);	
};

extern Stdio g_stdio;
