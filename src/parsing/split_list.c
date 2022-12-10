#include "../../includes/minishell.h"

static t_token_ms	*get_tokens_2(t_token_ms *tokens, int index_token)
{
	while (index_token)
	{
		tokens = tokens->next;
		index_token--;
	}
	return (tokens);
}

static t_token_ms	**get_both_halves(t_token_ms *tokens_1, int index_token)
{
	t_token_ms	**splited_tokens;
	t_token_ms	*tokens_2;

	splited_tokens = malloc(3 * sizeof(t_token_ms *));
	if (!splited_tokens)
		return (NULL);
	splited_tokens[0] = get_first_half(tokens_1, index_token);
	if (!splited_tokens[0])
		return (NULL);
	tokens_2 = get_tokens_2(tokens_1, index_token + 1);
	splited_tokens[1] = get_second_half(tokens_2);
	if (!splited_tokens[1])
	{
		free_splited_tokens(splited_tokens);
		return (NULL);
	}
	splited_tokens[2] = NULL;
	return (splited_tokens);
}

t_token_ms	**split_list(t_token_ms *tokens)
{
	t_token_ms	**splited_tokens;
	t_token_ms	*cpy_tokens;
	int			index_token;

	cpy_tokens = tokens;
	index_token = 1;
	while (cpy_tokens)
	{
		if (cpy_tokens->next && is_operator(cpy_tokens->next->type)
			&& check_token_pos(tokens, index_token + 1) == TOK_SHELL)
		{
			splited_tokens = get_both_halves(tokens, index_token);
			if (!splited_tokens)
				return (NULL);
			return (splited_tokens);
		}
		index_token++;
		cpy_tokens = cpy_tokens->next;
	}
	return (NULL);
}
