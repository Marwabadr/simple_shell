#include "simpleshell.h"

/**
 * main - entry point
 * @agc: argc
 * @agv: argv
 * Return: 0
 */
int main(int agc, char **agv)
{
	infoP infoP[] = { INFO_INIT };
	int filed = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (filed)
		: "r" (filed));

	if (agc == 2)
	{
		filed = open(agv[1], O_RDONLY);
		if (filed == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(agv[0]);
				_eputs(": 0: Can't open ");
				_eputs(agv[1]);
				_eputchar('\n');
				_eputchar(MY_BUF_F);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		infoP->readFd = filed;
	}
	populateEnvList(infoP);
	readHistory(infoP);
	hsh(infoP, agv);
	return (EXIT_SUCCESS);
}
