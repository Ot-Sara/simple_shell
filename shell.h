#ifndef SHELL_H
#define SHELL_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define MAX_WORD_COUNT 100

bool is_separator(char c, char *sep);
char **split_string(char *str, char *separators, int *word_count);
int _execute(char *arguments, struct stat *statbuf, char **env);
bool check_file_status(char *pathname, struct stat *statbuf);
void set_zeros(unsigned int *arr, unsigned int size);
unsigned int count_words(char *str, char *sep, unsigned int size);

#endif
