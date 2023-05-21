#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define STRING ((str) ? str : "(null)")

int _exceve(char *ptr, int arg_c, char *buff, int *status, char **envp);
char *get_path(char **envp);
int _printf(const char *format, ...);
int p_char(char c);
int p_string(char *s);
void p_number(int n);
int num_len(int n);
int specifier(char c, va_list args);
int _strlen(char *s);
char *_strcat(char *dest, char *src);
char *_strdup(char *str);
int _strncmp(const char *s1, const char *s2, size_t n);
int _atoi(char *s);
int _command_(char *ptr, char *argv, char *path, int argc,
int path_c, int count, char **envp, int *status);
int input(char **line, size_t *n);
int token(char *line, char *delim);
int _exit_(char *ptr, char *line, char *argv, int argc, int count);
char *space(char **line);
char *_strtok(char *s, const char *delim);
ssize_t _getline(char **line, size_t *n, int stream);
int _env(char **env, char *ptr);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void _echo(char **ptr, int val, int pid, char **envp);
int rev_cmp(char *s1, char *s2);
void tostring(char *str, int num);
char *_get_env(char **envp, char *env);

#endif
