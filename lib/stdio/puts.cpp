#include "stonksos/stdio.hpp"

int Stdio::puts(const char *str)
{
	return printf("%s", str);
}
