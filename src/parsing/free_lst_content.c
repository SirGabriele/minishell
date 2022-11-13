#include "../../includes/minishell.h"

void	free_lst_content(t_token_ms *tokens)
{
	while (!tokens->next)
	{
		free(tokens->content);
		tokens->content = NULL;
		tokens = tokens->next;
	}
}
