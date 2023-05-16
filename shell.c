#include "main.h"

void _exceve(char *ptr, int arg_c, char *argv)
{
    int i = 0;
    char **arg_v = malloc(sizeof(8 * (arg_c + 1)));
    char *env[] = {NULL};

    for (i = 0; i < arg_c; i++)
    {
        arg_v[i] = ptr;
        ptr += _strlen(ptr) + 1;
    }
    if (execve(arg_v[0], arg_v, env) == -1)
        perror(argv);
    exit(-1);
}

int main(int __attribute__ ((unused)) argc, char **argv)
{
    size_t n = 0;
    ssize_t read;
    char *line = NULL, *ptr, *token;
    int arg_c;
    pid_t id;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(1, "=> ", 3);
        read = getline(&line, &n, stdin);
        if (read == -1)
            return (-1);
        if (line[read - 1] == '\n')
            line[read - 1] = '\0';
        ptr = line;
        token = strtok(line, " ");
        arg_c = 0;
        while (token)
        {
            token = strtok(NULL, " ");
            arg_c++;
        }
        id = fork();
        if (!id)
            _exceve(ptr, arg_c, argv[0]);
        wait(NULL);
    }
    return (0);
}
