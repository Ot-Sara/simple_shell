#include "main.h"

/**
 * strcpy - copies a string
 * @destination: the destination
 * @source: the source
 * Return: a pointer to destination
 */

char *strcpy(char *destination, char *source)
{
	int a = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[a])
	{
		destination[a] = source[a];
		a++;
	}
	destination[a] = 0;
	return (destination);
}

/**
 * strdup - duplicates a string
 * @string: the string to duplicate
 * Return: pointer to the duplicated string
 */

char *strdup(const char *string)
{
	size_t len;
	char *p;

	if (string == NULL)
		return (NULL);
	len = strlen(string);
	p = malloc(sizeof(char) * (len + 1));
	if (p == NULL)
		return (NULL);
	strcpy(p, string);
	return (p);
}

/**
 * puts - prints an input string
 * @string: the string to be printed
 */

void puts(char *string)
{
	int a = 0;

	if (!string)
		return;
	while (string[a] != '\0')
	{
		_putchar(string[a]);
		a++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: the character to print
 * Return: 1 on success, -1 on error
 */

int _putchar(char c)
{
	static int a;
	static char buffer[W_BUF_SIZE]

	if (c == BUF_FLUSH || a >= W_BUF_SIZE)
	{
		write(1, buffer, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buffer[a++] = c;
	return (1);
}
