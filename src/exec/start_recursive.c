#include "../../includes/minishell.h"

static int	transfer_pipe_content(int *pipe_before, int *pipe_after)
{
	close(pipe_before[0]);
	close(pipe_before[1]);
	pipe_before[0] = dup(pipe_after[0]);
	pipe_before[1] = dup(pipe_after[1]);
	close(pipe_after[0]);
	close(pipe_after[1]);
	if (pipe(pipe_after) == -1)
	{
		ft_putstr_fd("Pipe_after's creation failed\n", 2);
		return (-1);
	}
	return (0);
}

//pour export, envoyer une adresse vers env_ll afin qu'export la modifie vraiment
//ajouter handle_all_redirs dans les builtin
static int	process_node(t_pipes_ms *pipes, t_children_ms *children,
	t_node_ms *root, t_env_ms *env_ll)//separer builtin ou non ET gerer selon TOK_SHELL, TOK_SUBSHELL
{
	char	**env_arr;

	if (root->operator == TOK_PIPE)
		transfer_pipe_content(pipes->before, pipes->after);
/*	if (root->operator == TOK_AND_OPER)
		verify_ret_value_and_do_like_&&*/
/*	else if (root->operator == TOK_OR_OPER)
		verify_ret_value_and_do_like_||*/
	else
	{
		env_arr = convert_env_ll_into_arr(env_ll);
		if (env_arr == NULL)
			return (-1);
		execute_cmd(pipes, children, root, env_arr);
		free_double_arr(env_arr);
	}
	return (0);
}

int	start_recursive(t_pipes_ms *pipes, t_children_ms *children, t_node_ms *root, t_env_ms *env_ll)//gerer selon TOK_OP_PAR ou TOK_CL_PAR
{
	if (root->left != NULL)
		start_recursive(pipes, children, root->left, env_ll);
	if (process_node(pipes, children, root, env_ll) == -1)
		return (-1);
	if (root->right != NULL)
		start_recursive(pipes, children, root->right, env_ll);
	return (0);
}
