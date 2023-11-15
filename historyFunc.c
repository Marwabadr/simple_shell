#include "simpleshell.h"

/**
 * getHistoryFile - getHistoryFil
 * @infoP: infoP structure
 * Return: string
 */

char *getHistoryFile(infoP *infoP)
{
	char *buf, *dir;

	dir = _getenv(infoP, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(MY_HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, MY_HIST_FILE);
	return (buf);
}

/**
 * writeHistory - create file
 * @infoP: infoP structure
 * Return: 1
 */
int writeHistory(infoP *infoP)
{
	ssize_t fd;
	char *filename = getHistoryFile(infoP);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = infoP->his; node; node = node->suc)
	{
		_putsfd(node->string, fd);
		_putfd('\n', fd);
	}
	_putfd(MY_BUF_F, fd);
	close(fd);
	return (1);
}

/**
 * readHistory - read his
 * @infoP: infoP structure
 *
 * Return: hisCount
 */
int readHistory(infoP *infoP)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = getHistoryFile(infoP);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			buildHistoryList(infoP, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		buildHistoryList(infoP, buf + last, linecount++);
	free(buf);
	infoP->hisCount = linecount;
	while (infoP->hisCount-- >= MY_HIST_MAX)
		deleteNodeAtIndex(&(info->history), 0);
	renumberHistory(infoP);
	return (infoP->hisCount);
}

/**
 * buildHistoryList - add to his list
 * @infoP: infoP structure
 * @buf: buffer
 * @linecount: count
 * Return: 0
 */
int buildHistoryList(infoP *infoP, char *buf, int linecount)
{
	strL *node = NULL;

	if (infoP->his)
		node = infoP->his;
	addNodeEnd(&node, buf, linecount);

	if (!infoP->his)
		infoP->his = node;
	return (0);
}

/**
 * renumberHistory - renumberHistory
 * @infoP: infoP structure
 * Return: hisCount
 */
int renumberHistory(infoP *infoP)
{
	strL *node = infoP->his;
	int i = 0;

	while (node)
	{
		node->n = i++;
		node = node->suc;
	}
	return (infoP->hisCount = i);
}
