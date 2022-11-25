#include "../../includes/minishell.h"

t_node_ms	*ft_create_node(void)
{
	t_node_ms	*elem;

	elem = malloc(sizeof(t_node_ms));
	if (elem == NULL)
		return (NULL);
	elem->left = NULL;
	elem->right = NULL;
	elem->first_redir = NULL;
	elem->content = NULL;
	elem->infile = NULL;
	elem->outfile = NULL;
	elem->infile_mode = TOK_NULL;
	elem->outfile_mode = TOK_NULL;
	elem->operator = TOK_NULL;
	return (elem);
}
