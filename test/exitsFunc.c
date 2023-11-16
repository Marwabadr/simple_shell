#include "simpleshell.h"

/**
 **_strncpy - copy a string
 *@d: dest
 *@s: src
 *@num: number of char copied
 *Return: string
 */
char *_strncpy(char *d, char *s, int num)
{
	int i, j;
	char *src = d;

	i = 0;
	while (s[i] != '\0' && i < num - 1)
	{
		d[i] = s[i];
		i++;
	}
	if (i < num)
	{
		j = i;
		while (j < num)
		{
			d[j] = '\0';
			j++;
		}
	}
	return (src);
}

/**
 **_strncat - concat strings
 *@d: string
 *@s: string
 *@num: the amount of bytes to be maximally used
 *Return: string
 */
char *_strncat(char *d, char *s, int num)
{
	int i, j;
	char *src = d;

	i = 0;
	j = 0;
	while (d[i] != '\0')
		i++;
	while (s[j] != '\0' && j < num)
	{
		d[i] = s[j];
		i++;
		j++;
	}
	if (j < num)
		d[i] = '\0';
	return (src);
}

/**
 **_strchr - character in a string
 *@str: string
 *@ch: character
 *Return: pointer
 */
char *_strchr(char *str, char ch)
{
	do {
		if (*str == ch)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
