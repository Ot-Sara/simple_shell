#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * count_word - helper function to count the number of words in a string
 * @s: string to evaluate
 * Return: number of words
 */

int count_word(char *s)
{
        int flag, c, w;

        flag = 0;
        w = 0;
        for (c = 0; s[c] != '\0'; c++)
        {
                if (s[c] == ' ')
                flag = 0;
                else if (flag == 0)
                {
                        flag = 1;
                        w++;
                }
        }
        return (w);
}
/**
 * strtow - splits a string into words
 * @str: the string
 * Return: a pointer to an array of strings (words).
 * NULL if str == NULL or str == "" or if it fails
 */

char **strtow(char *p)
{
	char **matrix, *tmp;
	int i = 0, j = 0, k = 0, len = 0, words, c = 0, start, end;
	static char *str = NULL;
	static int n = 0;

	if (p != NULL)
		str = p;
	else
		n++;

	while (*(str + len))
		len++;

	words = count_word(str);
	if (words == 0)
		return (NULL);

	matrix = (char **) malloc(sizeof(char *) * (words + 1));
	if (matrix == NULL)
		return (NULL);

	for (i = 0; i <= len; i++)
	{
		if (str[i] == ' ' || str[i] == '\0')
		{
			if (c)
			{
				end = i;
				tmp = (char *) malloc(sizeof(char) * (c + 1));
				if (tmp == NULL)
				{
					for (j = 0; j < k; j++)
						free(matrix[j]);
					free(matrix);
					return (NULL);
				}
				for(j = 0; start < end; j++, start++)
					tmp[j] = str[start];
				tmp[c] = '\0';
				matrix[k] = tmp;
				k++;
				c = 0;
			}
		}
		else if (c++ == 0)
			start = i;
	}
	matrix[k] = NULL;
	return (matrix);
}

/**
 * main - Entry point
 *
 * Return: 0 success
 */

int main(void)
{
	char a[] = "Hello World! Welcome to the program";
	char **words = strtow(a);
	int i = 0, j = 0;

	while (words == NULL)
	{       
		printf("Failed to split the string into words\n");
		return (1);
        }
	while (words[i] != NULL)
	{
		printf("%s\n", words[i]);
		i++;
	}
	for (j = 0; j < i; j++)
		free(words[j]);
	free(words);
	return (0);
}
