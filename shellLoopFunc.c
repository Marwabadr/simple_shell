#include "simpleshell.h"

/**
 * hsh - main shell loop
 * @infoP: infoP structure
 * @av: argv
 * Return: 0
 */
int hsh(infoP *infoP, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clearInfo(infoP);
		if (interactive(infoP))
			_puts("$ ");
		_eputchar(MY_BUF_F);
		r = getInput(infoP);
		if (r != -1)
		{
			setInfo(infoP, av);
			builtin_ret = findBuiltin(infoP);
			if (builtin_ret == -1)
				findCmd(infoP);
		}
		else if (interactive(infoP))
			_putchar('\n');
		freeInfo(infoP, 0);
	}
	writeHistory(info);
	freeInfo(infoP, 1);
	if (!interactive(infoP) && infoP->stat)
		exit(infoP->stat);
	if (builtin_ret == -2)
	{
		if (infoP->errn == -1)
			exit(infoP->stat);
		exit(infoP->errn);
	}
	return (builtin_ret);
}

/**
 * findBuiltin - find builtin cmd
 * @infoP: infoP structure
 * Return: -1
 */
int findBuiltin(infoP *infoP)
{
	int i, built_in_ret = -1;
	builtinTable builtintbl[] = {
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

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(infoP->argv[0], builtintbl[i].type) == 0)
		{
			infoP->lCount++;
			built_in_ret = builtintbl[i].func(infoP);
			break;
		}
	return (built_in_ret);
}

/**
 * findCmd - find a cmd
 * @infoP: infoP structure
 * Return: none
 */
void findCmd(infoP *infoP)
{
	char *path = NULL;
	int i, k;

	infoP->path = infoP->argv[0];
	if (infoP->lCountFlag == 1)
	{
		infoP->lineCount++;
		info->lCountFlag = 0;
	}
	for (i = 0, k = 0; infoP->arg[i]; i++)
		if (!is_delim(infoP->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = findPath(infoP, _getenv(info, "PATH="), infoP->argv[0]);
	if (path)
	{
		infoP->path = path;
		forkCmd(infoP);
	}
	else
	{
		if ((interactive(infoP) || _getenv(infoP, "PATH=")
			|| infoP->argv[0][0] == '/') && isCmd(infoP, infoP->argv[0]))
			forkCmd(infoP);
		else if (*(infoP->arg) != '\n')
		{
			infoP->stat = 127;
			printError(infoP, "not found\n");
		}
	}
}

/**
 * forkCmd - fork cmd
 * @infoP: infoP structure
 * Return: none
 */
void forkCmd(infoP *infoP)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(infoP->path, infoP->argv, getEnviron(infoP)) == -1)
		{
			freeInfo(infoP, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(infoP->stat));
		if (WIFEXITED(infoP->stat))
		{
			infoP->stat = WEXITSTATUS(infoP->stat);
			if (infoP->stat == 126)
				printError(infoP, "Permission denied\n");
		}
	}
}

