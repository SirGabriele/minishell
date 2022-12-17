#include "../../includes/minishell.h"

void	free_binary_tree(t_node_ms *binary_tree)
{
	if (binary_tree)
	{
		free_double_arr(binary_tree->content);
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

void	free_env_list(t_env_ms *env)
{
	t_env_ms	*tmp_env;

	while (env)
	{
		tmp_env = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp_env;
	}
}
