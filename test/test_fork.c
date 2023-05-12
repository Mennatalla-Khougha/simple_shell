#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

int main(void)
{
    pid_t pid;
    size_t n = 0, argc = 0, i;
    ssize_t read;
    char *line = NULL, *delim = " \n", *token, **argv, *ptr;

    while (1) 
    {
        if (isatty(STDIN_FILENO))
        {
            write(1, "=> ", 3);
        }
        read = getline(&line, &n, stdin);
        if (read == -1)
               break;
        ptr = line;
        if (line[read -1] == '\n')
            line[read - 1] = '\0';
        token = strtok(line, delim);

        while (token)
        {
            token = strtok(NULL, delim);
            argc++;
        }
        argv = malloc(8 * (argc + 1));
        for (i = 0; i < argc; i++)
        {
            argv[i] = ptr;
            ptr += strlen(ptr) + 1;
        }
        argv[i] = NULL;
        pid = fork();
        if (pid == -1)
        {
            perror("something went wrong");
            return 1;
        }
        else if (pid == 0)
        {
            if (execve(argv[0], argv, NULL) == -1)
                perror("something went wrong");
        }
        else
        {
            wait(NULL);
        }
    }
    free(argv);
    free(line);
    return (0);
}
