#include "../../includes/minishell.h"

void	init_pipeline_struct(t_pipeline_ms *pipeline)
{
	pipeline->first_redir = NULL;
	pipeline->infile = NULL;
	pipeline->outfile = NULL;
	pipeline->first_cmd = NULL;
}
