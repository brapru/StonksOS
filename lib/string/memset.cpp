#include "stonksos/string.hpp"
#include "types.hpp"

void* String::memset(void *bufptr, i32 value, size_t size)
{
	unsigned char *buf = reinterpret_cast<unsigned char *>(bufptr);
	for (size_t i = 0; i < size; i++)
	    buf[i] = static_cast<unsigned char>(value);
	return bufptr;
}
