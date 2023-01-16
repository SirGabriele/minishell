#include "../../includes/minishell.h"

int	is_last_token_and_or(t_token_ms *tokens)
{
	while (tokens != NULL)
	{
		if ((tokens->type == TOK_AND_OPER || tokens->type == TOK_OR_OPER)
			&& !tokens->next)
			return (0);
		tokens = tokens->next;
	}
	return (1);
}
