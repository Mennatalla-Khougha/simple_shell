#include "main.h"

char *space(char **line)
{
    int i = 0, j = 0;
    char *ptr = malloc(_strlen(*line));
    while((*line)[i] == ' ' && (*line)[i])
        i++;
    while((*line)[i])
    {
        if((*line)[i] == ' ')
        {
            ptr[j] = ' ';
            j++;

            while((*line)[i] == ' ')
                i++;
        }
        ptr[j] = (*line)[i];
        i++;
        j++;
    }
    ptr[j] = '\0';
    free(*line);
    *line = ptr;
    return (ptr);
}

int rev_cmp(char *s1, char *s2)
{
	int len1, len2, i;

	len1 = _strlen(s1);
	len2 = _strlen(s2);
	if(len2 > len1)
		return (0);
	len1--;
	for(i = len2 - 1; i >= 0; i--)
	{
		if(s1[len1] != s2[i])
			return (0);
		len1--;
	}
	return(1);
}

void _echo(char **ptr, int val, int pid, char **envp)
{
    char *num;
    char *str = _strdup(*ptr);

    if (str[0] == '$')
    {
        ++str;
        if (!strcmp(str, "$"))
        {
            num = malloc(10);
            tostring(num, pid);
            *ptr = num;
        }
        else if (!strcmp(str, "?"))
        {
            num = malloc(4);
            tostring(num, val);
            *ptr = num;
        }
        else if ( _get_env(envp, str) != NULL)
        {
            *ptr = _get_env(envp, str);
        }
        else
        {
            *ptr = "\0";
        }
    }
}
