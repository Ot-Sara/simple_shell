#include "shell.h"

/**
 * split_string - splits a string
 * @str: the string
 * @separators: the separators
 * @word_count: size
 * Return: vector of pointers
 */

char **split_string(char *str, char *separators, int *word_count)
{
	int c, v;
	char **words;
	char *str_ptr = str;
	bool start = false;
	unsigned int no_of_words;
	unsigned int word_sizes[MAX_WORD_COUNT];

	set_zeros(word_sizes, MAX_WORD_COUNT);
	no_of_words = count_words(str, seperators, word_sizes);

	if (no_of_words == 0)
		return (NULL);

	words = malloc((sizeof(char *) * no_of_words) + 1);
	if (!words)
		return (NULL);

	for (v = 0; v < no_of_words; v++)
	{
		words[v] = malloc((sizeof(char) * word_sizes[v]) + 1);
		if (!words[v])
		{
			for (v--; v >= 0; v--)
				free(words[v]);
			free(words);
			return (NULL);
		}
	}
}
