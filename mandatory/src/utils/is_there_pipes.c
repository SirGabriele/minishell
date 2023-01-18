#include "../../includes/minishell.h"

int	is_there_pipes(t_token_ms	*tokens)
{
	while (tokens)
	{
		if (tokens->type == TOK_PIPE)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}
