#include "main.h"
/**
 * main - Entry point
 * @ac: the number of items in av
 * @av: an array of strings
 * @env: the environment path
 * Return: 0 (SUCCESS)
 */

int main(int ac, char **av, char **env)
{
	char *str = NULL, **toks = NULL, *command;
	size_t str_size = 0;
	ssize_t num;
	pid_t pid;
	int status, execve_result;
	(void)ac;
	(void)av;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 0)
			write(1, "#cisfun$ ", 9);
		num = getline(&str, &str_size, stdin);
		if (num == -1)
		{
			write(1, "\n", 1);
			exit(EXIT_SUCCESS); }
		str[num - 1] = '\0';
		toks = split_string(str, " ");
		if (strcmp(toks[0], "exit") == 0)
			exit(0);
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE); }
		else if (pid == 0)
		{
			command = get_command(toks[0]);
			if (command)
				execve_result = execve(command, toks, env);
			else if (execve_result == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE); }
			else
				exit(0); }
		else
			wait(&status);
		free(toks); }
	free(str);
	return (0); }
