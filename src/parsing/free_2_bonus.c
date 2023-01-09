#include "../../includes/minishell.h"

void	free_double(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			str[i] = NULL;
			i++;
		}
		free(str);
		str = NULL;
	}
}

void	free_binary_tree(t_node_ms *binary_tree)
{
	if (binary_tree)
	{
		free_double(binary_tree->content);
		free_redirs_list(binary_tree->first_redir);
		binary_tree->first_redir = NULL;
		free(binary_tree->infile);
		binary_tree->infile = NULL;
		free(binary_tree->outfile);
		binary_tree->outfile = NULL;
		free_binary_tree(binary_tree->left);
		free_binary_tree(binary_tree->right);
		free(binary_tree);
	}
}
