#include "../../includes/minishell.h"

void	init_all_redirs(t_all_redirs_ms *all_redirs)
{
	all_redirs->next = NULL;
	all_redirs->infile = NULL;
	all_redirs->infile_mode = TOK_NULL;
	all_redirs->outfile = NULL;
	all_redirs->outfile_mode = TOK_NULL;
}
