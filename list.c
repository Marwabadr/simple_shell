#include "simpleshell.h"

/**
 * addNode - add a node
 * @h: address
 * @st: string
 * @n: node index
 * Return: size of list of node
 */
listS *addNode(listS **h, const char *st, int n)
{
	listS *newhead;

	if (!h)
		return (NULL);
	newhead = malloc(sizeof(listS));
	if (!newhead)
		return (NULL);
	_memset((void *)newhead, 0, sizeof(listS));
	newhead->num = n;
	if (st)
	{
		newhead->str = _strdup(st);
		if (!newhead->str)
		{
			free(newhead);
			return (NULL);
		}
	}
	newhead->next = *h;
	*h = newhead;
	return (newhead);
}

/**
 * addNodeEnd - add a node end
 * @h: address
 * @st: string
 * @n: node index
 * Return: size of list of node
 */
listS *addNodeEnd(listS **h, const char *st, int n)
{
	listS *newnode, *nod;

	if (!h)
		return (NULL);

	nod = *h;
	newnode = malloc(sizeof(listS));
	if (!newnode)
		return (NULL);
	_memset((void *)newnode, 0, sizeof(listS));
	newnode->num = n;
	if (st)
	{
		newnode->str = _strdup(st);
		if (!newnode->str)
		{
			free(newnode);
			return (NULL);
		}
	}
	if (nod)
	{
		while (nod->next)
			nod = nod->next;
		nod->next = newnode;
	}
	else
		*h = newnode;
	return (newnode);
}

/**
 * printListStr - print list of string
 * @h: pointer first node
 * Return: size of list of node
 */
size_t printListStr(const listS *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * deleteNodeAtIndex - delete node
 * @h: address
 * @ind: index
 * Return: 1 sinon 0
 */
int deleteNodeAtIndex(listS **h, unsigned int ind)
{
	listS *nod, *prevnod;
	unsigned int i = 0;

	if (!h || !*h)
		return (0);

	if (!ind)
	{
		nod = *h;
		*h = (*h)->next;
		free(nod->str);
		free(nod);
		return (1);
	}
	nod = *h;
	while (nod)
	{
		if (i == ind)
		{
			prevnod->next = nod->next;
			free(nod->str);
			free(nod);
			return (1);
		}
		i++;
		prevnod = nod;
		nod = nod->next;
	}
	return (0);
}

/**
 * freeList - free all list
 * @hptr: address
 * Return: void
 */
void freeList(listS **hptr)
{
	listS *nod, *nextnod, *h;

	if (!hptr || !*hptr)
		return;
	h = *hptr;
	nod = h;
	while (nod)
	{
		nextnod = nod->next;
		free(nod->str);
		free(nod);
		nod = nextnod;
	}
	*hptr = NULL;
}
