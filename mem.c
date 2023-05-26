#include "main.h"

/**
 * free_p - frees a pointer and NULLs the address
 * @ptr: the address of the pointer to free
 * Return: 1 if true, 0 otherwise
 */

int free_p(void **ptr)
{
	if (ptr == NULL || *ptr == NULL)
		return (0);
	free(*ptr);
	*ptr = NULL;
	return (1);
}
