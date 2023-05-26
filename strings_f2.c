#include "main.h"

/**
 * strlen - returns the length of a string
 * @str: the string to check the length of
 * Return: an integer
 */

int strlen(char *str)
{
	int length = 0;

	if (str == NULL)
		return (0);
	while (str[length] != '\0')
		length++;
	return (length);
}

/**
 * strcmp - compares two strings
 * @str1: the first string
 * @str2: the second string
 * Return: 0 success
 */

int strcmp(char *str1, *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return (*str1, *str2);
}

/**
 * starts - checks if pattern starts with text
 * @text: the string to search
 * @pattern: the substring to find
 * Return: address of the next char of text or NULL
 */

char *starts(const char *text, const char *pattern)
{
	char *text;

	while (*pattern && *pattern == *text)
	{
		pattern++;
		text++;
	}
	if (*pattern == '\0')
		return (text);
	else
		return (NULL);
}

/**
 * strcat - concatenates two strings
 * @destination: the destination buffer
 * @source: the source buffer
 * Return: pointer to destination buffer
 */

char *strcat(char *destination, const char *source)
{
	char *p = destination;

	while (*destination)
		destination++;
	while (*source)
	{
		*destination = *source;
		destination++;
		source++;
	}
	*destination = '\0';
	return (p);
}
