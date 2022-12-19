#include "../../includes/minishell.h"

/************************************************************/
/*															*/
/*	Checks if link is inside/outside of parenthesis			*/
/*															*/
/*	Parameters:												*/
/*		tokens		-	linked list							*/
/*		token_pos	-	index of the link to check			*/
/*															*/
/*	Return:													*/
/*		TOK_SUBSHELL - link between parenthesis				*/
/*		TOK_SHELL	 - link not between parenthesis			*/
/*															*/
/************************************************************/

t_enum_token	is_token_in_parenthesis(t_token_ms *tokens, int token_pos)
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
			return (TOK_SUBSHELL);
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

/************************************************************/
/*															*/
/*	Checks if the operator is in a shell or subshell		*/
/*															*/
/*	Parameters:												*/
/*		tokens	-	linked list								*/
/*															*/
/*	Return:													*/
/*		0	-	no parenthesis								*/
/*		1	-	parenthesis									*/
/*															*/
/************************************************************/

t_enum_token	what_is_oper_in(t_token_ms *tokens)
{
	t_enum_token	oper_pos;
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
			if (is_token_in_parenthesis(tokens, index_token) == TOK_SHELL)
				return (TOK_SHELL);
			else if (is_token_in_parenthesis(tokens, index_token) == TOK_SUBSHELL)
				oper_pos = TOK_SUBSHELL;
		}
		index_token++;
		cpy_tokens = cpy_tokens->next;
	}
	return (oper_pos);
}

/************************************************************/
/*															*/
/*	Find the operator that will cut the linked list in two	*/
/*															*/
/*	Parameters:												*/
/*														*/
/*		x - def												*/
/*															*/
/*	Return:													*/
/*		x - def												*/
/*		x - def												*/
/*															*/
/************************************************************/

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

/************************************************************/
/*															*/
/*	Deletes parenthesis if needed							*/
/*															*/
/*	Parameters:												*/
/*		tokens	-	linked list with potential parenthesis	*/
/*															*/
/*	Return:													*/
/*		tokens	-	linked list without parenthesis			*/
/*															*/
/************************************************************/

t_token_ms	*del_parenthesis_if_needed(t_token_ms *tokens)
{
	t_token_ms	*tokens_cpy;

	if (check_parenthesis(tokens) == TOK_SUBSHELL)//what_is_oper_in useless ?
	{
		tokens_cpy = tokens->next;
		free(tokens->content);
		free(tokens);
		tokens = tokens_cpy;
		while (tokens_cpy->next->next)
			tokens_cpy = tokens_cpy->next;
		free(tokens_cpy->next->content);
		free(tokens_cpy->next);
		tokens_cpy->next = NULL;
		tokens = del_parenthesis_if_needed(tokens);
	}
	return (tokens);
}

/************************************************************/
/*															*/
/*	Checks if command line is between parenthesis			*/
/*															*/
/*	Parameters:												*/
/*		tokens	-	linked list								*/
/*															*/
/*	Return:													*/
/*		0	-	no parenthesis								*/
/*		1	-	parenthesis									*/
/*															*/
/************************************************************/

t_enum_token	check_parenthesis(t_token_ms *tokens)
{
	int			op_parenthesis;
	int			cl_parenthesis;

	if (tokens->type == TOK_OP_PAR)
	{
		op_parenthesis = 0;
		cl_parenthesis = 0;
		while (tokens)
		{
			if (tokens->type == TOK_OP_PAR)
				op_parenthesis++;
			else if (tokens->type == TOK_CL_PAR)
				cl_parenthesis++;
			if (op_parenthesis == cl_parenthesis && !tokens->next)
				return (TOK_SUBSHELL);
			else if (op_parenthesis == cl_parenthesis && tokens->next)//pareil
				return (TOK_SHELL);
			tokens = tokens->next;
		}
	}
	if (tokens)
		return (TOK_SHELL);
	return (TOK_NULL);
}
