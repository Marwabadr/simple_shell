#include "simpleshell.h"

/**
 *_eputs - prints string
 * @s: string
 *
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
 * _eputchar - writes the character to stderr
 * @cr: character
 *
 * Return: 1.
 */
int _eputchar(char cr)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (cr == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (cr != BUF_FLUSH)
		buf[i++] = cr;
	return (1);
}

/**
 * _putfd - writes the character to given fd
 * @cr: character
 * @fld: The filedescriptor to write to
 *
 * Return: 1.
 */
int _putfd(char cr, int fld)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (cr == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fld, buf, i);
		i = 0;
	}
	if (cr != BUF_FLUSH)
		buf[i++] = cr;
	return (1);
}

/**
 *_putsfd - prints string
 * @s: string
 * @fld: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *s, int fld)
{
	int i = 0;

	if (!s)
		return (0);
	while (*s)
	{
		i += _putfd(*s++, fld);
	}
	return (i);
}
