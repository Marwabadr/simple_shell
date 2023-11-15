#include "simpleshell.h"
/**
 * _myhistory - history displayer
 * @infoP: infoP structure
 *  Return: 0
 */
int _myhistory(infoP *infoP)
{
	print_list(infoP->his);
	return (0);
}

/**
 * unsetAlias - sets alias to string
 * @infoP: infoP structure
 * @string: striing
 *
 * Return: 0
 */
int unsetAlias(infoP *infoP, char *string)
{
	char *pP, ch;
	int rett;

	pP = _strchr(string, '=');
	if (!pP)
		return (1);
	ch = *pP;
	*pP = 0;
	rett = deleteNodeAtIndex(&(infoP->al),
		getNodeIndex(infoP->al, nodeStartsWith(infoP->al, string, -1)));
	*pP = ch;
	return (rett);
}

/**
 * setAlias - sets al
 * @infoP: infoP structure
 * @string: striing
 *
 * Return: 0
 */
int setAlias(infoP *infoP, char *string)
{
	char *pP;

	pP = _strchr(string, '=');
	if (!pP)
		return (1);
	if (!*++pP)
		return (unsetAlias(infoP, string));

	unset_alias(infoP, string);
	return (addNodeEnd(&(infoP->al), string, 0) == NULL);
}

/**
 * printAlias - alias printer
 * @nodeA: node al
 *
 * Return: 0
 */
int printAlias(strL *nodeA)
{
	char *pP = NULL, *aA = NULL;

	if (nodeA)
	{
		pP = _strchr(nodeA->string, '=');
		for (aA = nodeA->string; aA <= pP; aA++)
			_putchar(*aA);
		_putchar('\'');
		_puts(pP + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - alias builder
 * @infoP: infoP structure
 *  Return: 0
 */
int _myalias(infoP *infoP)
{
	int i = 0;
	char *pP = NULL;
	list_t *nodeA = NULL;

	if (infoP->argc == 1)
	{
		nodeA = infoP->al;
		while (nodeA)
		{
			printAlias(nodeA);
			nodeA = nodeA->suc;
		}
		return (0);
	}
	for (i = 1; infoP->argv[i]; i++)
	{
		pP = _strchr(infoP->argv[i], '=');
		if (pP)
			setAlias(infoP, infoP->argv[i]);
		else
			printAlias(nodeStartsWith(infoP->al, infoP->argv[i], '='));
	}

	return (0);
}
