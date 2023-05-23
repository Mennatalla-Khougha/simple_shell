#include "main.h"

char *_strtok(char *s, const char *delim) {
    static char *last;
    char *token;

    if (s != NULL)
        last = s;
    else if (last == NULL)
        return (NULL);

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
    return token;
}
