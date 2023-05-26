#include "main.h"

/**
 * my_hist - displays the history list, one command by line
 * @data: Structure used to maintain constant function prototype.
 * Return: Always 0
 */

int my_hist(data_t *data)
{
	list_p(data->hist);
	return (0);
}

/**
 * alias_set - sets alias to string
 * @data: parameter struct
 * @s: the string alias
 * Return: Always 0 on success, 1 on error
 */

int alias_set(data_t *data, char *s)
{
	char *ptr;

	ptr = strchr(s, '=');
	if (!ptr)
		return (1);
	if (*++ptr == NULL)
		return (alias_unset(data, s));

	alias_unset(data, s);
	return (add_node(&(data->alias), s, 0) == NULL);
}

/**
 * alias_unset - sets alias to string
 * @data: parameter struct
 * @s: the string alias
 * Return: Always 0 on success, 1 on error
 */

int alias_unset(data_t *data, char *s)
{
	char *ptr, a;
	int b;

	ptr = strchr(s, '=');
	if (!ptr)
		return (1);
	a = *ptr;
	*ptr = 0;
	b = del_node(&(data->alias),
		get_node(data->alias, n_starts(data->alias, s, -1)));
	*ptr = a;
	return (b);
}

/**
 * alias_p - prints an alias string
 * @node: the alias node
 * Return: Always 0 on success, 1 on error
 */

int alias_p(list_t *node)
{
	char *ptr = NULL, *c = NULL;

	if (node)
	{
		ptr = strchr(node->s, '=');
		for (c = node->s; c <= ptr; c++)
			_putchar(*c);
		_putchar('\'');
		puts(ptr + 1);
		puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_alias - mimics the alias builtin (man alias)
 * @data: Structure used to maintain constant function prototype.
 *  Return: Always 0
 */

int my_alias(data_t *data)
{
	int a = 0;
	char *ptr = NULL;
	list_t *node = NULL;

	if (data->argc == 1)
	{
		node = data->alias;
		while (node)
		{
			alias_p(node);
			node = node->next;
		}
		return (0);
	}
	for (a = 1; data->argv[a]; a++)
	{
		ptr = strchr(data->argv[i], '=');
		if (ptr)
			alias_set(data, data->argv[i]);
		else
			alias_p(n_starts(data->alias, data->argv[i], '='));
	}

	return (0);
}
