#include "../../includes/minishell.h"

void	init_tree_struct(t_node_ms *root)
{
	root->left = NULL;
	root->right = NULL;
	root->fist_redir = NULL;
	root->content = NULL;
	root->infile = NULL;
	root->outfile = NULL;
}
