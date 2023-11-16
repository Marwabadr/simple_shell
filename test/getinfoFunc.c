#include "simpleshell.h"

/**
 * clearInfo - init infoP
 * @infoP: infoP structure
 */
void clearInfo(infoP *infoP)
{
	infoP->arg = NULL;
	infoP->argv = NULL;
	infoP->path = NULL;
	infoP->argc = 0;
}

/**
 * setInfo - init infoP
 * @infoP: infoP structure
 * @agv: agrv
 */
void setInfo(infoP *infoP, char **agv)
{
	int i = 0;

	infoP->fileName = agv[0];
	if (infoP->arg)
	{
		infoP->argv = strtow(infoP->arg, " \t");
		if (!infoP->argv)
		{

			infoP->argv = malloc(sizeof(char *) * 2);
			if (infoP->argv)
			{
				infoP->argv[0] = _strdup(infoP->arg);
				infoP->argv[1] = NULL;
			}
		}
		for (i = 0; infoP->argv && infoP->argv[i]; i++)
			;
		infoP->argc = i;

		replaceAlias(infoP);
		replaceVars(infoP);
	}
}

/**
 * freeInfo - free infoP
 * @infoP: infoP structure
 * @alll: all fields
 */
void freeInfo(infoP *infoP, int alll)
{
	ffree(infoP->argv);
	infoP->argv = NULL;
	infoP->path = NULL;
	if (alll)
	{
		if (!infoP->cmdBuf)
			free(infoP->arg);
		if (infoP->env)
			freeList(&(infoP->env));
		if (infoP->his)
			freeList(&(infoP->his));
		if (infoP->al)
			freeList(&(infoP->al));
		ffree(infoP->envi);
			infoP->envi = NULL;
		bfree((void **)infoP->cmdBuf);
		if (infoP->readFd > 2)
			close(infoP->readFd);
		_putchar(MY_BUF_F);
	}
}
