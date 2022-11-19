#include "../../includes/minishell.h"

t_token_ms	*increm_tokens_copy(t_token_ms *tokens_cpy)
{
	while (tokens_cpy->type != TOK_PIPE && tokens_cpy->type != TOK_OR_OPER
		&& tokens_cpy->type != TOK_AND_OPER && tokens_cpy->next)
		tokens_cpy = tokens_cpy->next;
	if (tokens_cpy->next)
		tokens_cpy = tokens_cpy->next;
	return (tokens_cpy);
}
