#include "../includes/minishell.h"

static void free_env(t_env_ms *env)
{
	t_env_ms	*current;
	t_env_ms	*next;

	current = env;
	while (current != NULL)
	{
		next = current->next;
		if (current->key != NULL)
			free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

/*static void	free_redirs(t_redir_ms *first_redir)
{
	t_redir_ms	*current;
	t_redir_ms	*next;

	current = first_redir;
	while (current != NULL)
	{
		next = current->next;
		if (current->file_name != NULL)
			free(current->file_name);
		free(current);
		current = next;
	}
}*/

static void	free_node(t_node_ms *node)
{
	int	i;

	i = 0;
//	if (node->first_redir != NULL)
//		free_redirs(node->first_redir);
	if (node->content != NULL)
	{
		while (node->content[i] != NULL)
		{
			free(node->content[i]);
			i++;
		}
		free(node->content);
	}
	if (node->infile != NULL)
		free(node->infile);
	if (node->outfile != NULL)
		free(node->outfile);
	free(node);
}
		
static void	free_tree(t_node_ms *root)
{
	t_node_ms	*node;

	node = root;
	if (node->left != NULL)
		free_tree(node->left);
	free_node(node);
	if (node->right != NULL)
		free_tree(node->right);
}

void	free_program(t_node_ms *root, t_env_ms *env)
{
	if (root != NULL)
		free_tree(root);
	if (env != NULL)
		free_env(env);
}
