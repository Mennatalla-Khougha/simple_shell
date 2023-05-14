#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

int main(void)
{
    int is_terminal = isatty(fileno(stdin));
    char *line = NULL;
    size_t n = 0;
    ssize_t read;
    char *delim = " \n";
    char *token;
    char *p;
    int argc, i;
    char **argv;
    char *env[] = {NULL};
    pid_t id;

    while (1)
    {
        if (is_terminal) {
            printf("=> ");
        }
        if (is_terminal) {
            read = getline(&line, &n, stdin);
        } else {
            read = getdelim(&line, &n, '\0', stdin);
        }
        if (read == -1) {
            break;
        }
        p = line;
        token = strtok(line, delim);
        argc = 0;
        while(token){
            token = strtok(NULL, delim);
            argc++;
        }
        id = fork();
        if (!id) {
            argv = malloc(8 * (argc + 1));
            for(i=0; i<argc; i++){
                argv[i] = p;
                p += strlen(p) + 1;
            }
            argv[i] = NULL;
            if (execve(argv[0], argv, env) == -1) {
                printf("error, unknown command.\n");
            }
        } else {
            wait(NULL);
        }
    }
    return 0;
}