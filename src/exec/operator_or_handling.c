#include "../../includes/minishell.h"

static t_node_ms	*skip_commands_until_and_operator(t_node_ms *root)
{
	while (root && root->operator != TOK_AND_OPER)
		root = root->right;
	return (root);
}

t_node_ms	*apply_or_operator(t_pipes_ms *pipes, t_children_ms *children, t_node_ms *root, t_env_ms *env_ll)
{
	int	wstatus;
	int	exit_code;

	exit_code = 0;
	if (close(pipes->before[0]) == -1 || close(pipes->before[1]) == -1
		|| close(pipes->after[0]) == -1 || close(pipes->after[1]))
		return (NULL);
	waitpid(children->pid_arr[children->index - 1], &wstatus, WUNTRACED);
	if (WIFEXITED(wstatus))
		exit_code = WEXITSTATUS(wstatus);
	set_exit_code(env_ll, exit_code);
	if (pipe(pipes->before) == -1 || pipe(pipes->after) == -1)
		return (NULL);
	if (exit_code == 0)
	{
		root = skip_commands_until_and_operator(root->right);
		return (root);
	}
	return (root);
}

