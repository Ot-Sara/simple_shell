#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

/**
 * split_string - splits and returns an array of strings
 * @str: the string to return
 * Return: an array of strings
 */
char **split_string(char *str)
{
	char *tok, **toks;
	int n = 0;

	toks = malloc(sizeof(char *) * 1024);
		if (toks == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
	while (*str != '\0')
	{
		while (*str == ' ')
			str++;
		if (*str == '\0')
			break;
		n++;
		tok = str;
		while (*str != ' ' && *str != '\0')
			str++;
		if (*str != '\0')
			*str = '\0';
		toks[n - 1] = tok;
	}
	return (toks);
}
/**
 * main - Entry point
 *
 * Return: 0 (SUCCESS)
 */

int main(void)
{
	size_t command_size = 0;
	ssize_t num;
	pid_t pid;
	int status;
	char *command = NULL;
	char **toks = NULL;

	while (1)
	{
		write(1, "#cisfun$ ", 9);
	num = getline(&command, &command_size, stdin);
	if (num == EOF)
	{
		perror("getline");
		break;
	}
	command[num - 1] = '\0';
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		toks = split_string(command);
		if (execve(toks[0], toks, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(&status);
	}
	free(toks);
	free(command);
	return (0);
}
