#include "main.h"

/**
 * _printf - print.
 * @format: the format
 *
 * Return: the number of chars
 */

int _printf(const char *format, ...)
{
	unsigned int i, len = 0;
	va_list args;

	if (format == NULL)
		return (-1);
	va_start(args, format);
	for (i = 0; format[i]; i++)
	{
		if (format[i] != '%')
		{
			len += p_char(format[i]);
			continue;
		}
		if (i++ == strlen(format) - 1)
			return (-1);
		len += specifier(format[i], args);
	}
	va_end(args);
	return (len);
}
