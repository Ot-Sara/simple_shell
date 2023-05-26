#include "main.h"

/**
 * exec_cmd - determines if a file is an executable command
 * @data: the data struct
 * @p: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int exec_cmd(data_t *data, char *p)
{
	struct stat st;
	(void)data;

	if (p)
	{
		if (stat(p, &st) == 0 && S_ISREG(st.st_mode))
		{
			return (1);
		}
	}
	return (0);
}

/**
 * char_dup - duplicates characters
 * @str: the PATH string
 * @start_ind: starting index
 * @stop_ind: stopping index
 *
 * Return: pointer to new buffer
 */

char *char_dup(char *str, int start_ind, int stop_ind)
{
	static char buffer[1024];
	int a, b = 0;

	for (b = 0, a = start_ind; a < stop_ind; a++)
	{
		if (str[a] != ':')
		{
			buffer[b++] = str[a];
		}
	}
	buffer[b] = '\0';
	return (buffer);
}

/**
 * path_finder - finds the cmd in the PATH string
 * @data: the data struct
 * @str: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */

char *path_finder(data_t *data, char *str, char *cmd)
{
	int a = 0, current = 0;
	char *p;

	if (!str)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts(cmd, "./"))
	{
		if (is_command(data, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!str[a] || str[a] == ':')
		{
			p = char_dup(str, current, a);
			if (!*p)
				strcat(p, cmd);
			else
			{
				strcat(p, "/");
				strcat(p, cmd);
			}
			if (is_command(data, p))
				return (p);
			if (!str[a])
				break;
			current = a;
		}
		a++;
	}
	return (NULL);
}
