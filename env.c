#include "main.h"

/**
 * _realloc - change buffer size and copy the content of the buffer.
 * @ptr: old buffer.
 * @old_size: the buffer old size.
 * @new_size: the buffer new size.
 * Return: the new buffer.
*/

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *buffer;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	buffer = malloc(new_size);
	if (buffer == NULL)
	{
		if (ptr)
			free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (buffer);
	for (i = 0; i < old_size && i < new_size; i++)
	{
		buffer[i] = ((char *) ptr)[i];
	}

	free(ptr);
	return (buffer);
}

/**
 * _atoi - convert a string to an int.
 * @str: string.
 * Return: the numbers in string
 */

int _atoi(char *str)
{
	int i = (_strlen(str) - 1), j, num = 0, power = 1;

	for (j = 0; j <= i; j++)
	{
		if (str[i - j] > 47 && str[i - j] < 58)
		{
			num += (str[i - j] - 48) * power;
			power *= 10;
		}
		else
			return (-1);
	}
	return (num);
}

/**
 * _get_env - get specific environmental variable.
 * @envp: array of environmental variable.
 * @env: the variable to search for.
 * @len: length of the variable to search for.
 * Return: the variable or NULL if not found.
*/

char *_get_env(char **envp, char *env, int len)
{
	int i;

	for (i = 0; envp[i] != NULL; i++)
	{
		if (_strncmp(envp[i], env, len) == 0)
			return (&envp[i][len + 1]);
	}
	return (NULL);
}

/**
 * _env - check if the input is env and provide it if it is.
 * @args: parameter of type args.
 * Return: 1 input = env, 0 input != env.
*/
int _env(para *args)
{
	int i;

	if (rev_cmp(args->line, "env"))
	{
		for (i = 0; args->envp[i] != NULL; i++)
		{
			write(1, args->envp[i], _strlen(args->envp[i]));
			write(1, "\n", 1);
		}
		return (1);
	}
	return (0);
}

/**
 * handle_realloc - handle realloc and free args in case it fail.
 * @args: parameter of type args.
 * @buffer: buffer to be reallocted
 * @buffer_size: the buffer size.
 * @extra: the size to be added.
 * @max: the number to comapre the buffer size with
 * Return: the buffer
 */
char *handle_realloc(para *args, char *buffer, int *buffer_size,
int extra, int max)
{
	if (*buffer_size <= max)
	{
		buffer = _realloc(buffer, *buffer_size, *buffer_size + extra);
			if (buffer == NULL)
			{
				free_exit(args);
			}
		*buffer_size += extra;
	}
	return (buffer);
}
