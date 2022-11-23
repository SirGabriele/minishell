#include "../../includes/minishell.h"

/*typedef struct s_context_ms
{
	struct s_context_ms		*next;
	struct s_all_redirs_ms	*all_redirs;
	t_tokens				what_is_pipeline_after;
	char					*pipeline;
}	t_context_ms;*/

static int	analyze_pipeline(t_context_ms *current_cont,
	t_context_ms *context)
{
	
}

int	how_to_handle_this_pipeline(t_context_ms *current_cont,
	t_context_ms *context)
{
//	if (current_cont->what_is_pipeline_after == TOK_OR_OPER)
//		ignore this pipeline if last status is good
//			or exec is the last status was wrong;
//	else if (current_cont->what_is_pipeline_after == TOK_AND_OPER)
//		send previous pipe content in final pipe and exec this pipeline
	else if (current_cont == TOK_NULL)
		if (analyze_pipeline(current_cont, context) == -1)
			return (-1);
}
