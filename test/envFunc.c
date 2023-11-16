#include "simpleshell.h"

/**
 * _myenv - print cur env
 * @infoP: infoP sturcture
 * Return: 0
 */
int _myenv(infoP *infoP)
{
	printListStr(infoP->env);
	return (0);
}

/**
 * _getenv - value of env var
 * @infoP: infoP structure
 * @n: name
 *
 * Return: value
 */
char *_getenv(infoP *infoP, const char *n)
{
	strL *noden = infoP->env;
	char *pP;

	while (noden)
	{
		pP = startsWith(node->string, n);
		if (pP && *pP)
			return (pP);
		noden = noden->suc;
	}
	return (NULL);
}

/**
 * _mysetenv - init new env
 * @infoP: infoP structure
 *  Return: 0
 */
int _mysetenv(infoP *infoP)
{
	if (infoP->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(infoP, infoP->argv[1], infoP->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv -  rm env var
 * @infoP: infoP structure
 *  Return: 0
 */
int _myunsetenv(infoP *infoP)
{
	int i;

	if (infoP->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= infoP->argc; i++)
		_unsetenv(infoP, infoP->argv[i]);

	return (0);
}

/**
 * populateEnvList - populatesenvlist
 * @infoP: infoP structure
 * Return: 0
 */
int populateEnvList(infoP *infoP)
{
	strL *noden = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		addNodeEnd(&noden, environ[i], 0);
	infoP->env = noden;
	return (0);
}
