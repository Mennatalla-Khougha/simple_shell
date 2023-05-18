#include "main.h"

void _exceve(char *ptr, int arg_c, char *argv, char *buff)
{
    int i = 0;
    char **arg_v; 
    char *env[] = {NULL};
    pid_t id;
    id = fork();
    
    if (!id)
    {
        arg_v = malloc(8 * (arg_c + 1));
        if(buff)
        {
            arg_v[0] = buff;
            i++;
            ptr += _strlen(ptr) + 1;
        }
        for (; i < arg_c; i++)
        {
            arg_v[i] = ptr;
            ptr += _strlen(ptr) + 1;
        }
        arg_v[i] = NULL;
        if (execve(arg_v[0], arg_v, env) == -1)
            perror(argv);
        free(arg_v);
        exit(-1);
    }
    wait(NULL);
}

char *get_path(char **envp)
{
    int i;

    for (i = 0; envp[i] != NULL; i++) {
        if (strncmp(envp[i], "PATH=", 5) == 0) {
          break;
        }
    }
    return (&envp[i][5]);
}
int main(int __attribute__ ((unused)) argc, char **argv, char **envp)
{
    size_t n = 0;
    ssize_t read;
    char *line = NULL, *ptr, *token, *env = strdup(get_path(envp)), *path_token, *path_v;
    int arg_c, path_c = 0, i;
/*     printf("%s\n", env); */
    path_v = env;
    path_token = strtok(env, ":");
    while (path_token)
    {
        path_token = strtok(NULL, ":");
        path_c++;
    }
    env = path_v;

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
        if(ptr[0] == '/')
            _exceve(ptr, arg_c, argv[0], NULL);
        else
        {
            for(i = 0; i < path_c; i++)
            {
            char buffer[1024] = "";
            strcat(buffer, path_v);
            strcat(buffer, "/");
            strcat(buffer, ptr);
            if (access(buffer, X_OK) == 0) 
            {
                _exceve(ptr, arg_c, argv[0], buffer);
                break;
            }
            path_v += _strlen(path_v) + 1;
            }
            path_v = env;
            if(i == path_c){
                perror(argv[0]);
            }
        }
    }
    free(line);
    return (0);
}
