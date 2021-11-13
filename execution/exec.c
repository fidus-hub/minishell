#include "../minishell.h"

int	execute(t_headers *header)
{
	t_cmds *ncmd;
	ncmd = header->cmd_h;
	int	i;


	if (ncmd->args[0] == NULL)
	{
		return (1);
	}
	i = 0;
	while(i < 6)
	{
		if (strcmp(ncmd->args[0], builtin_str[i]) == 0)
			return (*builtin_func[i])(header);
		i++;
	}
	return launch(header);
}