#include "main.h"

int _env(char **env, char *ptr) 
{
    int i;

	if (rev_cmp(ptr, "env"))
	{
    	for (i = 0; env[i] != NULL; i++) 
    	{
        	write(1, env[i], _strlen(env[i]));
			write(1, "\n", 1);
    	}
		return (1);
	}
    return 0;
}

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	p = malloc(new_size);
	if (p == NULL)
		return (NULL);
	if (ptr == NULL)
	{
		return (p);
	}
	for (i = 0; i < old_size && i < new_size; i++)
	{
		p[i] = ((char *) ptr)[i];
	}

	free(ptr);
	return (p);
}
