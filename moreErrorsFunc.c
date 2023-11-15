#include "simpleshell.h"

/**
 * _erratoi - convert a string
 * @string: string
 * Return: 0 r
 */
int _erratoi(char *string)
{
	int i = 0;
	unsigned long int resultat = 0;

	if (*string == '+')
		string++;
	for (i = 0;  string[i] != '\0'; i++)
	{
		if (string[i] >= '0' && string[i] <= '9')
		{
			resultat *= 10;
			resultat += (string[i] - '0');
			if (resultat > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (resultat);
}

/**
 * printError - prints an error message
 * @infoP: the parameter & return info struct
 * @strer: string error
 * Return: 0
 */
void printError(infoP *infoP, char *strer)
{
	_eputs(infoP->fileName);
	_eputs(": ");
	print_d(infoP->lcount, STDERR_FILENO);
	_eputs(": ");
	_eputs(infoP->argv[0]);
	_eputs(": ");
	_eputs(strer);
}

/**
 * print_d - print decimal
 * @inp: input
 * @filed: filedescriptor
 *
 * Return: num of char
 */
int print_d(int inp, int filed)
{
	int (*__putchar)(char) = _putchar;
	int i, cpt = 0;
	unsigned int _abs_, cur;

	if (filed == STDERR_FILENO)
		__putchar = _eputchar;
	if (inp < 0)
	{
		_abs_ = -inp;
		__putchar('-');
		cpt++;
	}
	else
		_abs_ = inp;
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
 * convertNumber - converter
 * @n: num
 * @b: base
 * @f: argument flags
 *
 * Return: string
 */
char *convertNumber(long int n, int b, int f)
{
	static char *arr;
	static char buffer[50];
	char signe = 0;
	char *ptrr;
	unsigned long number = n;

	if (!(f & CONVERT_UNSIGNED) && n < 0)
	{
		number = -n;
		signe = '-';

	}
	arr = f & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptrr = &buffer[49];
	*ptrr = '\0';

	do	{
		*--ptrr = arr[number % b];
		number /= b;
	} while (number != 0);

	if (signe)
		*--ptrr = signe;
	return (ptrr);
}

/**
 * removeComments - '#' with '\0'
 * @buff: str add to modify
 * Return: 0
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
