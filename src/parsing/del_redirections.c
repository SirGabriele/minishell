#include "../../includes/minishell.h"

t_token_ms	*del_redirections(t_token_ms *tokens)
{
	t_token_ms	*tmp_tokens;

	if (check_if_token_is_redir(tokens->type))
	{
		tmp_tokens = tokens->next->next;
		tokens = tmp_tokens;
	}
	else
		tmp_tokens = tokens;
	while (tokens)
	{
		if (tokens->next && check_if_token_is_redir(tokens->next->type))
			tokens->next = tokens->next->next->next;
		tokens = tokens->next;
	}
	return (tmp_tokens);
}
