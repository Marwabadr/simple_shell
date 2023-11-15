#include "simpleshell.h"

/**
 * addNode - add node
 * @head: poiter head to node
 * @str: string
 * @num: index
 * Return: len of list
 */
strL *add_node(list_t **head, const char *str, int num)
{
	strL *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->n = num;
	if (str)
	{
		new_head->string = _strdup(str);
		if (!new_head->string)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->suc = *head;
	*head = new_head;
	return (new_head);
}

/**
 * addNodeEnd - add to end
 * @head: poiter head to node
 * @str: string
 * @num: index
 * Return: len of list
 */
strL *addNodeEnd(strL **head, const char *str, int num)
{
	strL *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(strL));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(strL));
	new_node->n = num;
	if (str)
	{
		new_node->string = _strdup(str);
		if (!new_node->string)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->suc)
			node = node->suc;
		node->suc = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * printListStr - print string of the list
 * @h: pointer
 * Return: len of list
 */
size_t printListStr(const strL *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->string ? h->string : "(nil)");
		_puts("\n");
		h = h->suc;
		i++;
	}
	return (i);
}

/**
 * deleteNodeAtIndex - delete node
 * @head:  poiter head to node
 * @index: index
 * Return: 1
 */
int deleteNodeAtIndex(steL **head, unsigned int index)
{
	strL *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->suc;
		free(node->string);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->suc = node->suc;
			free(node->string);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->suc;
	}
	return (0);
}

/**
 * freeList - free all nodes
 * @headPtr:  poiter head to node
 *
 * Return: void
 */
void freeList(steL **headPtr)
{
	strL *node, *next_node, *head;

	if (!headPtr || !*headPtr)
		return;
	head = *headPtr;
	node = head;
	while (node)
	{
		next_node = node->suc;
		free(node->string);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
