#include "stonksos/stdio.hpp"
#include "stonksos/string.hpp"
#include "types.hpp"
#include <stdarg.h>

static Stdio s_stdio;
static String s_string;

bool Stdio::print(const char *data, size_t length)
{
        const unsigned char *bytes = reinterpret_cast<const unsigned char *>(data);
        for (size_t i = 0; i < length; i++)
            if (putchar(bytes[i]) == EOF)
                return false;
        return true;
}

void Stdio::init_miniuart(MiniUart *m)
{
	s_stdio.mu = m;
}

//adapted source code from
//https://github.com/torvalds/linux/blob/master/arch/x86/boot/printf.c

static inline i32 isdigit(i32 c)
{
        return '0' <= c && c <= '9';
}

static i32 skip_atoi(const char **s)
{
	i32 i = 0;

	while (isdigit(**s))
		i = i * 10 + *((*s)++) - '0';
	return i;
}

#define ZEROPAD	1		/* pad with zero */
#define SIGN	2		/* unsigned/signed long */
#define PLUS	4		/* show plus */
#define SPACE	8		/* space if plus */
#define LEFT	16		/* left justified */
#define SMALL	32		/* Must be 32 == 0x20 */
#define SPECIAL	64		/* 0x */

#define __do_div(n, base) ({ \
i32 __res; \
__res = ((u64) n) % (unsigned) base; \
n = ((u64) n) / (unsigned) base; \
__res; })

static char *number(char *str, long num, i32 base, i32 size, i32 precision,
		    i32 type)
{
	static const char digits[17] = "0123456789ABCDEF";

	char tmp[66];
	char c, sign, locase;
	i32 i;

	locase = (type & SMALL);
	if (type & LEFT)
		type &= ~ZEROPAD;
	if (base < 2 || base > 16)
		return NULL;
	c = (type & ZEROPAD) ? '0' : ' ';
	sign = 0;
	if (type & SIGN) {
		if (num < 0) {
			sign = '-';
			num = -num;
			size--;
		} else if (type & PLUS) {
			sign = '+';
			size--;
		} else if (type & SPACE) {
			sign = ' ';
			size--;
		}
	}
	if (type & SPECIAL) {
		if (base == 16)
			size -= 2;
		else if (base == 8)
			size--;
	}
	i = 0;
	if (num == 0)
		tmp[i++] = '0';
	else
		while (num != 0)
			tmp[i++] = (digits[__do_div(num, base)] | locase);
	if (i > precision)
		precision = i;
	size -= precision;
	if (!(type & (ZEROPAD + LEFT)))
		while (size-- > 0)
			*str++ = ' ';
	if (sign)
		*str++ = sign;
	if (type & SPECIAL) {
		if (base == 8)
			*str++ = '0';
		else if (base == 16) {
			*str++ = '0';
			*str++ = ('X' | locase);
		}
	}
	if (!(type & LEFT))
		while (size-- > 0)
			*str++ = c;
	while (i < precision--)
		*str++ = '0';
	while (i-- > 0)
		*str++ = tmp[i];
	while (size-- > 0)
		*str++ = ' ';
	return str;
}

