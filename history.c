#include "simpleshell.h"

/**
 * getHistoryFile - his file
 * @info: infoP struct
 * Return: string
 */

char *getHistoryFile(infoP *info)
{
	char *buff, *dire;

	dire = _getenv(info, "HOME=");
	if (!dire)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dire) + _strlen(HISTFILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dire);
	_strcat(buff, "/");
	_strcat(buff, HISTFILE);
	return (buff);
}

/**
 * writeHistory - create a file
 * @info: infoP 
 * Return: 1 sinon -1
 */
int writeHistory(infoP *info)
{
	ssize_t filed;
	char *fn = getHistoryFile(info);
	listS *nod = NULL;

	if (!fn)
		return (-1);

	filed = open(fn, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fn);
	if (filed == -1)
		return (-1);
	for (nod = info->history; nod; nod = nod->next)
	{
		_putsfd(nod->str, filed);
		_putfd('\n', filed);
	}
	_putfd(BUFFLUSH, filed);
	close(filed);
	return (1);
}

/**
 * readHistory - read his
 * @info: infoP struct
 * Return: count of his sinon 0
 */
int readHistory(infoP *info)
{
	int i, l = 0, lcount = 0;
	ssize_t filed, rdl, fs = 0;
	struct stat str;
	char *buff = NULL, *fn = getHistoryFile(info);

	if (!fn)
		return (0);

	filed = open(fn, O_RDONLY);
	free(fn);
	if (filed == -1)
		return (0);
	if (!fstat(filed, &str))
		fs = str.st_size;
	if (fs < 2)
		return (0);
	buff = malloc(sizeof(char) * (fs + 1));
	if (!buff)
		return (0);
	rdl = read(filed, buff, fs);
	buf[fs] = 0;
	if (rdl <= 0)
		return (free(buff), 0);
	close(filed);
	for (i = 0; i < fs; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			buildHistoryList(info, buff + l, lcount++);
			l = i + 1;
		}
	if (l != i)
		buildHistoryList(info, buff + l, lcount++);
	free(buff);
	info->histcount = lcount;
	while (info->histcount-- >= HISTMAX)
		deleteNodeAtIndex(&(info->history), 0);
	renumberHistory(info);
	return (info->histcount);
}

/**
 * buildHistoryList - add elem to his list
 * @info: infoP struct
 * @buff: buffer
 * @lcount: linecount && histcount
 * Return: o
 */
int buildHistoryList(infoP *info, char *buff, int lcount)
{
	listS *nod = NULL;

	if (info->history)
		nod = info->history;
	addNodeEnd(&nod, buff, lcount);

	if (!info->history)
		info->history = nod;
	return (0);
}

/**
 * renumberHistory - renumbers the history linked list after changes
 * @info: infoP struct
 * Return: new count of his
 */
int renumberHistory(infoP *info)
{
	listS *nod = info->history;
	int i = 0;

	while (nod)
	{
		nod->num = i++;
		nod = nod->next;
	}
	return (info->histcount = i);
}
