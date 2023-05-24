#include "main.h"

/**
 * cd - change directory.
 * @args: parameter of type para
 * Return: 0, 1
 */
int cd(para *args)
{
	char *dest, *line = args->line;

	if (!_strcmp(line, "cd"))
	{
		if (args->n_token == 1)
			dest = _get_env(args->envp, "HOME", 4);
		else
		{
			line += 3;
			if (!_strcmp(line, "-"))
			{
				dest = args->old_pwd;
				write(1, dest, _strlen(dest));
				write(1, "\n", 1);
			}
			else
				dest = line;
		}
		if (chdir(dest) == -1)
		{
		_printf("%s: %i: cd: an't cd to %s\n", args->shell_name, args->count, dest);
		args->status = 2;
		}
		else
		{
			free(args->old_pwd);
			args->old_pwd = _strdup(&((*(args->pwd))[4]));
			if (!args->old_pwd)
				free_exit(args);
			change_pwd(args);
			args->status = 0;
		}
		return (1);
	}
	return (0);
}

/**
 * change_pwd - change the pwd
 * @args: parameter of type para.
 */
void change_pwd(para *args)
{
	char buffer[250];
	char *pwd = _malloc(args, 256);

	getcwd(buffer, 250);
	pwd[0] = '\0';
	_strcat(pwd, "PWD=");
	_strcat(pwd, buffer);
	free(*(args->pwd));
	*(args->pwd) = pwd;
}

/**
 * get_PWD - get the pwd from the env
 * @args: parameter of type para.
 * Return: pointer to the pwd
 */
char **get_PWD(para *args)
{
	int i;
	char *pwd = NULL;

	for (i = 0; args->envp[i] != NULL; i++)
	{
		if (_strncmp(args->envp[i], "PWD", 3) == 0)
		{
			pwd = _strdup(args->envp[i]);
			args->envp[i] = pwd;
			return (&(args->envp[i]));
		}
	}
	return (NULL);
}

/**
 * free_exit - free arguments before exit
 * @args: parameter of type para
 */
void free_exit(para *args)
{
	if (args->line)
		free(args->line);
	if (args->path)
		free(args->path);
	if (*(args->pwd))
		free(*(args->pwd));
	if (args->old_pwd)
		free(args->old_pwd);
	exit(255);
}

/**
 * _malloc - handling malloc and freeing exit if malloc failed.
 * @args: parameter of type para
 * @size: the size to be maloced
 * Return: the buffer.
 */
char *_malloc(para *args, int size)
{
	char *buff = malloc(size);

	if (!buff)
		free_exit(args);
	return (buff);
}
