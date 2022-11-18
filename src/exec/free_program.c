#include "../../includes/minishell.h"

static void	free_first_redir(t_redir_ms *first_redir)
{
	t_redir_ms	*current;
	t_redir_ms	*next;

	current = first_redir;
	while (current != NULL)
	{
		next = current->next;
		if (current->file_name != NULL)
			free(current->file_name);
		free(current);
		current = next;
	}
}

static void	free_all_redirs(t_all_redirs_ms *all_redirs)
{
	if (all_redirs->first_redir != NULL)
		free_first_redir(all_redirs->first_redir);
//	if (all_redirs->infile)
//		free(all_redirs->infile);
//	if (all_redirs->outfile != NULL)
//		free(all_redirs->outfile);
}

/************************************************************/
/*															*/
/*	Free the totality of memory the different structures	*/
/*	needed													*/
/*															*/
/*	Parameters:												*/
/*		context - the first pipeline						*/
/*															*/
/************************************************************/
void	free_program(t_context_ms *context)
{
	t_context_ms	*next;
	t_context_ms	*current;

	current = context;
	while (current != NULL)
	{
		next = current->next;
		if (current->all_redirs != NULL)
			free_all_redirs(current->all_redirs);
		free(current->all_redirs);
//		if (current->pipeline != NULL)
//			free(current->pipeline);
		free(current);
		current = next;
	}
}
