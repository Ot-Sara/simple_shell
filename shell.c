#include "main.h"

/**
 * hsh - main shell loop
 * @data: the parameter & return info struct
 * @av: the argument vector from main()
 * Return: 0 on success, 1 on error, or error code
 */

int hsh(data_t *data, char **av)
{
	ssize_t i = 0;
	int built_ins = 0;

	while (i != -1 && built_ins != -2)
	{
		clear_data(data);
		if (inter(data))
			puts("$ ");
		_eputchar(BUF_FLUSH);
		i = get_in(data);
		if (i != -1)
		{
			set_data(data, av);
			built_ins = builtin_finder(data);
			if (built_ins == -1)
				cmd_finder(data);
		}
		else if (inter(data))
			_putchar('\n');
		free_data(data, 0);
	}
	write_hist(data);
	free_data(data, 1);
	if (!inter(data) && data->status)
		exit(data->status);
	if (built_ins == -2)
	{
		if (data->err_n == -1)
			exit(data->status);
		exit(data->err_n);
	}
	return (built_ins);
}

/**
 * builtin_finder - finds a builtin command
 * @data: the parameter & return data struct
 * Return: -1 if builtin not found, 0 if builtin executed
 * successfully, 1 if builtin found but not successful,
 * -2 if builtin signals exit()
 */

int builtin_finder(data_t *data)
{
	int a, built_in = -1;
	builtin_table builtin_tab[] = {
		{"exit", my_exit},
		{"env", my_env},
		{"help", my_help},
		{"hist", my_hist},
		{"setenv", my_setenv},
		{"unsetenv", my_unsetenv},
		{"cd", my_cd},
		{"alias", my_alias},
		{NULL, NULL}
	};

	for (a = 0; builtin_tab[a].type; a++)
		if (strcmp(data->argv[0], builtin_tab[a].type) == 0)
		{
			data->l_count++;
			built_in = builtin_tab[a].func(data);
			break;
		}
	return (built_in);
}

/**
 * cmd_finder - finds a command in PATH
 * @data: the parameter & return data struct
 * Return: void
 */

void cmd_finder(data_t *data)
{
	char *path = NULL;
	int a, c;

	data->path = data->argv[0];
	if (data->lcount_flag == 1)
	{
		data->l_count++;
		data->lcount_flag = 0;
	}
	for (a = 0, c = 0; data->arg[i]; i++)
		if (!del(data->arg[i], " \t\n"))
			c++;
	if (!c)
		return;

	path = path_finder(data, getenv(data, "PATH="), data->argv[0]);
	if (path)
	{
		data->path = path;
		c_fork(data);
	}
	else
	{
		if ((inter(data) || getenv(data, "PATH=") ||
		data->argv[0][0] == '/') && is_command(data, data->argv[0]))
			c_fork(data);
		else if (*(data->arg) != '\n')
		{
			data->status = 127;
			error_p(data, "not found\n");
		}
	}
}

/**
 * c_fork - forks a an exec thread to run cmd
 * @data: the parameter & return data struct
 * Return: void
 */

void c_fork(data_t *data)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error:");
		return;
	}
	if (pid == 0)
	{
		if (execve(data->path, data->argv, get_env(data)) == -1)
		{
			free_data(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(data->status));
		if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
			if (data->status == 126)
				error_p(data, "Permission denied\n");
		}
	}
}
