#pragma once
#include <stdbool.h>
#include <stdarg.h>
#include "stonksos/string.hpp"
#include "mini_uart.hpp"
#include "types.hpp"

#define EOF (-1)

class Stdio 
{
private:
	MiniUart mu;
	String str_o;
	bool print(const char *, size_t);
	i32 vsprintf(char *, const char *, va_list);

public:
	MiniUart *get_miniuart_object(void) { return &mu; }
	String *get_string_object(void) { return &str_o; }

	i32 printf(const char *, ...);
	i32 sprintf(char *buf, const char *fmt, ...);
	char putchar(char);
	i32 puts(const char *);	
};
