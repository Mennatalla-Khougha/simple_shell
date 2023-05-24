 #include "main.h"

/**
 * _command_ - handle the path of the command passed.
 * @args: parameter of type para
 * Return: 0 or 127
 */
int _command_(para *args)
{
	int i;
	char *path = args->path;

	if (_exit_(args) || cd(args))
		return (args->status);
	if (args->line[0] == '/')
	{
		if (access(args->line, X_OK) == 0)
		{
			if (!_env(args))
				return (_exceve(args, args->line));
			return (0);
		}
	_printf("%s: %i: %s: not found\n", args->shell_name, args->count, args->line);
	}
	else
	{
		for (i = 0; i < args->n_path; i++)
		{
			char buffer[500] = "";

			_strcat(buffer, path);
			_strcat(buffer, "/");
			_strcat(buffer, args->line);
			if (access(buffer, X_OK) == 0)
			{
				if (!_env(args))
					return (_exceve(args, buffer));
				return (0);
			}
			path += _strlen(path) + 1;
		}
	_printf("%s: %i: %s: not found\n", args->shell_name, args->count, args->line);
	}
	args->status = 127;
	return (127);
}

/**
* _exceve - function executing the command
* @args: parameter of type para
* @buff: input buffer
* Return: the exit status.
*/
int _exceve(para *args, char *buff)
{
	int i;
	char **arg_v, *env[] = {NULL}, *line = args->line;
	pid_t id = fork();

	if (!id)
	{
		if (rev_cmp(args->line, "pwd"))
		{
			arg_v = malloc(16);
			if (arg_v == NULL)
				exit(255);
			arg_v[0] = args->line;
			arg_v[1] = NULL;
		}
		else
		{
			arg_v = malloc(8 * (args->n_token + 1));
			if (arg_v == NULL)
				exit(255);
			for (i = 0; i < args->n_token; i++)
			{
				arg_v[i] = line;
				line += _strlen(line) + 1;
			}
			arg_v[i] = NULL;
		}
		execve(buff, arg_v, env);
		free(arg_v);
		exit(args->status);
	}
	wait(&(args->status));
	args->status = WEXITSTATUS(args->status);
	return (args->status);
}

/**
 * _exit_ - handle if exit the shell and the exit status.
 * @args: parameter of type para
 * Return: 0 success, 1 failure
*/
int _exit_(para *args)
{
int len;

if (!_strcmp(args->line, "exit"))
{
	if (args->n_token > 1)
	{
	len = _strlen(args->line) + 1;
	args->status = _atoi(args->line + len);
	}
	if (args->status != -1)
	{
		if (args->line)
			free(args->line);
		if (args->path)
			free(args->path);
		if (args->pwd)
			free(*(args->pwd));
		if (args->old_pwd)
			free(args->old_pwd);
		exit(args->status);
	}
	_printf("%s: %i: exit: Illegal number: %s\n",
	args->shell_name, args->count, args->line + len);
	args->status = 2;
	return (1);
}
	return (0);
}

/**
* token - function to return the splitted number of token
* @line: the string to be splitted
* @delim: the delim used to split the string
* Return:number of token splitted
*/
int token(char *line, char *delim)
{
	int n_token = 0;
	char *str_token = _strtok(line, delim);

	while (str_token)
	{
		str_token = _strtok(NULL, delim);
		n_token++;
	}
	return (n_token);
}

/**
* main - The entry point of the program
* @argc: number of argument to the program
* @argv: array of argument to the program
* @envp: array of environmental variable
* Return: 0;
*/
int main(int argc, char **argv, char **envp)
{
	para args;
	int  arrow = 1;

	args.line = NULL;
	args.envp = envp;
	args.path = _strdup(_get_env(envp, "PATH", 4));
	args.pwd = get_PWD(&args);
	args.old_pwd = _strdup(&((*args.pwd)[4]));
	args.shell_name = argv[0];
	args.count = 0;
	args.status = 0;
	args.file = 0;
	args.pid = (int)getpid();
	if (!args.path || !args.pwd || !args.old_pwd)
		free_exit(&args);
	args.n_path = token(args.path, ":");
	if (argc > 1)
	{
		args.file = open(argv[1], O_RDONLY);
		if (args.file == -1)
		{
			_printf("%s: 0: cannot open %s: No such file\n", argv[0], argv[1]);
			exit(2);
		}
	}
while (1)
{
	args.count++;
	if (isatty(STDIN_FILENO) && arrow && !args.file)
		write(1, "=> ", 3);
	arrow = input(&args, arrow);
	if (handle_input(&args))
		continue;
	args.n_token = token(args.line, " ");
	if (_command_(&args) == 255)
		free_exit(&args);
}
return (0);
}
