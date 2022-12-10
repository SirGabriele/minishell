#include "../../includes/minishell.h"

t_node_ms	*build_binary_tree(t_token_ms *tokens, t_tokens shell)
{
	t_node_ms	*binary_tree;
	t_tokens	oper_pos;

	oper_pos = detect_operators(tokens);
	if (oper_pos)
	{
		tokens = del_parenthesis_if_needed(tokens);
		binary_tree = get_list_infos(tokens, shell);
		if (!binary_tree)
			return (NULL);
	}
	else
	{
		binary_tree = get_pipeline_infos(tokens, shell);
		if (!binary_tree)
			return (NULL);
	}
	free_n_tokens(tokens, 0);
	return (binary_tree);
}
