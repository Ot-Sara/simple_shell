#include "main."

/**
 * my_exit - exits the shell
 * @data: Structure used to maintain constant function prototype.
 *  Return: exits with a given exit status (0) if info.argv[0] != "exit"
 */

int my_exit(data_t *data)
{
	int exit_check;

	if (data->argv[1])
	{
		exit_check = inter_err(data->argv[1]);
		if (exit_check == -1)
		{
			data->status = 2;
			error_p(data, "Illegal number: ");
			puts_err(data->argv[1]);
			_putchar_err('\n');
			return (1);
		}
		data->n_err = inter_err(data->argv[1]);
		return (-2);
	}
	data->n_err = -1;
	return (-2);
}

/**
 * my_cd - changes the current directory of the process
 * @data: Structure used to maintain constant function prototype.
 *  Return: Always 0
 */

int my_cd(data_t *data)
{
	char *str, *directory, buffer[1024];
	int chdirectory_r;

	str = getcwd(buffer, 1024);
	if (!str)
		puts("error\n");
	if (!data->argv[1])
	{
		directory = env(data, "HOME=");
		if (!directory)
			chdirectory((directory = env(data, "PWD="))
					? directory : "/");
		else
			chdirectory_r = chdirectory(directory);
	}
	else if (strcmp(data->argv[1], "-") == 0)
	{
		if (!env(data, "OLDPWD="))
		{
			puts(s);
			_putchar('\n');
			return (1);
		}
		puts(env(data, "OLDPWD=")), _putchar('\n');
			chdirectory((directory = env(data, "OLDPWD="))
					? directory : "/");
	}
	else
		chdirectory_r = chdirectory(data->argv[1]);
	if (chdirectory_r == -1)
	{
		error_p(data, "can't cd to ");
		puts_err(data->argv[1]), _putchar_err('\n');
	}
	else
	{
		set_env(data, "OLDPWD", env(data, "PWD="));
		set_env(data, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * my_help - changes the current directory of the process
 * @data: Structure used to maintain constant function prototype.
 * Return: Always 0
 */

int my_help(data_t *data)
{
	char **arg_arr;

	arg_arr = data->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		puts(*arg_arr);
	return (0);
}
