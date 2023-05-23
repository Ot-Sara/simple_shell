#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

/**
 * _getenv - 
 * @name:
 * Return: the value
 */

char *_getenv(const char *name)
{
	int i = 0;
	char *key;
	extern char **environ;

	while (environ[i])
	{
		key = strtok(environ[i], "=");
		if (strcmp(name, key) == 0)
			return (strtok(NULL, "\n"));
		i++;
	}
	return (NULL);

}

/**
 * split_string - splits and returns an array of strings
 * @str: the string to return
 * Return: an array of strings
 */


char *get_command(char *command)
{
        char *path = _getenv("PATH");
        char *token;
        char *cmd_full;
        struct stat st;

        token = strtok(path, ":");
        while (token)
        {
                cmd_full = malloc(strlen(token) + strlen(command) + 2);
                strcpy(cmd_full, token);
                strcat(cmd_full, "/");
                strcat(cmd_full, command);

                if (stat(cmd_full, &st) == 0)
                        return (cmd_full);


                free(cmd_full);
                token = strtok(NULL, ":");
        }
        return (NULL);
}


char **split_string(char *str, char *del)
{
	char *tok, **toks;
	int n = 0;

	toks = malloc(sizeof(char *) * 1024);
		if (toks == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
	tok = strtok(str, del);

	while (tok)
	{
		toks[n] = tok;
		tok = strtok(NULL, del);
		n++;
	}
	toks[n] = NULL;
	return (toks);
}
/**
 * main - Entry point
 *
 * Return: 0 (SUCCESS)
 */

int main(int ac, char **av, char **env)
{

	size_t command_size = 0;
	ssize_t num;
	pid_t pid;
	int status;
	char *command = NULL;
	char **toks = NULL;
	char *cmd;

	(void)ac;
	(void)av;

	while (1)
	{
		write(1, "#cisfun$ ", 9);
	num = getline(&command, &command_size, stdin);
	if (num == -1)
	{
		perror("getline");
		exit(1);
	}
	command[num - 1] = '\0';
	toks = split_string(command, " \t\n");

	if (strcmp(toks[0], "exit") == 0)
		exit (0);

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		cmd = get_command(toks[0]);
		
		if (cmd)
			execve(cmd, toks, env);
		else
			printf("Command not found\n");
		exit(0);
	}
	else
		wait(&status);
	}
	return (0);
} 
