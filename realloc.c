#include "simpleshell.h"

/**
 **_memset - fill mem with bytes
 *@s: poiter
 *@b: byte
 *@n: count of bytes
 *Return: pointer
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - free string
 * @stst: chaine des chaines
 */
void ffree(char **stst)
{
	char **a = stst;

	if (!stst)
		return;
	while (stst)
		free(*stst++);
	free(a);
}

/**
 * _realloc - realloc func
 * @ptr: pointer
 * @osize: byte old
 * @nsize: byte new
 * Return: pointer
 */
void *_realloc(void *ptr, unsigned int osize, unsigned int nsize)
{
	char *p;

	if (!ptr)
		return (malloc(nsize));
	if (!nsize)
		return (free(ptr), NULL);
	if (nsize == osize)
		return (ptr);

	p = malloc(nsize);
	if (!p)
		return (NULL);

	osize = osize < nsize ? osize : nsize;
	while (osize--)
		p[osize] = ((char *)ptr)[osize];
	free(ptr);
	return (p);
}
