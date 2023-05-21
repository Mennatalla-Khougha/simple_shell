#include "main.h"

ssize_t _getline(char **line, size_t *n, int stream)
{
    size_t buffer_size = 8, i = 0;
    ssize_t read_line;
    char *buffer;

    if (line == NULL || n == NULL)
        return (-1);
    buffer = malloc(buffer_size);
    if (buffer == NULL)
        return (-1);
    if (*line)
        free(*line);
    while ((read_line = read(stream, buffer + i, 1)) > 0)
    {
        i++;
        if (buffer[i-1] == '\n' || buffer[i-1] == ';')
            break;
        if (i >= buffer_size)
        {
            buffer = _realloc(buffer, buffer_size, buffer_size + 8);
            if (buffer == NULL)
            {
                free(buffer);
                return (-1);
            }
            buffer_size += 8;
        }
    }
    if (read_line < 0 || (!read_line && !i))
    {
        free (buffer);
        return (-1);
    }
    if(read_line != 8)
        buffer[i] = '\0';
    *line = buffer;
    *n = buffer_size;
    return (i);
}