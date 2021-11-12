#include "../minishell.h"

int	execute(t_headers *header)
{
	t_cmds *ncmd;
	ncmd = header->cmd_h;
	int	i;

	dprintf(2,"%d\n", getpid());


	if (ncmd->args[0] == NULL)
	{
		return (1);
	}
	i = 0;
	if (strcmp(ncmd->args[0], "env") == 0)
		return (*builtin_func[4])(header->env_h);
	while(i < 4)
	{
		if (strcmp(ncmd->args[0], builtin_str[i]) == 0)
			return (*builtin_func[i])(ncmd->args);
		i++;
	}
	return launch(header);
}