i32 Stdio::vsprintf(char *buf, const char *fmt, va_list args)
{
	i32 len;
	u64 num;
	i32 i, base;
	char *str;
	const char *s;

	i32 flags;		/* flags to number() */

	i32 field_width;	/* width of output field */
	i32 precision;		/* min. # of digits for integers; max
				   number of chars for from string */
	i32 qualifier;		/* 'h', 'l', or 'L' for integer fields */

	for (str = buf; *fmt; ++fmt) {
		if (*fmt != '%') {
			*str++ = *fmt;
			continue;
		}

		flags = 0;
	      repeat:
		++fmt;	
		switch (*fmt) {
		case '-':
			flags |= LEFT;
			goto repeat;
		case '+':
			flags |= PLUS;
			goto repeat;
		case ' ':
			flags |= SPACE;
			goto repeat;
		case '#':
			flags |= SPECIAL;
			goto repeat;
		case '0':
			flags |= ZEROPAD;
			goto repeat;
		}

		field_width = -1;
		if (isdigit(*fmt))
			field_width = skip_atoi(&fmt);
		else if (*fmt == '*') {
			++fmt;
			field_width = va_arg(args, i32);
			if (field_width < 0) {
				field_width = -field_width;
				flags |= LEFT;
			}
		}

		precision = -1;
		if (*fmt == '.') {
			++fmt;
			if (isdigit(*fmt))
				precision = skip_atoi(&fmt);
			else if (*fmt == '*') {
				++fmt;
				precision = va_arg(args, i32);
			}
			if (precision < 0)
				precision = 0;
		}

		qualifier = -1;
		if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L') {
			qualifier = *fmt;
			++fmt;
		}

		base = 10;

		switch (*fmt) {
		case 'c':
			if (!(flags & LEFT))
				while (--field_width > 0)
					*str++ = ' ';
			*str++ = (unsigned char)va_arg(args, i32);
			while (--field_width > 0)
				*str++ = ' ';
			continue;

		case 's':
			s = va_arg(args, char *);
			len = s_string.strnlen(s, precision);

			if (!(flags & LEFT))
				while (len < field_width--)
					*str++ = ' ';
			for (i = 0; i < len; ++i)
				*str++ = *s++;
			while (len < field_width--)
				*str++ = ' ';
			continue;

		case 'p':
			if (field_width == -1) {
				field_width = 2 * sizeof(void *);
				flags |= ZEROPAD;
			}
			str = number(str,
				     (u64)va_arg(args, void *), 16,
				     field_width, precision, flags);
			continue;

		case 'n':
			if (qualifier == 'l') {
				long *ip = va_arg(args, long *);
				*ip = (str - buf);
			} else {
				i32 *ip = va_arg(args, i32 *);
				*ip = (str - buf);
			}
			continue;

		case '%':
			*str++ = '%';
			continue;

		case 'o':
			base = 8;
			break;

		case 'x':
			flags |= SMALL;
		case 'X':
			base = 16;
			break;

		case 'd':
		case 'i':
			flags |= SIGN;
		case 'u':
			break;

		default:
			*str++ = '%';
			if (*fmt)
				*str++ = *fmt;
			else
				--fmt;
			continue;
		}
		if (qualifier == 'l')
			num = va_arg(args, u64);
		else if (qualifier == 'h') {
			num = (u16)va_arg(args, i32);
			if (flags & SIGN)
				num = (i16)num;
		} else if (flags & SIGN)
			num = va_arg(args, i32);
		else
			num = va_arg(args, u32);
		str = number(str, num, base, field_width, precision, flags);
	}
	*str = '\0';
	return str - buf;
}

i32 Stdio::sprintf(char *buf, const char *fmt, ...)
{
	va_list args;
	i32 i;

	va_start(args, fmt);
	i = s_stdio.vsprintf(buf, fmt, args);
	va_end(args);
	return i;
}

i32 Stdio::printf(const char *fmt, ...)
{
	char printf_buf[1024];
	va_list args;
	i32 printed;

	va_start(args, fmt);
	printed = s_stdio.vsprintf(printf_buf, fmt, args);
	va_end(args);

	s_stdio.print(printf_buf, printed);

	return printed;
}

char Stdio::getchar(void)
{
	char c = s_stdio.mu->uart_recv();
	return c;
}

char *Stdio::gets(char *buf, i32 size)
{
	char tmp;
	char *str = buf;
	while (--size > 0 && (tmp = s_stdio.getchar()) != '\n')
	{
		*str++ = tmp;
	}
	*str = '\0';
	return buf;
}


char Stdio::putchar(char ic)
{
	#if defined(__is_libk)
	if (ic == '\n')
	    s_stdio.mu->uart_send('\r');
	s_stdio.mu->uart_send(ic);
	#else
	//TODO: implement write system call here
	#endif

	return ic;
}

int Stdio::puts(const char *str)
{
	return s_stdio.printf("%s", str);
}
