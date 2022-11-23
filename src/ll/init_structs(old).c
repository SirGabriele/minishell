#include "../../includes/minishell.h"

void	init_context_all_redirs(t_all_redirs_ms *all_redirs)
{
	all_redirs->first_redir = NULL;
	all_redirs->infile = NULL;
	all_redirs->infile_mode = TOK_NULL;
	all_redirs->outfile = NULL;
	all_redirs->outfile_mode = TOK_NULL;
}

void	init_context_struct(t_context_ms *context)
{
	context->next = NULL;
	context->all_redirs = NULL;
	context->what_is_pipeline_after = TOK_NULL;
	context->pipeline = NULL;
}
