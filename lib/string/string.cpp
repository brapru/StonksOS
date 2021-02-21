#include "stonksos/string.hpp"
#include "types.hpp"

using namespace String;

int String::memcmp(const void *aptr, const void *bptr, size_t size)
{
	const unsigned char *a = reinterpret_cast<const unsigned char *>(aptr);
	const unsigned char *b = reinterpret_cast<const unsigned char *>(bptr);
	for (size_t i = 0; i < size; i++)
	{
		if (a[i] < b[i])
		    return -1;
		else if (b[i] < a[i])
		    return 1;
	}
	return 0;
}

void* String::memcpy(void* __restrict dstptr, const void* __restrict srcptr, size_t size)
{
	unsigned char *dst = reinterpret_cast<unsigned char *>(dstptr);
	const unsigned char *src = reinterpret_cast<const unsigned char *>(srcptr);
	for (size_t i = 0; i < size; i++)
	    dst[i] = src[i];
	return dstptr;
}

void* String::memmove(void *dstptr, const void* srcptr, size_t size)
{
	unsigned char *dst = reinterpret_cast<unsigned char *>(dstptr);
	const unsigned char *src = reinterpret_cast<const unsigned char *>(srcptr);
	if (dst < src)
	{
		for (size_t i = 0; i < size; i++)
		    dst[i] = src[i];
	}
	else
	{
		for (size_t i = size; i != 0; i--)
		    dst[i - 1] = src[i - 1];
	}
	return dstptr;
}

void* String::memset(void *bufptr, i32 value, size_t size)
{
	unsigned char *buf = reinterpret_cast<unsigned char *>(bufptr);
	for (size_t i = 0; i < size; i++)
	    buf[i] = static_cast<unsigned char>(value);
	return bufptr;
}

size_t String::strlen(const char *str)
{
	size_t len = 0;
	while (str[len])
	    len++;
	return len;
}

size_t String::strnlen(const char *str, size_t maxlen)
{
	const char *tmp;
	size_t n;

	for (tmp = str, n = 0; *tmp && n < maxlen; tmp++, n++)
	    ;
	return n;
}
