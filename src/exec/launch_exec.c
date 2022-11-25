#include "../../includes/minishell.h"

static int	process_node(t_node_ms *root, t_env_ms *env,
	int *pipe_before, int *pipe_after)
{
	(void)pipe_before;
	(void)pipe_after;
	(void)env;
	/*faire redirection des pipes si necessaire*/
	/*gerer infile*/
	/*gerer outfile*/
	/*parcourir first->redir*/
	if (browse_all_redirs(root) == -1)
		return (-2);

	ft_printf("%d\n\n", root->operator);
	return (0);
}

//if node est sur un pipe, rediriger node->left->pipe sur node->right->pipe

int	launch_exec(t_node_ms *root, t_env_ms *env)
{
	if (pipe(root->pipe_before) == -1 || pipe(root->pipe_after) == -1)
		return (-1);
	if (root->left != NULL)
		launch_exec(root->left, env);
	if (process_node(root, env, root->pipe_before, root->pipe_after) == -1)
		return (-1);
	if (root->right != NULL)
		launch_exec(root->right, env);
	close(root->pipe_before[0]);
	close(root->pipe_before[1]);
	close(root->pipe_after[0]);
	close(root->pipe_after[1]);
	return (0);
}
