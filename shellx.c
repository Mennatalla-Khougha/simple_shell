#include "main.h"

int _exceve(char *ptr, int arg_c, char *buff, int *status, char **envp)
{
    int i, pid = (int)getpid();
    char **arg_v; 
    char *env[] = {NULL};
    pid_t id;
    id = fork();
    
    if (!id)
    {
        if(rev_cmp(ptr, "pwd")){
            arg_v = malloc(16);
            arg_v[0] = ptr;
            arg_v[1] = NULL;
        }
        else
        {
            arg_v = malloc(8 * (arg_c + 1));
            for (i = 0; i < arg_c; i++)
            {
                arg_v[i] = ptr;
                ptr += _strlen(ptr) + 1;
            }
            if(arg_c > 1 && !strcmp(arg_v[0], "echo"))
            {
                _echo(&arg_v[1], *status, pid, envp);
            }
            arg_v[i] = NULL;
        }
        execve(buff, arg_v, env);
        free(arg_v);
        exit(-1);
    }
    wait(status);
    return (WEXITSTATUS(*status));
}

char *get_path(char **envp)
{
    int i;

    for (i = 0; envp[i] != NULL; i++) {
        if (_strncmp(envp[i], "PATH=", 5) == 0) {
          break;
        }
    }
    return (&envp[i][5]);
}

int main(int __attribute__ ((unused)) argc, char **argv, char **envp)
{
    size_t n = 0;
    char *line = NULL, *ptr, *env = _strdup(get_path(envp));
    int arg_c, path_c = 0, count = 0, status = 0, arrow = 1;

    path_c = token(env, ":");

    while (1)
    {
        count++;
        if (isatty(STDIN_FILENO) && arrow)
            write(1, "=> ", 3);
        arrow = input(&line, &n);
        ptr = space(&line);
        arg_c = token(line, " ");
        if(_exit_(ptr, line, argv[0], arg_c, count))
        {
            status = 2;
            continue;
        }
        status = _command_(ptr, argv[0], env, arg_c, path_c, count, envp, &status);
    }
    return (0);
}