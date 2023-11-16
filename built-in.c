#include "simpleshell.h"

/**
 * _myexit - exit sh
 * @info: infoP structure
 *  Return:  0 exit
 */
int _myexit(infoP *info)
{
	int exitC;

	if (info->argv[1])
	{
		exitC = _erratoi(info->argv[1]);
		if (exitC == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - cd func
 * @info: infoP structure
 *  Return: 0
 */
int _mycd(infoP *info)
{
	char *st, *dire, buff[1024];
	int chdirRet;

	st = getcwd(buff, 1024);
	if (!st)
		_puts("TODO: >>getcwd failure msg here<<\n");
	if (!info->argv[1])
	{
		dire = _getenv(info, "HOME=");
		if (!dire)
			chdirRet = chdir((dire = _getenv(info, "PWD=")) ? dire : "/");
		else
			chdirRet = chdir(dire);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(st);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdirRet = chdir((dire = _getenv(info, "OLDPWD=")) ? dire : "/");
	}
	else
		chdirRet = chdir(info->argv[1]);
	if (chdirRet == -1)
	{
		printError(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * _myhelp - change cur dir
 * @info: ingoP structure
 *  Return: 0
 */
int _myhelp(infoP *info)
{
	char **argTable;

	argTable = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argTable);
	return (0);
}
