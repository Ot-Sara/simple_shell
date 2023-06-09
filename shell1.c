#include "main.h"

/**
 * _getenv - retrieves the value of an environment variable
 * @name: the name of the environment variable we want to
 * retrieve the value for
 * Return: the value
 */

char *getenv(const char *name)
{
	int i = 0;
	char *key;
	char *value;

	while (environ[i])
	{
		key = strtok(environ[i], "=");
		value = strtok(NULL, "=");
		if (strcmp(name, key) == 0)
			return (value);
		i++;
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
	char *P = getenv("PATH");
	char *tok;
	char *command;
	struct stat st;

	tok = strtok(P, ":");
	while (tok)
	{
		command = malloc(strlen(tok) + strlen(cmd) + 2);
		if (!command)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
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
	if (!toks)
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
	size_t command_size = 0;
	ssize_t num;
	pid_t pid;
	int status, execve_result;
	char *command = NULL, **toks = NULL;
	(void)ac;
	(void)av;

	while (1)
	{
		write(1, "#cisfun$ ", 9);
		num = getline(&command, &command_size, stdin);
		if (num == EOF)
		{
			perror("getline");
			exit(EXIT_FAILURE); }
		command[num - 1] = '\0';
		toks = split_string(command, " \t");
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
	free(command);
	return (0); }
