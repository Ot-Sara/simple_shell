#include "shell.h"
#include <stdio.h>
#include <stdio.h>

/**
 * main - entry
 * @argc: argc
 * @args: args
 * @env: environement
 * Return: 0
 */

int main(int argc, char *args[], char **env)
{
	char *buff = NULL, *prompt = "$ ";
	size_t buff_size = 0;
	ssize_t bytes;
	pid_t wpid;
	int wstatus;
	bool from_pipe = false;
	struct stat statbuf;
	(void)argc;
	(void)args;

	while (1 && !from_pipe)
	{
		if (isatty(STDIN_FILENO) == 0)
			from_pipe = true;
		write(STDOUT_FILENO, prompt, 2);
		bytes = getline(&buff, &buff_size, stdin);
		if (bytes == -1)
		{
			perror("ERROR getline");
			free(buff);
			exit(EXIT_FAILURE);
		}
		if (buff[bytes - 1] == '\n')
			buff[bytes - 1] = '\n';
		wpid = fork();
		if (wpid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (wpid == 0)
			_execute(buff, &statbuf, env);
		if (waitpid(wpid, &wstatus, 0) == -1)
		{
			perror("wait");
			exit(EXIT_FAILURE);
		}
	}
	free(buff);
	return (0);
}

/**
 * _execute - executes
 * @arguments: first arg
 * @statbuf: second arg
 * @env: environement
 * Return: int
 */

int _execute(char *arguments, struct stat *statbuf, char **env)
{
	int argc;
	char **argv;
	char *exe;

	argv = split_string(arguments, " ", &argc);
	if (!check_file_status(argv[0], statbuf))
	{
		perror("Error (file status)");
		exit(EXIT_FAILURE);
	}
	execve(argv[0], argv, env);

	perror("execve");
	exit(EXIT_FAILURE);
}

/**
 * check_file_status - checks the file
 * @pathname: pathname
 * @statbuf: statbuf
 * Return: bool
 */

bool check_file_status(char *pathname, struct stat *statbuf)
{
	int stat_return;

	stat_return = stat(pathname, statbuf);

	if (stat_return == 0)
	{
		return (true);
	}
	return (false);

}
