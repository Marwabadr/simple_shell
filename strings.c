#include "simpleshell.h"

/**
 * _strlen - len of a string
 * @s: string
 * Return: len of str
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - comparer deux strings alpha
 * @s1: str1
 * @s2: str2
 * Return: -1,1,0
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * startsWith - needlestart withhaystack
 * @ht: haystack
 * @nd: needle
 * Return: addresse
 */
char *startsWith(const char *ht, const char *nd)
{
	while (*nd)
		if (*nd++ != *ht++)
			return (NULL);
	return ((char *)ht);
}

/**
 * _strcat - concatenation de deux strings
 * @dest: dest
 * @src: source
 *
 * Return: dest pointer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
