#include "simpleshell.h"

/**
 * listLen - list length
 * @h: poiter
 * Return: len of list
 */
size_t listLen(const strL *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->suc;
		i++;
	}
	return (i);
}

/**
 * listToStrings - list->string array
 * @head: pointer
 * Return: array
 */
char **listToStrings(atrL *head)
{
	strL *node = head;
	size_t i = listLen(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->suc, i++)
	{
		str = malloc(_strlen(node->string) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->string);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * printList - print strL elements
 * @h: pointer
 *
 * Return: len of list
 */
size_t printList(const strL *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->n, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->string ? h->string : "(nil)");
		_puts("\n");
		h = h->suc;
		i++;
	}
	return (i);
}

/**
 * nodeStartsWith - node stars with
 * @node: pointer
 * @prefix: string
 * @c: next character
 * Return: node
 */
strL *nodeStartsWith(strL *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->string, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->suc;
	}
	return (NULL);
}

/**
 * getNodeIndex - index of node
 * @head: pointer
 * @node: pointer
 * Return: index
 */
ssize_t getNodeIndex(strL *head, strL *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->suc;
		i++;
	}
	return (-1);
}
