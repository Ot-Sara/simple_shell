#include "main.h"

/**
 * strncpy - copies a string
 * @destination: the destination string to be copied
 * @source: the source string
 * @n: the amount of characters to be copied
 * Return: the concatenated string
 */

char *strncpy(char *destination, const char *source, size_t n)
{
	char *str = destination;
	size_t ind;

	for (i = 0; i < n; i++)
	{
		if (source[ind] != '\0')
			destination[ind] = source[ind];
		else
			break;
	}
	for (; ind < n; ind++)
		destination[ind] = '\0';
	return (str);
}

/**
 * strncat - concatenates two strings
 *@destination: the first string
 *@source: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */

char *strncat(char *destination, const char *source, size_t n)
{
	char *str = destination;
	size_t dest_len = strlen(destination), ind;

	for (ind = 0; ind < n && source[ind] != '\0'; ind++)
		destination[dest_len + ind] = source[ind];
	destination[dest_len + ind] = '\0';
	return (str);
}

/**
 * strchr - locates a character in a string
 *@str: the string to be parsed
 *@c: the character to look for
 *Return: a pointer to the memory area
 */

char *strchr(const char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == c)
			return ((char *)str);
		str++;
	}
	if (c == '\0')
		return ((char *)str);
	return (NULL);
}
