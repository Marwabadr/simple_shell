#include "simpleshell.h"
/**
 * interactive - checks shell interactive
 * @infoP: infoP structure
 *
 * Return: 1
 */
int interactive(infoP *infoP)
{
	return (isatty(STDIN_FILENO) && infoP->readFd <= 2);
}

/**
 * isDelim - trouve un delimiteur
 * @ch: character
 * @d: delimiter
 * Return: 1
 */
int isDelim(char ch, char *d)
{
	while (*d)
		if (*d++ == ch)
			return (1);
	return (0);
}

/**
 *_isalpha - checks alpha char
 *@c: character
 *Return: 1
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - stringToInteger
 *@s: striing
 *Return: 0
 */

int _atoi(char *s)
{
	int i, signe = 1, f = 0, sortie;

	unsigned int resultat = 0;

	for (i = 0;  s[i] != '\0' && f != 2; i++)
	{
		if (s[i] == '-')
			signe *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			f = 1;
			resultat *= 10;
			resultat += (s[i] - '0');
		}
		else if (f == 1)
			f = 2;
	}
	if (signe == -1)
		sortie = -resultat;
	else
		sortie = resultat;
	return (sortie);
}
