#include "main.h"

/**
 **memset - fills memory with a constant byte
 *@str: the pointer to the memory area
 *@byt: the byte to fill *str with
 *@num: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *memset(char *str, char byt, unsigned int num)
{
	unsigned int a;

	for (a = 0; a < num; a++)
		str[a] = byt;
	return (str);
}

/**
 * free_s - frees a string of strings
 * @ss: string of strings
 */

void free_s(char **ss)
{
	char **i = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(a);
}

/**
 * realloc - reallocates a block of memory
 * @p: pointer to previous malloc'ated block
 * @o_size: byte size of previous block
 * @n_size: byte size of new block
 *
 * Return: a pointer.
 */
void *realloc(void *p, unsigned int o_size, unsigned int n_size)
{
	char *i;

	if (!p)
		return (malloc(n_size));
	if (!n_size)
		return (free(p), NULL);
	if (n_size == o_size)
		return (p);

	i = malloc(n_size);
	if (!i)
		return (NULL);

	o_size = o_size < n_size ? o_size : n_size;
	while (o_size--)
		i[o_size] = ((char *)p)[o_size];
	free(p);
	return (i);
}
