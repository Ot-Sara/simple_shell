#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "env.h"
/**
 * _getenv - return the value of a spesific key
 * @name: the key to manipulate
 * Return: char*
 */

char *_getenv(const char *name)
{
	int l = 0;
	char *key;

	while (environ[l])
	{
		key = strtok(environ[l], "=");
		if (strcmp(name, key) == 0)
			return (strtok(NULL, "\n"));
		l++;
	}
	return (NULL);
}
/**
 * get_command - finds the path and stick it to the command
 * @cmd: the command entered by the user
 * Return: the whole path
 */

char *get_command(char *cmd)
{
	char *P = _getenv("PATH");
	char *tok;
	char *command;
	struct stat st;

	tok = strtok(P, ":");
	while (tok)
	{
		command = malloc(strlen(tok) + strlen(cmd) + 2);
		strcpy(command, tok);
		strcat(command, "/");
		strcat(command, cmd);

		if (stat(command, &st) == 0)
			return (command);

		free(command);
		tok = strtok(NULL, ":");
	}
	return (NULL);
}

/**
 * split_string - splits and returns an array of strings
 * @str: the string to return
 * @delimiter: the delimiter to check
 * Return: an array of strings
 */

char **split_string(char *str, char *delimiter)
{
	char *tok, **toks;
	int n = 0;

	toks = malloc(sizeof(char *) * 1024);
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
 * main - Entry point
 * @ac: the number of items in av
 * @av: an array of strings
 * @env: the environment path
 * Return: 0 (SUCCESS)
 */

int main(int ac, char **av, char **env)
{
	char *buffer = NULL;
	size_t buffer_size = 0;
	char *cmd;
	char **args;
	pid_t pid;
	int status, n;
	(void)ac;
	(void)av;
	while (1)
	{
		write(1, "#cisfun$ ", 9);
		n = getline(&buffer, &buffer_size, stdin);
		if (n == -1)
		{
			write(1, "\n", 1);
			exit(1);
		}
		args = split_string(buffer, " \t\n");
		if (strcmp(args[0], "exit") == 0)
			exit(0);
		pid = fork();
		if (pid == 0)
		{
			cmd = get_command(args[0]);
			if (cmd == NULL)
			{
				fprintf(stderr, "%s: command not found\n", args[0]);
				exit(127);
			}
			else if (execve(cmd, args, env) == -1)
			{
				fprintf(stderr, "%s: execution error\n", args[0]);
				exit(EXIT_FAILURE);
			}
			exit(0);
		}
		else
			wait(&status);
	}
	return (0);
}
