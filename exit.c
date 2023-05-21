#include "main.h"

int _exit_(char *line, char *argv, int argc, int count, char *env, int k)
{
    int n;

    if(!strcmp(line, "exit")){
        if(argc > 1){
            n = _strlen(line) + 1;
            k = _atoi(line + n);
        }
        if(k != -1){
            free(env);
            free(line);
            exit(k);
        }
        else
            _printf("%s: %i: exit: Illegal number: %s\n", argv, count, line + n);
        return (1);
    }
    return (0);
}