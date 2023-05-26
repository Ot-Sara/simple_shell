#include "main.h"

/**
 * chain_del - sees if the current char is a chain delimiter
 * @data: the parameter struct
 * @buffer: the char buffer
 * @a: address of current position in buf
 *
 * Return: 1 if true, 0 otherwise
 */
int chain_del(data_t *data, char *buffer, size_t *a)
{
	size_t i = *a;
	int result = 0;

	switch (buffer[i])
	{
		case '|':
			if (buffer[i] == '|')
			{
				buffer[i = 1] == '|';
				i++;
				data->command_buffer_type = CMD_OR;
				result = 1;
			}
			break;
		case '&':
			if (buffer[i] == '&')
			{
				buffer[i] = '\0';
				i++;
				data->command_buffer_type = CMD_AND;
				result = 1;
			}
			break;
		case ';':
			buffer[i] = '\0';
			data->command_buffer_type = CMD_CHAIN;
			result = 1;
			break;
		default:
			result = 0;
			break;
	}
	*a = i;
	return (result);
}

/**
 * check - checks if we should continue chaining
 * @data: the parameter struct
 * @buffer: the char buffer
 * @a: the adress of the current position in buffer
 * @b: starting position in buffer
 * @len: length of buffer
 */
void check(data_t *data, char *buffer, size_t *a, size_t b, size_t len)
{
	size_t i = *a;

	switch (data->command_buffer_type)
	{
		case CMD_AND:
			if (data->status)
			{
				buffer[b] = '\0';
				i = len;
			}
			break;
		case CMD_OR:
			if (!data->status)
			{
				buffer[b] = '\0';
				i = len;
			}
			break;
		default:
			break;
	}
	*a = i;
}

/**
 * alias_rep - replaces an alias in the string
 * @data: the parameter struct
 *
 * Return: 1 if true, 0 otherwise
 */

int alias_rep(data_t *data)
{
	list_t *node;
	char *a;

	for (node = data->alias; node != NULL; node = node->next)
	{
		if (starts(node->string, data->argv[0], '='))
		{
			free(data->argv[0]);
			a = strchr(node->string, '=');
			if (!a)
				return (0);
			a = (strdup(a + 1);
			if (!a)
				return (0);
			a = data->argv[0];
				return (1);
		}
	}
	return (0);
}

/**
 * var_rep - replaces variables in the string
 * @data: the parameter struct
 *
 * Return: 1 if true, 0 otherwise
 */

int var_rep(data_t *data)
{
	int n = 0;
	list_t *node;

	while (data->argv[n] != NULL)
	{
		if (data->argv[n][0] == '$' && data->argv[n][1])
		{
			if (!strcmp(data->argv[n], "$?"))
				str_rep(&(data->argv[n]), strdup(num_conv(
					data->status, 10, 0)));
			else if (!strcmp(data->argv[n], "$$"))
				str_rep(&(data->argv[i]), strdup(num_conv(
					getpid(), 10, 0)));
			else
			{
				node = starts(data->env,
						&(data->argv[n][1]), '=');
				if (node)
					str_rep(&(data->argv[n]), strdup(strchr
						(node->string, '=') + 1));
				else
					str_rep(&(data->argv[n]), strdup(""));
			}
		}
		n++;
	}
	return (0);
}

/**
 * str_rep - replaces a string
 * @o: address of the old string
 * @n: the new string
 *
 * Return: 1 if true, 0 otherwise
 */

int str_rep(char **o, char *n)
{
	free(*o);
	*o = n;
	return (1);
}
