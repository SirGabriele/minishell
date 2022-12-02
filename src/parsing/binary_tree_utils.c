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
			return (TOK_NULL);
		else if (index_token == token_pos && op_parenthesis == cl_parenthesis)
			return (TOK_SHELL);
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
	t_tokens	oper_pos;
	t_token_ms	*cpy_tokens;
	int			index_token;

	oper_pos = TOK_NULL;
	cpy_tokens = tokens;
	index_token = 1;
	while (cpy_tokens)
	{
		if (cpy_tokens->type == TOK_AND_OPER || cpy_tokens->type == TOK_OR_OPER
			|| cpy_tokens->type == TOK_PIPE)
		{
			if (check_token_pos(tokens, index_token) == TOK_SHELL)
				return (TOK_SHELL);
		}
		index_token++;
		cpy_tokens = cpy_tokens->next;
	}
	return (oper_pos);
}

t_tokens	identify_operator(t_token_ms *tokens, t_tokens operator_pos)
{
	t_token_ms	*cpy_tokens;
	int			index_token;

	cpy_tokens = tokens;
	index_token = 1;
	while (cpy_tokens)
	{
		if (cpy_tokens->type == TOK_AND_OPER || cpy_tokens->type == TOK_OR_OPER
			|| cpy_tokens->type == TOK_PIPE)
		{
			if (check_token_pos(tokens, index_token) == operator_pos)
				return (cpy_tokens->type);
		}
		index_token++;
		cpy_tokens = cpy_tokens->next;
	}
	return (TOK_NULL);
}

t_token_ms	*supp_parenthesis_if_needed(t_token_ms *tokens)
{
	t_token_ms	*tokens_cpy;

	tokens_cpy = tokens;
	if (check_parenthesis(tokens) == TOK_NULL)
	{
		tokens = tokens_cpy->next;
		while (tokens_cpy->next->next)
			tokens_cpy = tokens_cpy->next;
		tokens_cpy->next = NULL;
	}
	return (tokens);
}

int	check_parenthesis(t_token_ms *tokens)
{
	t_token_ms	*tmp_tokens;
	int			op_parenthesis;
	int			cl_parenthesis;

	tmp_tokens = tokens;
	if (tmp_tokens->type == TOK_OP_PAR)
	{
		op_parenthesis = 0;
		cl_parenthesis = 0;
		while (tmp_tokens)
		{
			if (tmp_tokens->type == TOK_OP_PAR)
				op_parenthesis++;
			else if (tmp_tokens->type == TOK_CL_PAR)
				cl_parenthesis++;
			if (op_parenthesis == cl_parenthesis && !tmp_tokens->next)
				return (TOK_NULL);
			else if (op_parenthesis == cl_parenthesis && tmp_tokens->next)
				return (TOK_SHELL);
			tmp_tokens = tmp_tokens->next;
		}
	}
	return (TOK_SHELL);
}