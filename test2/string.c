#include "main.h"

/**
 * _strlen - determine the length of a string.
 * @s: a string of char.
 * Return: the length of a string.
 */

int _strlen(char *s)
{
	int i = 0;

	while (s[i] != 0)
	{
		i++;
	}

	return (i);
}

/**
 * _strcat - function to concatenates two strings.
 * @dest: string to be cocatenated.
 * @src: string to be concatenated to.
 * Return: a pointer to the resulting string.
 */

char *_strcat(char *dest, char *src)
{
	int destlen = 0;
	int srclen = 0;

	while (dest[destlen] != '\0')
		destlen++;

	while (src[srclen] != '\0')
	{
		dest[destlen] = src[srclen];
		srclen++;
		destlen++;
	}

	dest[destlen] = '\0';
	return (dest);
}

/**
 * _strdup - return a pointer to space contain a copy of the string given
 * @str: string given.
 * Return: a pointer to a dupicate string.
 */

char *_strdup(char *str)
{
	char *s;
	int i;

	if (str == NULL)
		return (NULL);

	s = malloc(sizeof(char) * (_strlen(str) + 1));

	if (s == NULL)
		return (NULL);

	for (i = 0; i < _strlen(str); i++)
	{
		s[i] = str[i];
	}

	return (s);
}

int _strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	do {
		if (*s1 != *s2++)
			return (*(unsigned char *)s1 - *(unsigned char *)--s2);
		if (*s1++ == 0)
			break;
	} while (--n != 0);
	return (0);
}
