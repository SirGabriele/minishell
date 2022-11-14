#include "../../includes/minishell.h"

void	free_user_input_and_set_to_null(char *user_input)
{
	free(user_input);
	user_input = NULL;
}

void	free_lst_content(t_token_ms *tokens)
{
	while (!tokens->next)
	{
		free(tokens->content);
		tokens->content = NULL;
		tokens = tokens->next;
	}
}
