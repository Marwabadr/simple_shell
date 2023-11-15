#include "simpleshell.h"

/**
 * isCmd - executable cmd
 * @info: infoP structure
 * @path: path
 * Return: 1
 */
int is_cmd(infoP *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dupChars - dupli char
 * @pathstr: path
 * @start: index start
 * @stop: stop index
 * Return: pointer
 */
char *dupChars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * findPath - findPath
 * @infoP: infoP structure
 * @pathstr: path
 * @cmd: command
 * Return: path of cmd
 */
char *findPath(infoP *infoP, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && startsWith(cmd, "./"))
	{
		if (isCmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dupChars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (isCmd(infoP, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
