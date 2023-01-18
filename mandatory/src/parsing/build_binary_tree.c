#include "../../includes/minishell.h"

static t_node_ms	*set_node_infos(t_enum_token shell)
{
	t_node_ms	*node;

	node = malloc(sizeof(t_node_ms));
	if (node)
	{
		node->first_redir = NULL;
		node->content = NULL;
		node->infile = NULL;
		node->outfile = NULL;
		node->infile_mode = TOK_NULL;
		node->outfile_mode = TOK_NULL;
		node->shell = shell;
	}
	return (node);
}

static t_node_ms	*node_related(t_token_ms *tokens, t_node_ms *root, \
	t_enum_token shell)
{
	root = set_node_infos(shell);
	if (!root)
	{
		free_tokens(tokens);
		return (NULL);
	}
	root = get_list_infos(root, tokens, shell);
	free_tokens(tokens);
	return (root);
}

static t_node_ms	*pipeline_related(t_token_ms *tokens, t_node_ms *root, \
	t_enum_token shell)
{
	root = ft_lstnew_node(shell);
	if (!root)
	{
		free_tokens(tokens);
		return (NULL);
	}
	root = get_pipeline_infos(root, tokens);
	free_tokens(tokens);
	return (root);
}

t_node_ms	*build_binary_tree(t_token_ms *tokens, t_enum_token shell)
{
	t_node_ms		*root;
	int				nb_pipes;

	root = NULL;
	nb_pipes = is_there_pipes(tokens);
	if (nb_pipes)
		root = node_related(tokens, root, shell);
	else
		root = pipeline_related(tokens, root, shell);
	return (root);
}
