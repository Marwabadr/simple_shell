#include "simpleshell.h"

/**
 **_strncpy - copy string
 *@dest: dest
 *@src: source
 *@n: count of string copied
 *Return: concat string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenate strings
 *@dest: dest
 *@src: source
 *@n: count of string
 *Return: concat str
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_strchr - locate character
 *@st: string
 *@c: char
 *Return: string
 */
char *_strchr(char *st, char c)
{
	do {
		if (*st == c)
			return (st);
	} while (*st++ != '\0');

	return (NULL);
}
