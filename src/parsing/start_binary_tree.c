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

static t_node_ms	*set_node_infos(t_token_ms *tokens)
{
	t_node_ms	*node;

	node = malloc(sizeof(t_node_ms));
	if (node)
	{
		node->first_redir = NULL;
		node->content = NULL;
		node->infile = NULL;
		node->outfile = NULL;
		node->infile_mode = TOK_NULL;
		node->outfile_mode = TOK_NULL;
		node->shell = check_parenthesis(tokens);
		node->operator = TOK_NULL;
	}
	return (node);
}

t_node_ms	*build_binary_tree(t_token_ms *tokens, t_enum_token *operators)
{
	t_node_ms		*root;
	t_enum_token	oper_pos;

	oper_pos = what_is_oper_in(tokens);
	if (oper_pos)
	{
		root = set_node_infos(tokens);
		if (!root)
			return (NULL);
		tokens = del_parenthesis_if_needed(tokens);
		root = get_list_infos(root, tokens, operators);
		if (!root)
			return (NULL);
	}
	else
	{
		root = ft_lstnew_node(tokens);
		if (!root)
			return (NULL);
		tokens = del_parenthesis_if_needed(tokens);
		root = get_pipeline_infos(root, tokens, operators);
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

	operators = initialize_operators();
	if (!operators)
		return (NULL);
	root = build_binary_tree(tokens, operators);
	free(operators);
	return (root);
}
