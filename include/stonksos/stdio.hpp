#pragma once
#include <stdbool.h>
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

public:
	MiniUart *get_miniuart_object(void) { return &mu; }
	String *get_string_object(void) { return &str_o; }

	i32 printf(const char * __restrict, ...);
	i32 putchar(i32);
	i32 puts(const char *);	
};
