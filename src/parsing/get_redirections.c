#include "../../includes/minishell.h"

t_node_ms	*get_redirections_infos(t_token_ms *tokens)
{
	t_node_ms	*binary_tree;

	binary_tree = malloc(sizeof(t_node_ms));
	if (!binary_tree)
		return (NULL);
	binary_tree->first_redir = get_redirections_list(tokens);
	binary_tree = get_redirections_modes_and_files(binary_tree);
	return (binary_tree);
}
