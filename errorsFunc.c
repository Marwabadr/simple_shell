#include "simpleshell.h"

/**
 *_eputs - print string
 * @s: string
 * Return: none
 */
void _eputs(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		_eputchar(s[i]);
		i++;
	}
}

/**
 * _eputchar - write character to stderr
 * @cr: character
 * Return: 1
 */
int _eputchar(char cr)
{
	static int i;
	static char buff[MY_WRITE_BUF_S];

	if (cr == MY_BUF_F || i >= MY_WRITE_BUF_S)
	{
		write(2, buff, i);
		i = 0;
	}
	if (cr != MY_BUF_F)
		buff[i++] = cr;
	return (1);
}

/**
 * _putfd - write char
 * @ch: char
 * @fld: fileDescriptor
 * Return: 1
 */
int _putfld(char ch, int fld)
{
	static int i;
	static char buff[MY_WRITE_BUF_S];

	if (ch == MY_BUF_F || i >= MY_WRITE_BUF_S)
	{
		write(fld, buff, i);
		i = 0;
	}
	if (ch != MY_BUF_F)
		buff[i++] = ch;
	return (1);
}

/**
 *_putsfd - print an input
 * @string: stirng
 * @filed: fileDescriptor
 * Return: the number of chars put
 */
int _putsfd(char *string, int filed)
{
	int i = 0;

	if (!string)
		return (0);
	while (*string)
	{
		i += _putfld(*string++, filed);
	}
	return (i);
}
