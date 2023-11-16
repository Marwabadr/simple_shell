#include "simpleshell.h"

/**
 * isChain - chain delim
 * @info: infoP struct
 * @buff: buffer
 * @pb: addresse
 * Return: 1 sinon 0
 */
int isChain(infoP *info, char *buff, size_t *pb)
{
	size_t j = *pb;

	if (buff[j] == '|' && buff[j + 1] == '|')
	{
		buff[j] = 0;
		j++;
		info->cmd_buf_type = CMDOR;
	}
	else if (buff[j] == '&' && buff[j + 1] == '&')
	{
		buff[j] = 0;
		j++;
		info->cmd_buf_type = CMDAND;
	}
	else if (buff[j] == ';')
	{
		buff[j] = 0;
		info->cmd_buf_type = CMDCHAIN;
	}
	else
		return (0);
	*pb = j;
	return (1);
}

/**
 * checkChain - check chain
 * @info: infoP struct
 * @buff:buffer
 * @pt: adresse
 * @i: first pos
 * @len: len of buffer
 * Return: none void
 */
void checkChain(infoP *info, char *buff, size_t *pt, size_t i, size_t len)
{
	size_t j = *pt;

	if (info->cmd_buf_type == CMDAND)
	{
		if (info->status)
		{
			buff[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMDOR)
	{
		if (!info->status)
		{
			buff[i] = 0;
			j = len;
		}
	}

	*pt = j;
}

/**
 * replaceAlias - replace alias
 * @info: infoP struct
 * Return: 1 sinon 0
 */
int replaceAlias(infoP *info)
{
	int i;
	listS *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = nodeStartsWith(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replaceVars - replacevar
 * @info: infoP struct
 * Return: 1 sinon 0
 */
int replaceVars(infoP *info)
{
	int i = 0;
	listS *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replaceString(&(info->argv[i]),
				_strdup(convertNumber(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replaceString(&(info->argv[i]),
				_strdup(convertNumber(getpid(), 10, 0)));
			continue;
		}
		node = nodeStartsWith(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replaceString(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replaceString(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replaceString - replacestring
 * @os: old str
 * @ns: new str
 * Return: 1 sinon 0
 */
int replaceString(char **os, char *ns)
{
	free(*os);
	*os = ns;
	return (1);
}
