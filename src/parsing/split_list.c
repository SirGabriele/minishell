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
	t_token_ms	**splitted_tokens;
	t_token_ms	*tokens_2;//c'est quoi token_2 exactement?

	splitted_tokens = malloc(3 * sizeof(t_token_ms *));
	if (!splitted_tokens)
		return (NULL);
	splitted_tokens[0] = get_first_half(tokens_1, index_token);
	if (!splitted_tokens[0])
		return (NULL);
	tokens_2 = get_tokens_2(tokens_1, index_token + 1);
	splitted_tokens[1] = get_second_half(tokens_2);
	if (!splitted_tokens[1])
	{
		free_splitted_tokens(splitted_tokens);
		return (NULL);
	}
	splitted_tokens[2] = NULL;
	return (splitted_tokens);
}

/************************************************************/
/*															*/
/*	Splits the linked list in two							*/
/*															*/
/*	Parameters:												*/
/*		tokens	-	linked list								*/
/*															*/
/*	Return:													*/
/*		splitted_tokens	-	double array containing			*/
/*							both halves						*/
/*															*/
/************************************************************/

t_token_ms	**split_list(t_token_ms *tokens)
{
	t_token_ms	**splitted_tokens;
	t_token_ms	*cpy_tokens;
	int			index_token;

	cpy_tokens = tokens;
	index_token = 1;
	while (cpy_tokens)
	{
		if (cpy_tokens->next && is_operator(cpy_tokens->next->type)
			&& check_token_pos(tokens, index_token + 1) == TOK_SHELL)
		{
			splitted_tokens = get_both_halves(tokens, index_token);
			if (!splitted_tokens)
				return (NULL);
			return (splitted_tokens);
		}
		index_token++;
		cpy_tokens = cpy_tokens->next;
	}
	return (NULL);
}
