#include "../../includes/minishell.h"

static t_tokens	check_token_pos(t_token_ms *tokens)
{
	int	opened_parenthesis;
	int	closed_parenthesis;

	opened_parenthesis = 0;
	closed_parenthesis = 0;
	while (tokens->next)
	{
		if (tokens->type == TOK_OP_PAR)
			opened_parenthesis++;
		else if (tokens->type == TOK_CL_PAR)
			closed_parenthesis++;
		if (opened_parenthesis == closed_parenthesis && opened_parenthesis)
		{
			if (j > i)
				return (TOK_IN_PAR);
		}
		j++;
	}
	return (TOK_NOT_IN_PAR);
}

t_tokens	detect_operators(t_token_ms *tokens)
{
	t_tokens	operator_pos;

	operator_pos = TOK_NULL;
	while (tokens->next)
	{
		if (tokens->type == TOK_AND_OPER || tokens->type == TOK_OR_OPER
			|| tokens->type == TOK_PIPE)
		{
			if (check_token_pos(tokens) == TOK_NOT_IN_PAR)
				return (TOK_NOT_IN_PAR);
			else if (check_token_pos(tokens) == TOK_IN_PAR)
				operator_pos = TOK_IN_PAR;
		}
		tokens = tokens->next;
	}
	return (operator_pos);
}

t_tokens	identify_operator(t_token_ms *tokens, t_tokens operator_pos)
{
	while (tokens->next)
	{
		if (tokens->type == TOK_AND_OPER || tokens->type == TOK_OR_OPER
			|| tokens->type == TOK_PIPE)
		{
			if (check_token_pos(tokens) == operator_pos)
				return (tokens->type);
		}
		tokens = tokens->next;
	}
	return (TOK_NULL);
}
