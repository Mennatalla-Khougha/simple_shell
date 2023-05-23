#include "main.h"

int _exit_(char *ptr, char *line, char *argv, int argc, int count)
{
    int k = 0;

    if(!strcmp(ptr, "exit")){
        if(argc > 1){
            ptr += _strlen(ptr) + 1;
            k = _atoi(ptr);
        }
        if(k != -1){
            free(line);
            exit(k);
        }
        else
            _printf("%s: %i: exit: Illegal number: %s\n", argv, count, ptr);
        return (1);
    }
    return (0);
}
