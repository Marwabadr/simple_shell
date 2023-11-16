#include "simpleshell.h"

/**
 *_eputs - print string
 * @string: string
 * Return: none
 */
void _eputs(char *string)
{
	int i = 0;

	if (!string)
		return;
	while (string[i] != '\0')
	{
		_eputchar(string[i]);
		i++;
	}
}

/**
 * _eputchar - character to stderr
 * @ch: character
 *
 * Return: 1,-1,errno
 */
int _eputchar(char ch)
{
	static int i;
	static char buff[WRITEBUFSIZE];

	if (ch == BUFFLUSH || i >= WRITEBUFSIZE)
	{
		write(2, buff, i);
		i = 0;
	}
	if (ch != BUFFLUSH)
		buff[i++] = ch;
	return (1);
}

/**
 * _putfd - write char to filedescriptor
 * @ch: character
 * @filed: filedescriptor
 * Return: 1,-1,errno
 */
int _putfd(char ch, int filed)
{
	static int i;
	static char buff[WRITEBUFSIZE];

	if (ch == BUFFLUSH || i >= WRITEBUFSIZE)
	{
		write(filed, buff, i);
		i = 0;
	}
	if (ch != BUFFLUSH)
		buff[i++] = ch;
	return (1);
}

/**
 *_putsfd - print input str
 * @string: string
 * @filed: filedescriptor
 * Return: count of char
 */
int _putsfd(char *string, int filed)
{
	int i = 0;

	if (!string)
		return (0);
	while (*string)
	{
		i += _putfd(*string++, filed);
	}
	return (i);
}
