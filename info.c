#include "simpleshell.h"

/**
 * clearInfo - init infoP struct
 * @info: infoP struct
 */
void clearInfo(infoP *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * setInfo - init infoP struct
 * @info: struct address
 * @agv: argument vector
 */
void setInfo(infoP *info, char **agv)
{
	int i = 0;

	info->fname = agv[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replaceAlias(info);
		replaceVars(info);
	}
}

/**
 * freeInfo - free infoP struct
 * @info: infoP struct
 * @allf: all field->true 
 */
void free_info(infoP *info, int allf)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (allf)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			freeList(&(info->env));
		if (info->history)
			freeList(&(info->history));
		if (info->alias)
			freeList(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUFFLUSH);
	}
}
