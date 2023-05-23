#include "main.h"

/**
* _strtok - split the string into tokens.
* @str: string to be divided.
* @delim: delimiter to split the string by.
* Return: token.
*/
char *_strtok(char *str, const char *delim)
{
	static char *last;
	char *token;

	if (str != NULL)
	{
		last = str;
	}
	else if (last == NULL)
	{
		return (NULL);
	}
	token = last;
	while (*last != '\0')
	{
		if (*delim == *last)
		{
			*last = '\0';
			last++;
			return (token);
		}
		last++;
	}
	last = NULL;
	return (token);
}

/**
* _strdup - return a pointer to space contain a copy of the string given
 * @str: string given.
 * Return: a pointer to a duplicate string.
*/
char *_strdup(char *str)
{
	char *copy;
	int i;

	copy = malloc(_strlen(str) + 1);
	if (!copy)
		return (NULL);
	for (i = 0; i < _strlen(str); i++)
	{
		copy[i] = str[i];
	}
	return (copy);
}

/**
* _strncmp - compare the first n bytes of str1 and str2.
 * @str1: the first string to be compared.
 * @str2: the second string to be compared.
 * @n: the number of bytes to be compared.
 * Return: 0 if the strings are equal.
*/
int _strncmp(const char *str1, const char *str2, size_t n)
{
	while (n-- && (*str1 != '\0' || *str2 != '\0'))
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	return (0);
}

/**
* _strchr - locate a character in a string.
 * @str: string.
 * @c: character to be located.
 * Return: a pointer to the first occurrence of c. or null if not found.
 */
char *_strchr(char *str, char c)
{
	int i = 0;

	while (i < _strlen(str))
	{
		if (str[i] == c)
		{
			return (str + i);
		}
		i++;
	}
	return (NULL);
}
/**
* _strncat - concatenate one sting to another.
 *@dest: the string to be added to.
 *@src: the string to be added.
 *@n: number of bytes from src.
*Return: the resulting concatenated string.
*/
char *_strncat(char *dest, char *src, int n)
{
	int dest_len = _strlen(dest), i = 0;

	while (i < n && src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}
