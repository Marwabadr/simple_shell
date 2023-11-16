#include "simpleshell.h"

/**
 * _strcpy - copy a string
 * @dest: destination
 * @src:  source
 * Return: dest pointer
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strdup - duplicatestr
 * @str: source
 * Return: pointer
 */
char *_strdup(const char *str)
{
	int leng = 0;
	char *retu;

	if (str == NULL)
		return (NULL);
	while (*str++)
		leng++;
	retu = malloc(sizeof(char) * (leng + 1));
	if (!retu)
		return (NULL);
	for (leng++; leng--;)
		retu[leng] = *--str;
	return (retu);
}

/**
 *_puts - print input str
 *@str: string
 *
 * Return: none void
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - write char to stdout
 * @c: character
 * Return: On success 1,-1,errno
 */
int _putchar(char c)
{
	static int i;
	static char buff[WRITEBUFSIZE];

	if (c == BUFFLUSH || i >= WRITEBUFSIZE)
	{
		write(1, buff, i);
		i = 0;
	}
	if (c != BUFFLUSH)
		buff[i++] = c;
	return (1);
}
