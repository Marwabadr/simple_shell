#include "simpleshell.h"

/**
 * hsh - sh loop
 * @info: infoP struct
 * @agv: argv
 * Return: 0,1,errno
 */
int hsh(infoP *info, char **agv)
{
	ssize_t rr = 0;
	int builtinRet = 0;

	while (rr != -1 && builtinRet != -2)
	{
		clearInfo(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUFFLUSH);
		rr = getInput(info);
		if (rr != -1)
		{
			setInfo(info, agv);
			builtinRet = findBuiltin(info);
			if (builtinRet == -1)
				findCmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		freeInfo(info, 0);
	}
	writeHistory(info);
	freeInfo(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtinRet == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtinRet);
}

/**
 * findBuiltin - find builtin cmd
 * @info: infoP struct
 * Return: -1,0,1,-2
 */
int findBuiltin(infoP *info)
{
	int i, builtinRet = -1;
	builtinTable builtinTab[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtinTab[i].type; i++)
		if (_strcmp(info->argv[0], builtinTab[i].type) == 0)
		{
			info->line_count++;
			builtinRet = builtinTab[i].func(info);
			break;
		}
	return (builtinRet);
}

/**
 * findCmd - find cmd
 * @info: infoP struct
 * Return: void
 */
void findCmd(infoP *info)
{
	char *pa = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!isDelim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	pa = findPath(info, _getenv(info, "PATH="), info->argv[0]);
	if (pa)
	{
		info->path = pa;
		forkCmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && isCmd(info, info->argv[0]))
			forkCmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			printError(info, "not found\n");
		}
	}
}

/**
 * forkCmd - fork to run cmd
 * @info: tinfoP struct
 * Return: void
 */
void forkCmd(infoP *info)
{
	pid_t filspid;

	filspid = fork();
	if (filspid == -1)
	{
		perror("Error:");
		return;
	}
	if (filspid == 0)
	{
		if (execve(info->path, info->argv, getEnviron(info)) == -1)
		{
			freeInfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				printError(info, "Permission denied\n");
		}
	}
}
