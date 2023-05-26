#ifndef _MAIN_H_
#define _MAIN_H_

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

/*
 * Declaration for accessing environment variables
 */
extern char **environ;

char *_getenv(const char *name);
char *get_command(char *cmd);
char **split_string(char *str, char *delimiter);
int count_word(char *s);
char **strtow(char *str);


#endif
