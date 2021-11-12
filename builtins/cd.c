#include "../minishell.h"

int	cd(char **args)
{
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