#include "simpleshell.h"
/**
 * _myexit - exit shelll
 * @infoP: infoP structure
 * Return: exit
 */
int _myexit(infoP *infoP)
{
	int exitChecker;

	if (infoP->argv[1])  /* If there is an exit arguement */
	{
		exitChecker = _erratoi(infoP->argv[1]);
		if (exitChecker == -1)
		{
			infoP->stat = 2;
			printError(infoP, "Illegal number: ");
			_eputs(infoP->argv[1]);
			_eputchar('\n');
			return (1);
		}
		infoP->errn = _erratoi(infoP->argv[1]);
		return (-2);
	}
	infoP->errn = -1;
	return (-2);
}

/**
 * _mycd - cd in shell
 * @infoP: infoP structure
 *  Return: 0
 */
int _mycd(infoP *infoP)
{
	char *str, *dire, buffer[1024];
	int chdirRet;

	str = getcwd(buffer, 1024);
	if (!str)
		_puts("TODO: >>getcwd failmsg here<<\n");
	if (!infoP->argv[1])
	{
		dire = _getenv(infoP, "HOME=");
		if (!dire)
			chdirRet = chdir((dire = _getenv(infoP, "PWD=")) ? dire : "/");
		else
			chdirRet = chdir(dire);
	}
	else if (_strcmp(infoP->argv[1], "-") == 0)
	{
		if (!_getenv(infoP, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(infoP, "OLDPWD=")), _putchar('\n');
		chdirRet = chdir((dire = _getenv(infoP, "OLDPWD=")) ? dire : "/");
	}
	else
		chdirRet = chdir(infoP->argv[1]);
	if (chdirRet == -1)
	{
		printError(infoP, "Can't cd to ");
		_eputs(infoP->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(infoP, "OLDPWD", _getenv(infoP, "PWD="));
		_setenv(infoP, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - change cur dir
 * @infoP: infoP structure
 *  Return: 0
 */
int _myhelp(infoP *infoP)
{
	char **argArr;

	argArr = infoP->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argArr);
	return (0);
}
