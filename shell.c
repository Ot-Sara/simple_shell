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
	char *str = NULL;
	size_t str_size = 0;
	ssize_t num;
	char **toks;
	pid_t pid;
	int status;
	(void)ac;
	(void)av;

	while (1)
	{
		write(1, "#cisfun$ ", 9);
		num = getline(&str, &str_size, stdin);
		if (num == -1)
		{
			write(1, "\n", 1);
			exit(1); }
		str[num - 1] = '\0';
		toks = split_string(str, " ");
		if (strcmp(toks[0], "exit") == 0)
			exit(0);
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE); }
		if (pid == 0)
		{
			str = get_command(toks[0]);
			if (str)
				execve(str, toks, env);
			else
			exit(0); }
		else
			wait(&status);
		free(toks);
	}
	free(str);
	return (0);
}
