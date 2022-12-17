#include "../../includes/minishell.h"

static t_enum_token	*initialize_operators(void)
{
	t_enum_token	*operators;

	operators = malloc(2 * sizeof(t_enum_token));
	if (!operators)
	{
		perror(NULL);
		return (NULL);
	}
	operators[0] = TOK_NULL;
	operators[1] = TOK_NULL;
	return (operators);
}

t_node_ms	*build_binary_tree(t_token_ms *tokens, t_enum_token shell, \
	t_enum_token *operators)
{
	t_node_ms		*root;
	t_enum_token	oper_pos;

	oper_pos = what_is_oper_in(tokens);
	if (oper_pos)
	{
		tokens = del_parenthesis_if_needed(tokens);
		root = get_list_infos(tokens, shell, operators);
		if (!root)
			return (NULL);
	}
	else
	{
		root = get_pipeline_infos(tokens, shell, operators);
		if (!root)
			return (NULL);
	}
	free_tokens(tokens);
	return (root);
}

/************************************************************/
/*															*/
/*	Creates binary_tree										*/
/*															*/
/*	Parameters:												*/
/*		tokens	-	linked list of tokens					*/
/*															*/
/*	Return:													*/
/*		root	-	root of binary_tree						*/
/*															*/
/************************************************************/

t_node_ms	*start_binary_tree(t_token_ms *tokens)
{
	t_node_ms		*root;
	t_enum_token	*operators;
	t_enum_token	shell;

	operators = initialize_operators();
	if (!operators)
		return (NULL);
	shell = check_parenthesis(tokens);
	root = build_binary_tree(tokens, shell, operators);
	free(operators);
	return (root);
}
