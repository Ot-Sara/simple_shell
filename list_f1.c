#include "main.h"

/**
 * list_l - determines length of linked list
 * @j: the pointer to first node
 * Return: size of list
 */
size_t list_l(const list_t *j)
{
	size_t a = 0;

	while (j)
	{
		j = j->next;
		a++;
	}
	return (a);
}

/**
 * list_str - returns an array of strings of the list->str
 * @j: pointer to first node
 * Return: array of strings
 */
char **list_str(list_t *j)
{
	list_t *node = j;
	size_t a = list_l(j), b;
	char **str;
	char *str;

	if (!j || !a)
		return (NULL);
	strs = malloc(sizeof(char *) * (a + 1));
	if (!strs)
		return (NULL);
	for (a = 0; node; node = node->next, a++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (b = 0; b < a; b++)
				free(strs[b]);
			free(strs);
			return (NULL);
		}

		str = strcpy(str, node->str);
		strs[a] = str;
	}
	strs[a] = NULL;
	return (strs);
}


/**
 * list_p - prints all elements of a list_t linked list
 * @j: pointer to first node
 * Return: size of list
 */
size_t list_p(const list_t *j)
{
	size_t a = 0;

	while (j)
	{
		puts(num_conv(j->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		puts(j->str ? j->str : "(nil)");
		puts("\n");
		j = j->next;
		j++;
	}
	return (a);
}

/**
 * n_starts - returns node whose string starts with prefix
 * @node: pointer to list head
 * @pre: string to match
 * @c: the next character after prefix to match
 * Return: match node or null
 */
list_t *n_starts(list_t *node, char *pre, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = starts(node->str, pre);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node - gets the index of a node
 * @j: pointer to list head
 * @node: pointer to the node
 * Return: index of node or -1
 */
ssize_t get_node(list_t *j, list_t *node)
{
	size_t a = 0;

	while (j)
	{
		if (j == node)
			return (a);
		j = j->next;
		a++;
	}
	return (-1);
}
