#include "main.h"

/**
 * node_a - adds a node to the start of the list
 * @j: address of pointer to head node
 * @s: str field of node
 * @n: node index used by history
 * Return: size of list
 */

list_t *node_a(list_t **j, const char *s, int n)
{
	list_t *new_h;

	if (!j)
		return (NULL);
	new_h = malloc(sizeof(list_t));
	if (!new_h)
		return (NULL);
	memset((void *)new_h, 0, sizeof(list_t));
	new_h->n = n;
	if (s)
	{
		new_h->s = strdup(s);
		if (!new_h->s)
		{
			free(new_h);
			return (NULL);
		}
	}
	new_h->next = *h;
	*j = new_h
	return (new_h);
}

/**
 * add_node - adds a node to the end of the list
 * @j: address of pointer to head node
 * @s: str field of node
 * @n: node index used by history
 * Return: size of list
 */

list_t *add_node(list_t **j, const char *s, int n)
{
	list_t *new_n, *node;

	if (!j)
		return (NULL);

	node = *j;
	new_n = malloc(sizeof(list_t));
	if (!new_n)
		return (NULL);
	memset((void *)new_n, 0, sizeof(list_t));
	new_n->n = n;
	if (s)
	{
		new_n->s = strdup(s);
		if (!new_n->s)
		{
			free(new_n);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_n;
	}
	else
		*j = new_n;
	return (new_n);
}

/**
 * list_p_s - prints only the str element of a list_t linked list
 * @j: pointer to first node
 * Return: size of list
 */

size_t list_p_s(const list_t *j)
{
	size_t a = 0;

	while (j)
	{
		puts(j->s ? j->s : "(nil)");
		puts("\n");
		j = j->next;
		a++;
	}
	return (a);
}

/**
 * del_node - deletes node at given index
 * @j: address of pointer to first node
 * @i: index of node to delete
 * Return: 1 on success, 0 on failure
 */

int del_node(list_t **j, unsigned int i)
{
	list_t *node, *prev_node;
	unsigned int a = 0;

	if (!j || !*j)
		return (0);

	if (!i)
	{
		node = *j;
		*j = (*j)->next;
		free(node->s);
		free(node);
		return (1);
	}
	node = *j;
	while (node)
	{
		if (a == i)
		{
			prev_node->next = node->next;
			free(node->s);
			free(node);
			return (1);
		}
		a++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * list_f - frees all nodes of a list
 * @j_ptr: address of pointer to head node
 * Return: void
 */

void list_f(list_t **j_ptr)
{
	list_t *node, *next_node, *j;

	if (!j_ptr || !*j_ptr)
		return;
	j = *j_ptr;
	node = j;
	while (node)
	{
		next_node = node->next;
		free(node->s);
		free(node);
		node = next_node;
	}
	*j_ptr = NULL;
}
