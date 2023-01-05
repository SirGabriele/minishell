#include "../../includes/minishell.h"

t_node_ms	*ft_lstnew_node(t_enum_token *operators)
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
	if (operators[0] == TOK_PIPE || operators[1] == TOK_PIPE)
		node->shell = TOK_SUBSHELL;
	else
		node->shell = TOK_SHELL;
	node->operator = TOK_NULL;
	return (node);
}
