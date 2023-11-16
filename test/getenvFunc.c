#include "simpleshell.h"

/**
 * getEnviron - string env
 * @infoP: infoP structure
 * Return: Always 0
 */
char **getEnviron(infoP *infoP)
{
	if (!infoP->envi || infoP->envChanged)
	{
		info->envi = listToStrings(infoP->envi);
		infoP->envChanged = 0;
	}

	return (infoP->envi);
}

/**
 * _unsetenv - remove env
 * @infoP: infoP
 * @vars: string
 *  Return: 1
 */
int _unsetenv(infoP *infoP, char *vars)
{
	strL *nodea = infoP->env;
	size_t i = 0;
	char *pP;

	if (!nodea || !vars)
		return (0);

	while (nodea)
	{
		pP = startsWith(nodea->string, vars);
		if (pP && *pP == '=')
		{
			infoP->envChanged = deleteNodeAtIndex(&(infoP->env), i);
			i = 0;
			nodea = infoP->env;
			continue;
		}
		nodea = nodea->suc;
		i++;
	}
	return (infoP->envChanged);
}

/**
 * _setenv - init env
 * @infoP: infoP structure
 * @vars: env var
 * @vals: env var val
 *  Return: 0
 */
int _setenv(infoP *infoP, char *vars, char *vals)
{
	char *buff = NULL;
	strL *nodea;
	char *pP;

	if (!vars || !vals)
		return (0);

	buff = malloc(_strlen(vars) + _strlen(vals) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, vars);
	_strcat(buff, "=");
	_strcat(buff, vals);
	nodea = infoP->env;
	while (nodea)
	{
		pP = startsWith(nodea->string, vars);
		if (pP && *pP == '=')
		{
			free(nodea->string);
			nodea->string = buff;
			infoP->envChanged = 1;
			return (0);
		}
		nodea = nodea->suc;
	}
	addNodeEnd(&(infoP->env), buff, 0);
	free(bufF);
	infoP->envChanged = 1;
	return (0);
}
