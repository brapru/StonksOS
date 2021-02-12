#include "stonksos/stdio.hpp"
#include "stonksos/string.hpp"
#include "types.hpp"
#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>

bool Stdio::print(const char* data, size_t length) {
	const unsigned char* bytes = (const unsigned char *)data;
	for (size_t i = 0; i < length; i++)
		if (putchar(bytes[i]) == EOF)
			return false;
	return true;
}

i32 Stdio::printf(const char* __restrict fmt, ...) {
	va_list parameters;
	va_start(parameters, fmt);

	i32 written = 0;
	while (*fmt != '\0')	
	{
		size_t maxrem = INT_MAX - written;

		if (fmt[0] != '%' || fmt[1] == '%') {
			if (fmt[0] == '%')
				fmt++;
			size_t amount = 1;
			while (fmt[amount] && fmt[amount] != '%')
				amount++;
			if (maxrem < amount) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(fmt, amount))
				return -1;
			fmt += amount;
			written += amount;
			continue;
		}
		
		const char *fmt_begun_at = fmt++;

		if (*fmt == 'c') {
			fmt++;
			char c = static_cast<char>(va_arg(parameters, i32));
			if (!maxrem) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(&c, sizeof(c)))
				return -1;
			written++;
		} else if (*fmt == 's') {
			fmt++;
			const char* str = va_arg(parameters, const char*);
			size_t len = get_string_object()->strlen(str);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(str, len))
				return -1;
			written += len;
		}
		else 
		{
			fmt = fmt_begun_at;
			size_t len = get_string_object()->strlen(fmt);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(fmt, len))
				return -1;
			written += len;
			fmt += len;
		}
	}

	va_end(parameters);
	return written;
}
