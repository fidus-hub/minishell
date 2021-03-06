#include "../minishell.h"

void	redirection_inside_loop(int *in, int *out, t_file *file_h) 
{
	if (file_h->filename && (file_h->type == 1 || file_h->type == 2))
	{
		if (*out != STDOUT_FILENO)
			close(*out);
		if (file_h->type == 1)
			*out = open(file_h->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (file_h->type == 2)
			*out = open(file_h->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (file_h->filename && file_h->type == 3)
	{
		if (*in != STDIN_FILENO)
			close(*in);
		*in = open(file_h->filename, O_RDONLY, 0644);
	}
}

void	redirection(t_cmds *cmd_h)
{
	t_file *nfile;
	nfile = cmd_h->file_h;
	int in = STDIN_FILENO;
	int out = STDOUT_FILENO;
	
	while (nfile != NULL)
	{
		redirection_inside_loop(&in, &out, nfile);
		nfile = nfile->next;
	}
	if (in > 2)
	{
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (out > 2)
	{
		dup2(out, STDOUT_FILENO);
		close(out);
	}
}
