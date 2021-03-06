#include "minishell.h"

void	ft_addbotcmd(t_headers *head, char *val)
{
	t_cmds	*stack;
	t_cmds	*to_add;

	to_add = malloc(sizeof(t_cmds));
	if (!to_add)
		exit(0);
	if (head->cmd_h == NULL)
	{
		to_add->cmd = add_str(val);
		to_add->file_h = NULL;
		to_add->file_f = NULL;
		to_add->next = NULL;
		to_add->prec = NULL;
		head->cmd_f = to_add;
		head->cmd_h = to_add;
	}
	else
	{
		stack = head->cmd_f;
		to_add->cmd = add_str(val);
		to_add->file_h = NULL;
		to_add->file_f = NULL;
		to_add->prec = stack;
		to_add->next = NULL;
		stack->next = to_add;
		head->cmd_f = to_add;
	}
}

void	ft_freefile(t_cmds *head)
{
	while (head->file_h)
		ft_delbotfile(head);
}

void	ft_delbotcmd(t_headers *head)
{
	t_cmds	*to_delete;
	t_cmds	*stack;

	if (head != NULL && head->cmd_h != NULL)
	{
		to_delete = head->cmd_f;
		if (!to_delete->prec)
		{
			ft_freefile(to_delete);
			ft_free(to_delete->args);
			free(to_delete->cmd);
			free(to_delete);
			head->cmd_h = NULL;
			head->cmd_f = NULL;
			to_delete = NULL;
		}
		else
		{
			stack = to_delete->prec;
			head->cmd_f = stack;
			stack->next = NULL;
			ft_freefile(to_delete);
			ft_free(to_delete->args);
			free(to_delete->cmd);
			free(to_delete);
			to_delete = NULL;
		}
	}
}

void	ft_complet(t_headers *header)
{
	t_cmds *new_cmd;
	new_cmd = header->cmd_h;
	while (new_cmd)
	{
		new_cmd->args = ft_flex(new_cmd->cmd, ' ');
		new_cmd = new_cmd->next;
	}
}

void	fill_cmd(t_headers *header, char	**str)
{
	int i;

	i = 0;
	while (str[i])
	{
		ft_addbotcmd(header, str[i]);
		i++;
	}
}

char	*to_find(char *str, int k)
{
	int		i;
	int		r;
	char	*var;

	i = 0;
	r = k + 1;
	while (str[r] && str[r] != '"' && str[r] != ' ' && str[r] != '\'' && str[r] != '$')
	{
		i++;
		r++;
	}
	var = malloc(sizeof(char) * (i + 2));
	r = i + 1;
	i = 0;
	while (i < r/*str[k] && str[k] != '"' && str[k] != ' ' && str[k] != '\'' && str[k] != '$'*/)
		var[i++] = str[k++];
	var[i] = '\0';
	return (var);
}

char	*findit(t_headers *header, char *var)
{
	t_env	*checkenv;
	char	*str;

	checkenv = header->env_h;
	if (var[1] != '_' && !ft_isalpha(var[1]))
	{
		var += 2;
		str = ft_strdup(var);
		return(str);
	}
	var++;
	while (checkenv)
	{
		if (!ft_strcmp(checkenv->var, var))
		{
			str = ft_strdup(checkenv->val);
			return (str);
			}
		checkenv = checkenv->suivant;
	}
	str = malloc(1);
	*str = '\0';
	return (str);
}

int		calculate_dollar(char *str, int i)
{
	int		d;

	d = 0;
	while (str[i] && str[i] == '$')
	{
		i++;
		d++;
	}
	return (d);	
}

void	checkdollar_cmd(t_headers *header)
{
	t_cmds *new_cmd;
	char	*var;
	char	*val;
	char	*rest;
	int		i;
	int		s_q;
	int		d_q;
	int		d;

	d = 0;
	i = 0;
	new_cmd = header->cmd_h;
	while (new_cmd)
	{
		d = 0;
		i = 0;
		s_q = 0;
		d_q = 0;
		while (new_cmd->cmd[i])
		{
			if (new_cmd->cmd[i] == '\'' && (d_q % 2) == 0)
					s_q++;
			if (new_cmd->cmd[i] == '"' && (s_q % 2) == 0)
					d_q++;
			if (new_cmd->cmd[i] == '$')
			{
				d = calculate_dollar(new_cmd->cmd, i);
				i += (d - 1);
			}
			if (new_cmd->cmd[i] == '$' && (d % 2) && new_cmd->cmd[i + 1] != '\0' && s_q % 2 == 0)
			{
				var = to_find(new_cmd->cmd, i);
				rest = ft_strdup(ft_strstr(new_cmd->cmd + i, var));
				val = findit(header, var); // STILL HAVE A PRBLM WHEN U DON'T FIND THE VAR
				new_cmd->cmd = ft_strjoin_dollarfree(new_cmd->cmd, val, i);
				new_cmd->cmd = ft_strjoin_free(new_cmd->cmd, rest);
				i = -1;
				free(var);
				free(val);
				free(rest);
			}
			i++;
		}
		new_cmd = new_cmd->next;
	}
}

void	save_cmd(t_headers *header, char **str)
{
	t_cmds	*new_cmd;
	t_file	*file;
	
	fill_cmd(header, str);
	checkdollar_cmd(header);
	checkredirection_cmd(header);
	ft_complet(header);
	execute(header);
	while (header->cmd_h)
		ft_delbotcmd(header);
	// new_cmd = header->cmd_h;
	// while (new_cmd)
	// {
	// 	file = new_cmd->file_h;
	// 	int i = 0;
	// 	while (new_cmd->args[i])
	// 	{
	// 		printf("%s\n",new_cmd->args[i]);
	// 		i++;
	// 	}
	// 	while (file)
	// 	{
	// 		printf("[type:%d][name:%s]\n",file->type,file->filename);
	// 		// printf("[%s]\n",file->filename);
	// 		file = file->next;
	// 	}
	// 	printf("----------------------\n");
	// 	new_cmd = new_cmd->next;
	// }
	// save(header, str);
	
}