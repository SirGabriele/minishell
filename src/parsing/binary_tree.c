#include "../../includes/minishell.h"

t_node_ms	*build_binary_tree(t_token_ms *tokens)
{
	t_node_ms	*binary_tree;
	t_tokens	operator_pos;

	operator_pos = detect_operators(tokens);
	if (operator_pos)
	{
		binary_tree = get_list_infos(tokens, operator_pos);
		if (!binary_tree)
			return (NULL);
	}
	else
	{
		binary_tree = get_pipeline_infos(tokens);
		if (!binary_tree)
			return (NULL);
	}
	return (binary_tree);
}
