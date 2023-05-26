#include "main.h"

/**
 * hist_get - gets the history file
 * @data: parameter struct
 * Return: allocated string containg history file
 */

char *hist_get(data_t *data)
{
	char *buffer, *directory;

	directory = env(data, "HOME=");
	if (!directory)
		return (NULL);
	buffer = malloc(sizeof(char) * (strlen(directory) +
				strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	strcpy(buffer, directory);
	strcat(buffer, "/");
	strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * w_hist - creates a file, or appends to an existing file
 * @data: the parameter struct
 * Return: 1 on success, else -1
 */

int w_hist(data_t *data)
{
	ssize_t f_d;
	char *file_name = hist_get(data);
	list_t *node = NULL;

	if (!file_name)
		return (-1);

	f_d = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (f_d == -1)
		return (-1);
	for (node = data->hist; node; node = node->next)
	{
		puts_fd(node->str, f_d);
		put_fd('\n', f_d);
	}
	put_fd(BUF_FLUSH, f_d);
	close(f_d);
	return (1);
}

/**
 * r_hist - reads history from file
 * @data: the parameter struct
 * Return: histcount on success, 0 otherwise
 */

int r_hist(data_t *data)
{
	int a, last = 0, l_count = 0;
	ssize_t f_d, rd_length, f_size = 0;
	struct stat st;
	char *buffer = NULL, *file_name = hist_get(data);

	if (!file_name)
		return (0);

	f_d = open(file_name, O_RDONLY);
	free(file_name);
	if (f_d == -1)
		return (0);
	if (!fstat(f_d, &st))
		f_size = st.st_size;
	if (f_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (f_size + 1));
	if (!buffer)
		return (0);
	rd_length = read(f_d, buffer, f_size);
	buffer[f_size] = 0;
	if (rd_length <= 0)
		return (free(buffer), 0);
	close(f_d);
	for (a = 0; a < f_size; a++)
		if (buffer[a] == '\n')
		{
			buffer[a] = 0;
			hist_l(data, buffer + last, l_count++);
			last = a + 1;
		}
	if (last != a)
		hist_l(data, buffer + last, l_count++);
	free(buffer);
	data->hist_count = l_count;
	while (data->hist_count-- >= HIST_MAX)
		del_node(&(data->hist), 0);
	ren_hist(data);
	return (data->hist_count);
}

/**
 * hist_l - adds entry to a history linked list
 * @data: Structure containing potential arguments
 * @buffer: buffer
 * @l_count: the history linecount, histcount
 * Return: Always 0
 */

int hist_l(data_t *data, char *buffer, int l_count)
{
	list_t *node = NULL;

	if (data->hist)
		node = data->hist;
	add_node(&node, buffer, l_count);

	if (!data->hist)
		data->hist = node;
	return (0);
}

/**
 * ren_hist - renumbers the history linked list after changes
 * @data: Structure containing potential arguments
 * Return: the new histcount
 */

int ren_hist(data_t *data)
{
	list_t *node = data->hist;
	int a = 0;

	while (node)
	{
		node->num = a++;
		node = node->next;
	}
	return (data->hist_count = a);
}
