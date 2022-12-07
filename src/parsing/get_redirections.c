#include "../../includes/minishell.h"

t_node_ms	*get_redirections_infos(t_token_ms *tokens, t_node_ms *binary_tree)
{
	binary_tree->first_redir = get_redirections_list(tokens);
	if (!binary_tree->first_redir)
	{
		//free(binary_tree);
		return (NULL);
	}
	binary_tree = get_redirections_modes_and_files(binary_tree);
	return (binary_tree);
}
