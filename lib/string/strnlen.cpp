#include "stonksos/string.hpp"
#include "types.hpp"

size_t String::strnlen(const char *str, size_t maxlen)
{
	const char *tmp;
	size_t n;

	for (tmp = str, n = 0; *tmp && n < maxlen; tmp++, n++)
	    ;
	return n;
}
