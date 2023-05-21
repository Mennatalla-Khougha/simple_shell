#include "main.h"

void tostring(char *str, int num)
{
    int i, len = 0, n;
 
    n = num;
    if (!n)
    {
        str[0] = '0';
        str[1] = '\0';
        return;
    }
    while (n)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        str[len - (i + 1)] = num % 10 + '0';
        num /= 10;
    }
    str[len] = '\0';
}

char *_get_env(char **envp, char *env)
{
    int i, len = _strlen(env);

    for (i = 0; envp[i] != NULL; i++) {
        if (_strncmp(envp[i], env, len) == 0) {
           return (&envp[i][len + 1]);
        }
    }
    return (NULL);
}
