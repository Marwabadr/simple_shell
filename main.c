#include "simpleshell.h"

/**
 * main - main entry point
 * @agc: argc
 * @agv: argv
 *
 * Return: 0 sinon 1
 */
int main(int agc, char **agv)
{
	infoP info[] = { INFOINIT };
	int filed = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (filed)
		: "r" (filed));

	if (agc == 2)
	{
		filed = open(av[1], O_RDONLY);
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
				_eputchar(BUFFLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = filed;
	}
	populateEnvList(info);
	readHistory(info);
	hsh(info, agv);
	return (EXIT_SUCCESS);
}
