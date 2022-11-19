#include "../../includes/minishell.h"

void	free_redirections(t_redir_list_ms *redir_list)
{
	t_redir_list_ms	*redir_list_cpy;

	while (redir_list->next)
	{
		free(redir_list->file_name);
		redir_list_cpy = redir_list->next;
		free(redir_list);
		redir_list = redir_list_cpy;
	}
}

void	free_all_redirections(t_all_redir_ms *all_redirs)
{
	if (all_redirs->outfile)
		free(all_redirs->outfile);
	if (all_redirs->infile)
		free(all_redirs->infile);
	free_redirections(all_redirs->first_redir);
	free(all_redirs);
}

void	free_context(t_context_ms *cmd_lst)
{
	t_context_ms	*cmd_lst_cpy;

	while (cmd_lst)
	{
		free(cmd_lst->pipeline);
		if (cmd_lst->all_redirs)
			free_all_redirections(cmd_lst->all_redirs);
		cmd_lst_cpy = cmd_lst->next;
		free(cmd_lst);
		cmd_lst = cmd_lst_cpy;
	}
}
