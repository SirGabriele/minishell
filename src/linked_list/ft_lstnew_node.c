#include "../../includes/minishell.h"

t_node_ms	*ft_lstnew_node(void)
{
	t_node_ms	*node;

	node = malloc(sizeof(t_node_ms));
	if (!node)
		return (NULL);
	node->left = NULL;
	node->right = NULL;
	node->content = NULL;
	node->first_redir = NULL;
	node->infile = NULL;
	node->outfile = NULL;
	node->infile_mode = TOK_NULL;
	node->outfile_mode = TOK_NULL;
	node->shell = TOK_NULL;
	node->operator = TOK_NULL;
	return (node);
}
