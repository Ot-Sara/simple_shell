#include "main.h"

/**
 * get_env - returns the string array copy of our environ
 * @data: Structure used to maintain constant function prototype.
 * Return: Always 0
 */
char **get_env(data_t *data)
{
	if (!data->environ || data->env_changed)
	{
		data->environ = list_str(data->env);
		data->env_changed = 0;
	}

	return (data->environ);
}

/**
 * set_env - Initialize a new environment variable,
 *             or modify an existing one
 * @data: Structure used to maintain constant function prototype.
 * @v: the string env var property
 * @val: the string env var value
 * Return: Always 0
 */
int set_env(data_t *data, char *v, char *val)
{
	char *buffer = NULL;
	list_t *node;
	char *ptr;

	if (!v || !val)
		return (0);

	buffer = malloc(strlen(v) + strlen(val) + 2);
	if (!buffer)
		return (1);
	strcpy(buffer, v);
	strcat(buffer, "=");
	strcat(buffer, val);
	node = data->env;
	while (node)
	{
		ptr = starts(node->str, v);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buffer;
			data->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node(&(data->env), buffer, 0);
	free(buffer);
	data->env_changed = 1;
	return (0);
}

/**
 * unset_env - Remove an environment variable
 * @data: Structure used to maintain constant function prototype.
 * @v: the string env var property
 * Return: 1 on delete, 0 otherwise
 */
int unset_env(data_t *data, char *v)
{
	list_t *node = data->env;
	size_t a = 0;
	char *ptr;

	if (!node || !v)
		return (0);

	while (node)
	{
		ptr = starts(node->str, v);
		if (ptr && *ptr == '=')
		{
			data->env_changed = del_node(&(data->env), a);
			a = 0;
			node = data->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (data->env_changed);
