#include "../../includes/minishell_bonus.h"

t_enum_token	identify_splitting_operator(t_token_ms *tokens)
{
	t_token_ms	*cpy_tokens;
	int			index_token;

	cpy_tokens = tokens;
	index_token = 1;
	while (cpy_tokens)
	{
		if ((cpy_tokens->type == TOK_AND_OPER || cpy_tokens->type == TOK_OR_OPER
				|| cpy_tokens->type == TOK_PIPE)
			&& is_token_in_parenthesis(tokens, index_token) == TOK_SHELL)
			return (cpy_tokens->type);
		index_token++;
		cpy_tokens = cpy_tokens->next;
	}
	return (TOK_NULL);
}
