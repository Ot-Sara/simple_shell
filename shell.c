#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

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

	while (1)
	{
		printf("$ ");
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
		if (execlp(command, command, NULL) == -1)
		{
			perror("execlp");
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(&status);
	}
	printf("Exit\n");
	return (0);
}
