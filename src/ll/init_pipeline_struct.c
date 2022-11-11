#include "../../includes/minishell.h"

void	init_pipeline_struct(t_pipeline_ms *pipeline)
{
	pipeline->to_create_trunc = NULL;
	pipeline->to_create_append = NULL;
	pipeline->infile = NULL;
	pipeline->outfile = NULL;
	pipeline->first_cmd = NULL;
}
