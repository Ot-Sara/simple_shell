#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * set_zeros - sets to zeros
 * @arr: arr
 * @size: size
 */
void set_zeros(unsigned int *arr, unsigned int size)
{
	unsigned int i;

	for (i = 0 ; i < size ; i++)
	{
		arr[i] = 0;
	}
}

