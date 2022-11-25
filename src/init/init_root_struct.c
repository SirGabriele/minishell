#include "../../includes/minishell.h"

void	init_root_struct(t_node_ms *root)
{
	root->left = NULL;
	root->right = NULL;
	root->first_redir = NULL;
	root->content = NULL;
	root->infile = NULL;
	root->outfile = NULL;
	root->infile_mode = TOK_NULL;
	root->infile_mode = TOK_NULL;
	root->operator = TOK_NULL;
}
