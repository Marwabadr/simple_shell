#include "simpleshell.h"

/**
 * listLen - length of list
 * @h: pointer
 * Return: size
 */
size_t listLen(const listS *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * listToStrings - sting array
 * @h: pointer
 * Return: string array
 */
char **listToStrings(listS *h)
{
	listS *nod = h;
	size_t i = listLen(h), j;
	char **stst;
	char *st;

	if (!h || !i)
		return (NULL);
	stst = malloc(sizeof(char *) * (i + 1));
	if (!stst)
		return (NULL);
	for (i = 0; nod; nod = nod->next, i++)
	{
		st = malloc(_strlen(nod->str) + 1);
		if (!st)
		{
			for (j = 0; j < i; j++)
				free(stst[j]);
			free(stst);
			return (NULL);
		}

		st = _strcpy(st, nod->str);
		stst[i] = st;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * printList - prints all listS
 * @h: pointer
 * Return: size
 */
size_t printList(const listS *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * nodeStartsWith - string start with prefix
 * @node: pointer
 * @prf: prefix
 * @c: next char
 * Return: node, null
 */
listS *nodeStartsWith(listS *node, char *prf, char c)
{
	char *p = NULL;

	while (node)
	{
		p = startsWith(node->str, prf);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * getNodeIndex - index of node
 * @h: pointer
 * @node: pointer
 *
 * Return: index of node or -1
 */
ssize_t getNodeIndex(listS *h, listS *node)
{
	size_t i = 0;

	while (h)
	{
		if (h == node)
			return (i);
		h = h->next;
		i++;
	}
	return (-1);
}
