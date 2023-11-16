#include "simpleshell.h"

/**
 * _myenv - print cur env
 * @info: infoP struct
 * Return: 0
 */
int _myenv(infoP *info)
{
	printListStr(info->env);
	return (0);
}

/**
 * _getenv - get env var value
 * @info: infoP struct
 * @varname: envvar name
 * Return: val
 */
char *_getenv(infoP *info, const char *varname)
{
	listS *node = info->env;
	char *p;

	while (node)
	{
		p = startsWith(node->str, varname);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - init new env
 * @info: infoP struct
 *  Return: 0
 */
int _mysetenv(infoP *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - remove env var
 * @info: infoP struct
 *  Return: 0
 */
int _myunsetenv(infoP *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populateEnvList - populate envlist
 * @info: infoP struct
 * Return: 0
 */
int populateEnvList(infoP *info)
{
	listS *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		addNodeEnd(&node, environ[i], 0);
	info->env = node;
	return (0);
}
