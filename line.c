#include "simpleshell.h"

/**
 * inputBuf - bufferchainedcmd
 * @info: infoP struct
 * @buff:buffer
 * @l: address
 * Return: byte
 */
ssize_t inputBuf(infoP *info, char **buff, size_t *l)
{
	ssize_t rr = 0;
	size_t lenp = 0;

	if (!*l)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USEGETLINE
		rr = getline(buff, &lenp, stdin);
#else
		rr = _getline(info, buff, &lenp);
#endif
		if (rr > 0)
		{
			if ((*buff)[rr - 1] == '\n')
			{
				(*buff)[rr - 1] = '\0';
				rr--;
			}
			info->linecount_flag = 1;
			removeComments(*buff);
			buildHistoryList(info, *buff, info->histcount++);
			{
				*l = rr;
				info->cmd_buf = buff;
			}
		}
	}
	return (rr);
}

/**
 * getInput - get a line
 * @info: infoP struct
 * Return: byte
 */
ssize_t getInput(infoP *info)
{
	static char *buff;
	static size_t i, j, l;
	ssize_t rr = 0;
	char **buffp = &(info->arg), *ptr;

	_putchar(BUFFLUSH);
	rr = inputBuf(info, &buff, &l);
	if (rr == -1)
		return (-1);
	if (l)
	{
		j = i;
		ptr = buff + i;

		checkChain(info, buff, &j, i, l);
		while (j < l)
		{
			if (isChain(info, buff, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= l)
		{
			i = l = 0;
			info->cmd_buf_type = CMDNORM;
		}

		*buffp = ptr;
		return (_strlen(ptr));
	}

	*buffp = buff;
	return (rr);
}

/**
 * readBuf - read buffer
 * @info: infoP struct
 * @buff: buffer
 * @i: size
 * Return: rr
 */
ssize_t readBuf(infoP *info, char *buff, size_t *i)
{
	ssize_t rr = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buff, READBUFSIZE);
	if (rr >= 0)
		*i = rr;
	return (rr);
}

/**
 * _getline - get  nextline
 * @info: infoP struct
 * @ptr:pointer
 * @leng: size of buffer
 * Return: st
 */
int _getline(infoP *info, char **ptr, size_t *leng)
{
	static char buff[READBUFSIZE];
	static size_t i, len;
	size_t k;
	ssize_t rr = 0, st = 0;
	char *pp = NULL, *newp = NULL, *cp;

	pp = *ptr;
	if (pp && leng)
		st = *leng;
	if (i == len)
		i = len = 0;

	rr = readBuf(info, buff, &len);
	if (rr == -1 || (rr == 0 && len == 0))
		return (-1);

	cp = _strchr(buff + i, '\n');
	k = cp ? 1 + (unsigned int)(cp - buff) : len;
	newp = _realloc(pp, st, st ? st + k : k + 1);
	if (!newp)
		return (pp ? free(pp), -1 : -1);

	if (st)
		_strncat(newp, buff + i, k - i);
	else
		_strncpy(newp, buff + i, k - i + 1);

	st += k - i;
	i = k;
	pp = newp;

	if (leng)
		*leng = st;
	*ptr = pp;
	return (st);
}

/**
 * sigintHandler - block ctrl C
 * @sig_num: signal number
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFLUSH);
}
