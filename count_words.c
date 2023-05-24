#include "shell.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
/**
 * count_words - counts
 * @str: string
 * @sep: seperator
 * @size
 * Return: unsigned int
 */
unsigned int count_words(char *str, char *sep, unsigned int *size)
{
	unsigned int count = 0;
	bool start = false;
	int i = 0;

	while (str[i] != '\0')
	{
		if (is_separator(str[i], sep))
		{
			start = false;
		}
		else if (!start)
		{
			start = true;
			count++;
		}

		if (start)
		{
			size[count - 1]++;
		}

		i++;
	}
	return (count);
}

/**
 * is_separator - function
 * @c: c
 * @sep: separ
 * Return: bool
 */
bool is_separator(char c, char *sep)
{
	int i = 0;

	while (sep[i] != '\0')
	{
		if (sep[i] == c)
		{
			return (true);
		}
		i++;
	}
	return (false);
}
