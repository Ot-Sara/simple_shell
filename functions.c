#include "main.h"

/**
 * _getenv - return the value of a spesific key
 * @name: the key to manipulate
 * Return: char*
 */

char *_getenv(const char *name)
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
	char *P = _getenv("PATH");
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
			exit(EXIT_FAILURE); }
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
