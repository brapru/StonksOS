#include "stonksos/string.hpp"
#include "types.hpp"

size_t String::strlen(const char *str)
{
	size_t len = 0;
	while (str[len])
	    len++;
	return len;
}
