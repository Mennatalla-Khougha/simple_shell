#include "main.h"

void _exceve(char *ptr, int arg_c, char *buff)
{
    int i;
    char **arg_v; 
    char *env[] = {NULL};
    pid_t id;
    id = fork();
    
    if (!id)
    {
        arg_v = malloc(8 * (arg_c + 1));
        for (i = 0; i < arg_c; i++)
        {
            arg_v[i] = ptr;
            ptr += _strlen(ptr) + 1;
        }
        arg_v[i] = NULL;
        execve(buff, arg_v, env);
        free(arg_v);
        exit(-1);
    }
    wait(NULL);
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
    ssize_t read;
    char *line = NULL, *ptr, *token, *env = _strdup(get_path(envp)), *path_token, *path_v;
    int arg_c, path_c = 0, i, k, count = 0;
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
        count++;
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
        if(!strcmp(ptr, "exit")){
            k = 0;
            if(arg_c > 1){
                ptr += _strlen(ptr) + 1;
                k = _atoi(ptr);
            }
            if(k != -1){
                free(line);
                exit(k);
            }
            else{
                _printf("%s: %i: exit: Illegal number: %s\n", argv[0], count, ptr);
                continue;
            }
        }
        if(ptr[0] == '/')
        {
            if (access(ptr, X_OK) == 0)
                _exceve(ptr, arg_c, ptr);
            else
                _printf("%s: %i: %s: not found\n", argv[0], count, ptr);
        }
        else
        {
            for(i = 0; i < path_c; i++)
            {
                char buffer[1024] = "";
                _strcat(buffer, path_v);
                _strcat(buffer, "/");
                _strcat(buffer, ptr);
                if (access(buffer, X_OK) == 0) 
                {
                    _exceve(ptr, arg_c, buffer);
                    break;
                }
                path_v += _strlen(path_v) + 1;
            }
            path_v = env;
            if(i == path_c){
                _printf("%s: %i: %s: not found\n", argv[0], count, ptr);
            }
        }
    }
    return (0);
}
