#include "stonksos/string.hpp"
#include "types.hpp"

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
