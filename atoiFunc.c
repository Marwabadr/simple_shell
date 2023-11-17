#include "simpleshell.h"

/**
 * interactive - interactive mode
 * @info: infoP structure
 * Return: 1
 */
int interactive(infoP *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * isDelim - delimeter
 * @ch: cahr
 * @D: delimeter
 * Return: 1 sinon 0
 */
int isDelim(char ch, char *D)
{
	while (*D)
		if (*D++ == ch)
			return (1);
	return (0);
}

/**
 *_isalpha - alpha char
 *@ch: char
 *Return: 1 sinon 0
 */

int _isalpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - str to int
 *@st: string
 *Return: 0  sinon output
 */

int _atoi(char *st)
{
	int i, signe = 1, f = 0, out;
	unsigned int resultat = 0;

	for (i = 0;  st[i] != '\0' && f != 2; i++)
	{
		if (st[i] == '-')
			signe *= -1;

		if (st[i] >= '0' && st[i] <= '9')
		{
			f = 1;
			resultat *= 10;
			resultat += (st[i] - '0');
		}
		else if (f == 1)
			f = 2;
	}

	if (signe == -1)
		out = -resultat;
	else
		out = resultat;

	return (out);
}
