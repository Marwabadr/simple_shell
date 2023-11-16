#include "simpleshell.h"

/**
 * _myhistory - afiche his list
 * @info: infoP struct
 *  Return: 0
 */
int _myhistory(infoP *info)
{
	printList(info->history);
	return (0);
}

/**
 * unset_alias - set al to str
 * @info: infoP struct
 * @stral: str alais
 *
 * Return: retu sinon 1
 */
int unsetAlias(infoP *info, char *stral)
{
	char *pp, cp;
	int retu;

	pp = _strchr(stral, '=');
	if (!pp)
		return (1);
	cp = *pp;
	*pp = 0;
	retu = deleteNodeAtIndex(&(info->alias),
		getNodeIndex(info->alias, nodeStartsWith(info->alias, stral, -1)));
	*pp = cp;
	return (retu);
}

/**
 * setAlias - set alias to str
 * @info: infoP struct
 * @stral: stral
 * Return: 0,1,errno
 */
int setAlias(infoP *info, char *stral)
{
	char *pp;

	pp = _strchr(stral, '=');
	if (!pp)
		return (1);
	if (!*++pp)
		return (unsetAlias(info, stral));

	unsetAlias(info, stral);
	return (addNodeEnd(&(info->alias), stral, 0) == NULL);
}

/**
 * printAlias - printalias
 * @nodeal: alias node
 *
 * Return: 0 sinon 1
 */
int printAlias(listS *nodeal)
{
	char *ptr = NULL, *ap = NULL;

	if (nodeal)
	{
		ptr = _strchr(nodeal->str, '=');
		for (ap = node->str; ap <= ptr; ap++)
			_putchar(*ap);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - is like man alias
 * @info: infoP struct
 *  Return: 0
 */
int _myalias(infoP *info)
{
	int i = 0;
	char *ptr = NULL;
	listS *nod = NULL;

	if (info->argc == 1)
	{
		nod = info->alias;
		while (nod)
		{
			printAlias(nod);
			nod = nod->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		ptr = _strchr(info->argv[i], '=');
		if (ptr)
			setAlias(info, info->argv[i]);
		else
			printAlias(nodeStartsWith(info->alias, info->argv[i], '='));
	}

	return (0);
}
