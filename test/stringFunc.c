#include "simpleshell.h"

/**
 * inputBuf - buff cmd
 * @infoP: infoP structure
 * @buff: buffer
 * @l: len of variables
 * Return: byte
 */
ssize_t inputBuf(infoP *infoP, char **buff, size_t *l)
{
	ssize_t rr = 0;
	size_t len = 0;

	if (!*l)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if MY_USE_GETLINE
		rr = getline(buff, &len, stdin);
#else
		rr = _getline(infoP, buff, &len);
#endif
		if (rr > 0)
		{
			if ((*buff)[rr - 1] == '\n')
			{
				(*buff)[rr - 1] = '\0';
				rr--;
			}
			infoP->lCountFlag = 1;
			removeComments(*buff);
			buildHistoryList(infoP, *buff, infoP->hisCount++);
			{
				*l = rr;
				infoP->cmdBuf = buff;
			}
		}
	}
	return (rr);
}

/**
 * getInput - getLineInput
 * @infoP: infoP  stucture
 * Return: byte
 */
ssize_t getInput(infoP *infoP)
{
	static char *buff;
	static size_t i, j, len;
	ssize_t rr = 0;
	char **bufp = &(infoP->arg), *pP;

	_putchar(MY_BUF_F);
	rr = inputBuf(infoP, &buff, &len);
	if (rr == -1)
		return (-1);
	if (len)
	{
		j = i;
		pP = buff + i;

		checkChain(infoP, buff, &j, i, len);
		while (j < len)
		{
			if (isChain(infoP, buff, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			infoP->cmdBufType = MY_CAMD_NORM;
		}

		*bufp = pP;
		return (_strlen(pP));
	}

	*bufp = buff;
	return (rr);
}

/**
 * readBuf - read buff
 * @infoP: infoP structure
 * @buff: buffer
 * @i: size
 * Return: r
 */
ssize_t readBuf(infoP *infoP, char *buff, size_t *i)
{
	ssize_t rr = 0;

	if (*i)
		return (0);
	rr = read(infoP->readFd, buff, MY_READ_BUF_S);
	if (rr >= 0)
		*i = rr;
	return (rr);
}

/**
 * _getline - netLineInput from stdin
 * @infoP: infoP structure
 * @ptr: pointer
 * @l: sixe
 * Return: size
 */
int _getline(infoP *infoP, char **ptr, size_t *l)
{
	static char buf[MY_READ_BUF_S];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *newp = NULL, *c;

	p = *ptr;
	if (p && l)
		s = *l;
	if (i == len)
		i = len = 0;

	r = readBuf(infoP, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	newp = _realloc(p, s, s ? s + k : k + 1);
	if (!newp)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(newp, buf + i, k - i);
	else
		_strncpy(newp, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = newp;

	if (l)
		*l = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: signal num
 * Return: none
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(MY_BUF_F);
}
