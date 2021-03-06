#include "../minishell.h"

int	eexit(t_headers *headers)
{
	int j;
	char **args;

	args = headers->cmd_h->args;
	if (!args[1])
	{
		printf("exit\n");
		exit(g_var.exit_status);
	}

	if (args[2] != NULL)
	{
		printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		return (1);
	}

	j = 0;
	while (args[1][j])
	{
		if (!(isdigit(args[1][j])))
		{
			printf("exit\n");
			printf("%s %s: %s \n","minishell: exit:",args[1], "numeric argument required");
			exit(255);
		}
		j++;
	}
	if (args[2] == NULL)
	{
		g_var.exit_status = atoi(args[1]);
		printf("exit\n");
		exit(g_var.exit_status);
	}
}