#include "stonksos/string.hpp"
#include "types.hpp"

void* String::memcpy(void* __restrict dstptr, const void* __restrict srcptr, size_t size)
{
	unsigned char *dst = reinterpret_cast<unsigned char *>(dstptr);
	const unsigned char *src = reinterpret_cast<const unsigned char *>(srcptr);
	for (size_t i = 0; i < size; i++)
	    dst[i] = src[i];
	return dstptr;
}
