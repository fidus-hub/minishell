#include "../minishell.h"

int	cd(t_headers *headers)
{
	char **args;

	args = headers->cmd_h->args;
	if (!args[1])
	{
		char*buf = getenv("HOME");
		if (buf == 0)
		{
			printf("HOME not set\n");
			return (1);
		}
		chdir(buf);
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("grissen");
		}
	}
	return (1);
}