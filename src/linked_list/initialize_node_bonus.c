#include "../../includes/minishell.h"

void	initialize_node(t_node_ms *node)
{
	node->left = NULL;
	node->right = NULL;
	node->first_redir = NULL;
	node->content = NULL;
	node->infile = NULL;
	node->outfile = NULL;
	node->infile_mode = TOK_NULL;
	node->infile_mode = TOK_NULL;
	node->shell	= TOK_NULL;
	node->operator = TOK_NULL;
}
