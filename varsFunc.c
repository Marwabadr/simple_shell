#include "simpleshell.h"

/**
 * isChain - test if cur char in bufr is a chain delim
 * @infoP: infoP structure
 * @buf: buffer
 * @p: address
 * Return: 1
 */
int isChain(infoP *infoP, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		infoP->cmdBufType = MY_CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		infoP->cmdBufType = MY_CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		infoP->cmdBufType = MY_CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * checkChain - check chaining based on last status
 * @infoP: infoP structure
 * @buf: buffer
 * @p: address
 * @i: position
 * @len: length of buf
 * Return: none
 */
void checkChain(infoP *infoP, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (infoP->cmdBufType == MY_CMD_AND)
	{
		if (infoP->stat)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (infoP->cmdBufType == MY_CMD_OR)
	{
		if (!infoP->stat)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replaceAlias - replace  alias
 * @infoP: infoP structure
 * Return: 1
 */
int replaceAlias(infoP *infoP)
{
	int i;
	strL *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(infoP->al, infoP->argv[0], '=');
		if (!node)
			return (0);
		free(infoP->argv[0]);
		p = _strchr(node->string, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		infoP->argv[0] = p;
	}
	return (1);
}

/**
 * replaceVars - replace var
 * @infoP: infoP structure
 * Return: 1
 */
int replaceVars(infoP *infoP)
{
	int i = 0;
	strL *node;

	for (i = 0; infoP->argv[i]; i++)
	{
		if (infoP->argv[i][0] != '$' || !infoP->argv[i][1])
			continue;

		if (!_strcmp(infoP->argv[i], "$?"))
		{
			replaceString(&(infoP->argv[i]),
				_strdup(convertNumber(infoP->status, 10, 0)));
			continue;
		}
		if (!_strcmp(infoP->argv[i], "$$"))
		{
			replaceString(&(infoP->argv[i]),
				_strdup(convertNumber(getpid(), 10, 0)));
			continue;
		}
		node = nodeStartsWith(infoP->env, &infoP->argv[i][1], '=');
		if (node)
		{
			replaceString(&(infoP->argv[i]),
				_strdup(_strchr(node->string, '=') + 1));
			continue;
		}
		replacestring(&infoP->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replaceString - replace string
 * @old: address
 * @new: string
 * Return: 1
 */
int replaceString(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
