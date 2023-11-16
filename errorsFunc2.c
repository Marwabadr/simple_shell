#include "simpleshell.h"

/**
 * _erratoi - string to int
 * @st: string
 * Return: 0,-1
 */
int _erratoi(char *st)
{
	int i = 0;
	unsigned long int resultat = 0;

	if (*st == '+')
		st++;
	for (i = 0;  st[i] != '\0'; i++)
	{
		if (st[i] >= '0' && st[i] <= '9')
		{
			resultat *= 10;
			resultat += (st[i] - '0');
			if (resultat > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (resultat);
}

/**
 * printError - printerror msg
 * @info: infoP srtuct
 * @stre: error string
 */
void printError(infoP *info, char *stre)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(stre);
}

/**
 * print_d - function decimal
 * @in: input
 * @filed: filedescriptor
 * Return: count of char
 */
int print_d(int in, int filed)
{
	int (*__putchar)(char) = _putchar;
	int i, cpt = 0;
	unsigned int _abs_, cur;

	if (filed == STDERR_FILENO)
		__putchar = _eputchar;
	if (in < 0)
	{
		_abs_ = -in;
		__putchar('-');
		cpt++;
	}
	else
		_abs_ = in;
	cur = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + cur / i);
			cpt++;
		}
		cur %= i;
	}
	__putchar('0' + cur);
	cpt++;

	return (cpt);
}

/**
 * convertNumber - convert function
 * @number: number
 * @b: base
 * @f: flaf
 *
 * Return: str
 */
char *convertNumber(long int number, int b, int f)
{
	static char *table;
	static char buff[50];
	char signe = 0;
	char *p;
	unsigned long n = number;

	if (!(f & CONVERTUNSIGNED) && number < 0)
	{
		n = -number;
		signe = '-';

	}
	table = f & CONVERTLOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buff[49];
	*p = '\0';

	do	{
		*--p = table[n % b];
		n /= b;
	} while (n != 0);

	if (signe)
		*--p = signe;
	return (p);
}

/**
 * removeComments -  # with \0
 * @buff: address
 *
 * Return: void
 */
void removeComments(char *buff)
{
	int i;

	for (i = 0; buff[i] != '\0'; i++)
		if (buff[i] == '#' && (!i || buff[i - 1] == ' '))
		{
			buff[i] = '\0';
			break;
		}
}
