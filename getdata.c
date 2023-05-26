#include "main.h"

/**
 * cl_data - initializes data_t struct
 * @data: struct address
 */

void cl_data(data_t *data)
{
	data->arg = NULL;
	data->argv = NULL;
	data->argc = 0;
	data->path = NULL;
}

/**
 * set_data - initializes info_t struct
 * @data: struct address
 * @av: argument vector
 */
void set_data(data_t *data, char **av)
{
	int a = 0;

	data->fname = av[0];
	if (data->arg)
	{
		data->argv = strtow_f1(data->arg, " \t");
		if (!data->argv)
		{

			data->argv = malloc(sizeof(char *) * 2);
			if (data->argv)
			{
				data->argv[0] = strdup(data->arg);
				data->argv[1] = NULL;
			}
		}
		for (a = 0; data->argv && data->argv[i]; a++)
			;
		data->argc = a;

		alias_rep(data);
		var_rep(data);
	}
}

/**
 * data_free - frees data_t struct fields
 * @data: struct address
 * @all: true if freeing all fields
 */
void data_free(data_t *data, int all)
{
	dfree(data->argv);
	data->argv = NULL;
	data->path = NULL;
	if (all)
	{
		if (!data->cmd_buffer)
			free(data->arg);
		if (data->env)
			free_list(&(data->env));
		if (data->hist)
			free_list(&(data->hist));
		if (data->alias)
			free_list(&(data->alias));
		dfree(data->environ);
			data->environ = NULL;
		free_p((void **)data->cmd_buffer);
		if (data->readfd > 2)
			close(data->readfd);
		_putchar(BUF_FLUSH);
	}
}
