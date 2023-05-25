#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * split_string - splits and returns an array of strings
 * @str: the string to return
 * @delimiter: the delimiter to check
 * Return: an array of strings
 */
char **split_string(char *str, char *delimiter)
{
	char *tok, **toks = NULL;
	int n = 0;

	toks = malloc(sizeof(char *) * 1024);
	if (toks == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	if (toks == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	tok = strtok(str, delimiter);
	while (tok)
	{
		toks[n] = tok;
		tok = strtok(NULL, delimiter);
		n++;
	}
	toks[n] = NULL;
	return (toks);
}

/**
 * main - entry point
 *
 * Return: 0 (SUCCESS)
 */

int main(void)
{
	size_t command_size = 0;
	ssize_t num;
	pid_t pid;
	int status;
	char *command = NULL, **toks = NULL;

	while (1)
	{
		write(1, "$ ", 2);
		num = getline(&command, &command_size, stdin);
		if (num == EOF)
		{
			perror("getline");
			exit(EXIT_SUCCESS);
		}
		command[num - 1] = '\0';
		toks = split_string(command, " ");
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (execve(command, toks, NULL) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else
			wait(&status);
	}
	printf("Exit\n");
	free(toks);
	return (0);
}
