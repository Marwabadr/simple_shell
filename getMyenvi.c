#include "simpleshell.h"

/**
 * getEnviron - string copied in env
 * @info: infoP structure
 * Return: char
 */
char **getEnviron(infoP *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = listToStrings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - remove envvar
 * @info: infoP structure
 * @v: env var
 *  Return: 1 del 0 sinon
 */
int _unsetenv(infoP *info, char *v)
{
	listS *nod = info->env;
	size_t i = 0;
	char *ptr;

	if (!nod || !v)
		return (0);

	while (nod)
	{
		ptr = startsWith(nod->str, v);
		if (ptr && *ptr == '=')
		{
			info->env_changed = deleteNodeAtIndex(&(info->env), i);
			i = 0;
			nod = info->env;
			continue;
		}
		nod = nod->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - init a new env var
 * @info: infoP sruct
 * @v: env var
 * @val: env var value
 *  Return: 0
 */
int _setenv(infoP *info, char *v, char *val)
{
	char *buff = NULL;
	listS *nod;
	char *ptr;

	if (!v || !val)
		return (0);

	buff = malloc(_strlen(v) + _strlen(val) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, v);
	_strcat(buff, "=");
	_strcat(buff, val);
	nod = info->env;
	while (nod)
	{
		ptr = startsWith(nod->str, v);
		if (ptr && *ptr == '=')
		{
			free(nod->str);
			nod->str = buff;
			info->env_changed = 1;
			return (0);
		}
		nod = nod->next;
	}
	addNodeEnd(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}
