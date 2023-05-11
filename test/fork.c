#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

/**
  * main - The entry point of the program
  * Return: int .
 */
int main(void)
{
	int is_terminal = isatty(fileno(stdin));

	while (1)
	{
		if (is_terminal)
			printf("=> ");
		char *line = NULL;
		size_t n = 0;
		ssize_t read;

		if (is_terminal)
			read = getline(&line, &n, stdin);
		else
			read = getdelim(&line, &n, '\0', stdin);
		if (read == -1)
			break;
		char *delim = "\n";
		char *token;

		token = strtok(line, delim);
		int id = fork();

		if (!id)
		{
			char *argv[] = {token, NULL};
			char *env[] = {NULL};

			if (execve(token, argv, env) == -1)
				printf("error, unknown command.\n");
		}
		else
			wait(NULL);
	}
	return (0);
}
