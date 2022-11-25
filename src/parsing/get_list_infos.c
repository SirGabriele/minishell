#include "../../includes/minishell.h"

static t_node_ms	*get_node(t_token_ms *tokens, t_tokens operator_pos)
{
	t_node_ms	*binary_tree;

	binary_tree = malloc(sizeof(t_node_ms));
	if (binary_tree)
	{
		binary_tree->first_redir = NULL;
		binary_tree->content = NULL;
		binary_tree->infile = NULL;
		binary_tree->outfile = NULL;
		binary_tree->infile_mode = TOK_NULL;
		binary_tree->outfile_mode = TOK_NULL;
		binary_tree->operator_pos = operator_pos;
		binary_tree->operator = identify_operator(tokens, operator_pos);
	}
	return (binary_tree);
}

static t_token_ms	**split_list(t_token_ms *tokens, t_tokens operator_pos)
{
	t_token_ms	**splited_tokens;

	splited_tokens = malloc(3 * sizeof(t_token_ms *));
	if (!splited_tokens)
		return (NULL);
	splited_tokens[2] = NULL;
	splited_tokens[0] = tokens;
	while (tokens->next)
	{
		if (tokens->next->type == TOK_AND_OPER
			|| tokens->next->type == TOK_OR_OPER
			|| tokens->next->type == TOK_PIPE)
		{
			if (check_token_pos(tokens) == operator_pos)
			{
				splited_tokens[1] = tokens->next->next;
				tokens->next = NULL;
				tokens->content = NULL;
				return (splited_tokens);
			}
		}
		tokens = tokens->next;
	}
	return (NULL);
}

t_node_ms	*get_list_infos(t_token_ms *tokens, t_tokens operator_pos)
{
	t_node_ms	*binary_tree;
	t_token_ms	**splited_tokens;

	binary_tree = get_node(tokens, operator_pos);
	if (!binary_tree)
		return (NULL);
	splited_tokens = split_list(tokens, operator_pos);
	if (!splited_tokens)
		return (NULL);
	binary_tree->left = build_binary_tree(splited_tokens[0]);
	if (!binary_tree->left)
		return (NULL);
	binary_tree->right = build_binary_tree(splited_tokens[1]);
	if (!binary_tree->right)
		return (NULL);
	free_tokens(splited_tokens[0]);
	free_tokens(splited_tokens[1]);
	free(splited_tokens);
	return (binary_tree);
}
