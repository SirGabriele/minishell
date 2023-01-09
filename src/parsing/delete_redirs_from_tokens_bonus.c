#include "../../includes/minishell.h"

static void	free_redirs_tokens(t_token_ms *tokens)
{
	free(tokens->next->content);
	free(tokens->next);
	free(tokens->content);
	tokens->content = NULL;
	free(tokens);
	tokens = NULL;
}

