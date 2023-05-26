#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define R_BUF_SIZE 1024
#define W_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@p: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@command_buffer_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *p;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buffer; /* pointer to cmd ; chain buffer, for memory mangement */
	int command_buffer_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} data_t;

#define DATA_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(data_t *);
} builtin_table;


/* toem_shell.c */
int hsh(data_t *, char **);
int builtin_finder(data_t *);
void cmd_finder(data_t *);
void c_fork(data_t *);

/* toem_decode.c */
int exec_cmd(info_t *, char *);
char *char_dup(char *, int, int);
char *path_finder(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void puts_err(char *);
int putchar_err(char);
int put_fd(char c, int fd);
int puts_fd(char *str, int fd);

/* toem_strings_f2.c */
int strlen(char *);
int strcmp(char *, char *);
char *starts(const char *, const char *);
char *strcat(char *, char *);

/* toem_strings_f1.c */
char *strcpy(char *, char *);
char *strdup(const char *);
void puts(char *);
int _putchar(char);

/* toem_exit_f.c */
char *strncpy(char *, char *, int);
char *strncat(char *, char *, int);
char *strchr(char *, char);

/* toem_split_string.c */
char **strtow_f1(char *, char *);
char **strtow_f2(char *, char);

/* toem_my_realloc.c */
char *memset(char *, char, unsigned int);
void dfree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_mem.c */
int free_p(void **);

/* toem_inter.c */
int inter(info_t *);
int del(char, char *);
int isalpha(int);
int atoi(char *);

/* toem_errors1.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_built_in2.c */
int my_exit(data_t *);
int my_cd(data_t *);
int my_help(data_t *);

/* toem_built_in1.c */
int my_hist(data_t *);
int alias_set(data_t, char *);
int alias_unset(data_t, char *);
int alias_p(list_t *);
int my_alias(data_t *);

/*toem_getline.c */
ssize_t get_in(data_t *);
int _getline(data_t *, char **, size_t *);
void sig_handler(int);

/* toem_getdata.c */
void cl_data(data_t *);
void set_data(data_t *, char **);
void data_free(data_t *, int);

/* toem_environ.c */
char *_getenv(data_t *, const char *);
int my_env(data_t *);
int my_setenv(data_t *);
int my_unsetenv(data_t *);
int pop_env(data_t *);

/* toem_env.c */
char **get_env(data_t *);
int unset_env(data_t *, char *);
int set_env(data_t *, char *, char *);

/* toem_hist.c */
char *hist_get(data_t *data);
int w_hist(data_t *data);
int r_hist(data_t *data);
int hist_l(data_t *data, char *buffer, int l_count);
int ren_hist(data_t *data);

/* toem_list_f2.c */
list_t *node_a(list_t **, const char *, int);
list_t *add_node(list_t **, const char *, int);
size_t list_p_s(const list_t *);
int del_node(list_t **, unsigned int);
void list_f(list_t **);

/* toem_list_f1.c */
size_t list_l(const list_t *);
char **list_str(list_t *);
size_t list_p(const list_t *);
list_t *n_starts(list_t *, char *, char);
ssize_t get_node(list_t *, list_t *);

/* toem_variables.c */
int chain_del(data_t *, char *, size_t *);
void check(data_t *, char *, size_t *, size_t, size_t);
int alias_rep(data_t *);
int var_rep(data_t *);
int str_rep(char **, char *);

#endif
