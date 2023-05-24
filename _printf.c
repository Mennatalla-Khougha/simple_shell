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
		if ((int)i++ == _strlen((char *)format) - 1)
			return (-1);
		len += specifier(format[i], args);
	}
	va_end(args);
	return (len);
}

/**
 * handle_dots - handle the dots
 * @line: input
 * @args: parameter of type para
 */

void handle_dots(char **line, para *args)
{
	int i = 0, len;
	char *line_c = *line, *buffer;

	if (line_c[0] == '.')
	{
		buffer = malloc(512);
		if (buffer == NULL)
		{
			free(*line);
			free_exit(args);
		}
		buffer[0] = '\0';
		_strcat(buffer, &((*(args->pwd))[4]));
		len = _strlen(buffer);
		while (line_c[i])
		{
			if (line_c[i] == '.' && line_c[i + 1] == '.')
			{
				while (buffer[len - 1] != '/')
					buffer[(len--) - 1] = '\0';
				buffer[(len--) - 1] = '\0';
				i++;
			}
			else if (line_c[i] != '/' && line_c[i] != '.')
			{
				buffer[len++] = '/';
				while (line_c[i] && line_c[i] != '/')
					buffer[len++] = line_c[i++];
			}
			i++;
		}
		buffer[len] = '\0';
		if (access(buffer, X_OK) == 0)
		{
			free(*line);
			*line = buffer;
		}
	}
}
