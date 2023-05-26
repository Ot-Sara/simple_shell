#include "main.h"

/**
 * inter - returns true if shell is in interactive mode
 * @data: struct address
 * Return: 1 if true, 0 otherwize
 */

int inter(data_t *data)
{
	return (isatty(STDIN_FILENO) && data->readfd <= STDERR_FILENO);
}

/**
 * del - checks if character is delimiter
 * @c: the char to check
 * @delimiter: the delimiter string
 * Return: 1 if true, 0 otherwise
 */

int del(char c, char *delimiter)
{
	for (; *delimiter; delimiter++)
	{
		if (*delimiter == c)
			return (1);
	}
	return (0);
}

/**
 * isalpha - checks for alphabetic  character
 * @c: the character to input
 * Return: 1 if true, 0 otherwise
 */

int isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * atoi - converts a string to an integer
 * @str: the string to be converted
 * Return: converted number if true, 0 otherwise
 */

int atoi(char *str)
{
	int symbol = 1, f = 0;
	unsigned int result = 0;

	while (*str != '\0' && f != 2)
	{
		if (*str == '-')
			symbol *= -1;
		if (*str >= '0' && *str <= '9')
		{
			f = 1;
			result *= 10;
			result += (*str - '0');
		}
		else if (f == 1)
			f = 2;
		str++;
	}
	return (symbol == -1 ? -result : result);
}
