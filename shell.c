#include <stdio.h>
#include <unistd.h>

/**
 * main - Entry point
 * @ac: the number of items in av
 * @av: an array of strings
 * Return: 0 (SUCCESS)
 */

int main()
{
	size_t size_BUF = 0;
	int num = 0;
	char *BUF = NULL;

	write(1, "~ ", 2);
	num = getline(&BUF, &size_BUF, stdin);
	if (num == EOF)
		perror("getline");
	BUF[num - 1] = '\0';
	printf("%s\n", BUF);
	return (0);
}
