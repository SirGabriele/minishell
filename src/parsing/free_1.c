#include "../../includes/minishell.h"

void	free_user_input_and_set_to_null(char *user_input)
{
	free(user_input);
	user_input = NULL;
}

void	free_lst_content(t_token_ms *tokens)
{
	while (tokens->next)
	{
		free(tokens->content);
		tokens->content = NULL;
		tokens = tokens->next;
	}
}

void	free_tokens(t_token_ms *tokens)
{
	t_token_ms	*tokens_cpy;

	while (tokens->next)
	{
		free(tokens->content);
		tokens_cpy = tokens->next;
		free(tokens);
		tokens = tokens_cpy;
	}
}
