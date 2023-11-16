#include "simpleshell.h"

/**
 * execute_command - execute a cmd
 * @cmd: command
 * Return: integer
 */
int execute_command(char *cmd)
{
	int ret = access(cmd, X_OK);

	if (ret == 0)
	{
		pid_t pid = fork();

		if (pid == 0)
		{
			execl(cmd, cmd, NULL);
			exit(EXIT_SUCCESS);
		}
		else if (pid > 0)
		{
			wait(NULL);
		}
		else
		{
			perror("fork");
		}
		return (0);
	}
	else
	{
		print_error(cmd);
		return (-1);
	}
}
/**
 * print_error - print error fot the cmd
 * @cmd: command
 * Return: none void
 */
void print_error(char *cmd)
{
	fprintf(stderr, "%s: No such file or directory\n", cmd);
}
