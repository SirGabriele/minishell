#include "../../includes/minishell.h"

t_tokens	check_token_pos(t_token_ms *tokens, int token_pos)
{
	int	op_parenthesis;
	int	cl_parenthesis;
	int	index_token;

	op_parenthesis = 0;
	cl_parenthesis = 0;
	index_token = 1;
	while (tokens)
	{
		if (index_token == token_pos && op_parenthesis > cl_parenthesis)
			return (TOK_IN_PAR);
		else if (index_token == token_pos && op_parenthesis == cl_parenthesis)
			return (TOK_NOT_IN_PAR);
		else if (tokens->type == TOK_OP_PAR)
			op_parenthesis++;
		else if (tokens->type == TOK_CL_PAR)
			cl_parenthesis++;
		index_token++;
		tokens = tokens->next;
	}
	return (TOK_NULL);
}

t_tokens	detect_operators(t_token_ms *tokens)
{
	t_tokens	operator_pos;
	int			index_token;

	operator_pos = TOK_NULL;
	index_token = 1;
	while (tokens)
	{
		if (tokens->type == TOK_AND_OPER || tokens->type == TOK_OR_OPER
			|| tokens->type == TOK_PIPE)
		{
			if (check_token_pos(tokens, index_token) == TOK_NOT_IN_PAR)
				return (TOK_NOT_IN_PAR);
			else if (check_token_pos(tokens, index_token) == TOK_IN_PAR)
				operator_pos = TOK_IN_PAR;
		}
		index_token++;
		tokens = tokens->next;
	}
	return (operator_pos);
}

t_tokens	identify_operator(t_token_ms *tokens, t_tokens operator_pos)
{
	int	index_token;

	index_token = 1;
	while (tokens)
	{
		if (tokens->type == TOK_AND_OPER || tokens->type == TOK_OR_OPER
			|| tokens->type == TOK_PIPE)
		{
			if (check_token_pos(tokens, index_token) == operator_pos)
				return (tokens->type);
		}
		index_token++;
		tokens = tokens->next;
	}
	return (TOK_NULL);
}
