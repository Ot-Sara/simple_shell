#include "main.h"

/**
 * **strtow_f1 - splits a string into words
 * @string: the input string
 * @delimiter: the delimiter string
 * Return: a pointer to an array of strings, or NULL otherwise
 */

char **strtow_f1(char *string, char *delimiter)
{
	int a = 0, b = 0, c = 0, d = 0, n_word = 0;
	char **toks;

	if (string == NULL || string[0] == '\0')
		return (NULL);
	if (!delimiter)
		delimiter = " ";
	for (a = 0; string[a] != '\0'; a++)
		if (!del(string[a], delimiter) && (del(string[a + 1],
				delimiter) || !string[a + 1]))
			n_word++;
	if (n_word == 0)
		return (NULL);
	toks = malloc(sizeof(char *) * (n_word + 1));
	if (!toks)
		return (NULL);
	for (a = 0, b = 0; b < n_word; b++)
	{
		while (del(string[a], delimiter))
			a++;
		c = 0;
		while (del(string[a + c], delimiter) && string[a + c] != '\0')
			c++;
		toks[b] = malloc(sizeof(char) * (c + 1));
		if (!toks[b])
		{
			for (c = 0; c < b; c++)
				free(toks[c]);
			free(toks);
			return (NULL); }
		for (d = 0; d < c; d++)
			toks[b][d] = string[a++];
		toks[b][d] = '\0'; }
	toks[b] = NULL;
	return (toks); }

/**
 * **strtow_f2 - splits a string into words
 * @string: the input string
 * @delimiter: the delimiter
 * Return: a pointer to an array of strings, or NULL otherwise
 */

char **strtow_f2(char *string, char delimiter)
{
	int a = 0, b = 0, c = 0, d = 0, n_word = 0;
	char **toks;

	if (string == NULL || string[0] == '\0')
		return (NULL);
	for (a = 0; string[a] != '\0'; a++)
		if ((string[a] != delimiter && string[a + 1] == delimiter) ||
				(string[a] != delimiter && !string[a + 1]) || string[a + 1] == delimiter)
			n_word++;
	if (n_word == 0)
		return (NULL);
	toks = malloc(sizeof(char *) * (n_word + 1));
	if (!toks)
		return (NULL);
	for (a = 0, b = 0; b < n_words; b++)
	{
		while (string[a] == delimiter && string[a] != '\0')
			a++;
		c = 0;
		while (string[a + c] != delimiter && string[a + c] != '\0'
				&& string[a + c] != delimiter)
			c++;
		toks[b] = malloc(sizeof(char) * (c + 1));
		if (!toks[b])
		{
			for (c = 0; c < b; c++)
				free(toks[c]);
			free(toks);
			return (NULL); }
		for (d = 0; d < c; d++)
			toks[b][d] = string[a++];
		toks[b][d] = '\0'; }
	toks[b] = NULL;
	return (toks); }
