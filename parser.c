#include "simpleshell.h"

/**
 * isCmd - find if a file is an exe cmd
 * @info: infoP struct
 * @path: path
 * Return: 1 sinon 0
 */
int isCmd(infoP *info, char *path)
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
 * dupChars - duplicates characters
 * @pathst: path str
 * @strt: startindex
 * @stp: stopindex
 * Return: pointer
 */
char *dupChars(char *pathst, int strt, int stp)
{
	static char buff[1024];
	int i = 0, k = 0;

	for (k = 0, i = strt; i < stp; i++)
		if (pathst[i] != ':')
			buff[k++] = pathst[i];
	buff[k] = 0;
	return (buff);
}

/**
 * findPath - find cmd in path
 * @info: infoP struct
 * @pathst: path 
 * @cmd: command
 * Return: pathCmd
 */
char *findPath(infoP *info, char *pathst, char *cmd)
{
	int i = 0, curr = 0;
	char *path;

	if (!pathst)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathst[i] || pathst[i] == ':')
		{
			path = dupChars(pathst, curr, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathst[i])
				break;
			curr = i;
		}
		i++;
	}
	return (NULL);
}
