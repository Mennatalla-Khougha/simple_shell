#include "main.h"

int main(int __attribute__ ((unused)) x, char *y[])
{
	char *line = NULL, *token, *p, **argv, *env[] = {NULL};
	size_t n = 0;
	ssize_t read;
	int argc, i;
	pid_t id;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(1, "=> ", 3);
		read = getline(&line, &n, stdin);
		if (read == -1)
			break;
		if (line[read -1] == '\n')
			line[read - 1] = '\0';
		p = line;
		token = strtok(line, " ");
		argc = 0;
		while (token)
		{
			token = strtok(NULL, " ");
			argc++;
		}
		id = fork();
		if (!id)
		{
			argv = malloc(8 * (argc + 1));
			for (i = 0; i < argc; i++)
			{
				argv[i] = p;
				p += _strlen(p) + 1;
			}
			argv[i] = NULL;
			if (execve(argv[0], argv, env) == -1)
				perror(y[0]);
		}
		else
			wait(NULL);
	}
	return (0);
}
