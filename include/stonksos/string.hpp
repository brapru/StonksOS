#pragma once
#include "types.hpp"

class String 
{
public:
	i32 memcmp(const void*, const void*, size_t);
	void *memcpy(void* __restrict, const void* __restrict, size_t);
	void *memmove(void*, const void*, size_t);
	void *memset (void*, i32, size_t);
	size_t strlen(const char*);
	size_t strnlen(const char *, size_t);
};

extern String g_string;
