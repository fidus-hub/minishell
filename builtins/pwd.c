#include "../minishell.h"

int	pwd(char **args)
{
	long n;
	char *buf;

	buf = getcwd(NULL, 0);
	if (buf == NULL)
	{
		perror("getcwd");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("%s\n", buf);
	}
	free(buf);
	return (EXIT_SUCCESS);
}