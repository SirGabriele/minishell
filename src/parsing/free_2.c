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
	free(all_redirs->outfile);
	free(all_redirs->infile);
	free_redirections(all_redirs->output_redir);
	free_redirections(all_redirs->input_redir);
	free(all_redirs);
}

void	free_context(t_context_ms *cmd_line)
{
	t_context_ms	*cmd_line_cpy;

	while (cmd_line->next)
	{
		free(cmd_line->pipeline);
		free_all_redirections(cmd_line->all_redirs);
		cmd_line_cpy = cmd_line->next;
		free(cmd_line);
		cmd_line = cmd_line_cpy;
	}
}
