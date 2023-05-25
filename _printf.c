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
		buffer = malloc2(*line, args, 512);
		buffer[0] = '\0';
		_strcat(buffer, &((*(args->pwd))[4]));
		len = _strlen(buffer);
		while (line_c[i] && line_c[i] != ' ')
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
				while (line_c[i] && line_c[i] != '/' && line_c[i] != ' ')
					buffer[len++] = line_c[i++];
				i--;
			}
			i++;
		}
		buffer[len] = '\0';
		if (access(buffer, X_OK) == 0)
		{
			_strcat(buffer, &line_c[i]);
			free(*line);
			*line = buffer;
		}
	}
}

/**
 * malloc2 - handle malloc2
 * @line: input
 * @args: parameter of type para
 * @size: the size
 *
 * Return: the buffer
 */

char *malloc2(char *line, para *args, int size)
{
	char *buffer = malloc(size);

	if (!buffer)
	{
		free(line);
		free_exit(args);
	}
	return (buffer);
}

/**
* token - function to return the splitted number of token
* @line: the string to be splitted
* @delim: the delim used to split the string
* Return:number of token splitted
*/
int token(char *line, char *delim)
{
	int n_token = 0;
	char *str_token = _strtok(line, delim);

	while (str_token)
	{
		str_token = _strtok(NULL, delim);
		n_token++;
	}
	return (n_token);
}
