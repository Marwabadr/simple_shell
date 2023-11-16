#include "simpleshell.h"

/**
 * bfree - free a pointer address to NULL
 * @potr: address
 *
 * Return: 1  free sinon 0
 */
int bfree(void **potr)
{
	if (pptr && *potr)
	{
		free(*potr);
		*potr = NULL;
		return (1);
	}
	return (0);
}
