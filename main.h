#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
<<<<<<< HEAD
#include "env.h"
=======
>>>>>>> ac8d8435a1d76bab40489442088b2c73ec78f2ae
#include <fcntl.h>

extern char **environ;

char *_getenv(const char *name);
char *get_command(char *cmd);
char **split_string(char *str, char *delimiter);
<<<<<<< HEAD

=======
>>>>>>> ac8d8435a1d76bab40489442088b2c73ec78f2ae
#endif
