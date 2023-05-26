#include "main.h"

/**
 * buffer_in - buffers chained commands
 * @data: parameter struct
 * @buffer: address of buffer
 * @length: address of len var
 * Return: bytes read
 */

ssize_t buffer_in(data_t *data, char **buffer, size_t *length)
{
	ssize_t a = 0;
	size_t length_p = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sig_Handler);
#if USE_GETLINE
		r = getline(buffer, &length_p, stdin);
#else
		r = _getline(data, buffer, &length_p);
#endif
		if (a > 0)
		{
			if ((*buffer)[a - 1] == '\n')
			{
				(*buffer)[a - 1] = '\0';
				a--;
			}
			data->l_count_flag = 1;
			r_com(*buffer);
			hist_l(data, *buffer, data->hist_count++);
			{
				*length = a;
				data->cmd_buffer = buffer;
			}
		}
	}
	return (a);
}

/**
 * get_in - gets a line minus the newline
 * @data: parameter struct
 * Return: bytes read
 */

ssize_t get_in(data_t *data)
{
	static char *buffer;
	static size_t b, c, length;
	ssize_t a = 0;
	char **buffer_p = &(data->arg), *ptr;

	_putchar(BUF_FLUSH);
	a = buffer_in(data, &buffer, &length);
	if (a == -1)
		return (-1);
	if (length)
	{
		c = b;
		ptr = buffer + b;

		check_chain(data, buffer, &c, b, length);
		while (c < length)
		{
			if (is_chain(data, buffer, &c))
				break;
			c++;
		}

		b = c + 1;
		if (b >= length)
		{
			b = length = 0;
			data->command_buffer_type = CMD_NORM;
		}

		*buffer_p = ptr;
		return (strlen(ptr));
	}

	*buffer_p = buffer;
	return (a);
}

/**
 * r_buffer - reads a buffer
 * @data: parameter struct
 * @buffer: buffer
 * @b: size
 * Return: a
 */

ssize_t r_buffer(data_t *data, char *buffer, size_t *b)
{
	ssize_t a = 0;

	if (*b)
		return (0);
	a = read(data->readfd, buffer, R_BUF_SIZE);
	if (a >= 0)
		*b = a;
	return (a);
}

/**
 * _getline - gets the next line of input from STDIN
 * @data: parameter struct
 * @p: address of pointer to buffer, preallocated or NULL
 * @len: size of preallocated ptr buffer if not NULL
 * Return: str
 */

int _getline(data_t *data, char **p, size_t *len)
{
	static char buffer[R_BUF_SIZE];
	static size_t b, l;
	size_t k;
	ssize_t a = 0, str = 0;
	char *ptr = NULL, *new_ptr = NULL, *c;

	ptr = *p;
	if (ptr && len)
		str = *len;
	if (b == l)
		b = l = 0;

	a = r_buffer(data, buffer, &l);
	if (a == -1 || (a == 0 && l == 0))
		return (-1);

	c = strchr(buffer + b, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : l;
	new_ptr = _realloc(ptr, str, str ? str + k : k + 1);
	if (!new_ptr)
		return (ptr ? free(ptr), -1 : -1);

	if (str)
		strncat(new_ptr, buffer + b, k - b);
	else
		strncpy(new_ptr, buffer + b, k - b + 1);

	str += k - b;
	b = k;
	ptr = new_ptr;

	if (len)
		*len = str;
	*p = ptr;
	return (str);
}

/**
 * sig_handler - blocks ctrl-C
 * @sig_n: the signal number
 * Return: void
 */

void sig_handler(__attribute__((unused))int sig_n)
{
	puts("\n");
	puts("$ ");
	putchar(BUF_FLUSH);
}
