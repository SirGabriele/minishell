/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:27:55 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 23:44:37 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	close_all_pipes(t_pipes_ms *pipes)
{
	close(pipes->before[0]);
	close(pipes->before[1]);
	close(pipes->after[0]);
	close(pipes->after[1]);
}

static void	free_memory_fork_and_exit(t_pipes_ms *pipes, char **env_arr,
	t_env_ms *env_ll, int exit_code)
{
	free_binary_tree(pipes->tree_root);
	free_env_list(env_ll);
	free(pipes->children->pid_arr);
	free(pipes->children);
	if (env_arr != NULL)
		free_double_arr(env_arr);
	close_all_pipes(pipes);
	free(pipes);
	close(0);
	close(1);
	close(2);
	exit(exit_code);
}

static void	test_permission_and_directory(t_pipes_ms *pipes, t_node_ms *node,
	char **env_arr, t_env_ms *env_ll)
{
	if (node->content[0][0] != '\0' && (is_a_directory(node->content[0]) == 0
		|| is_permission_denied(node->content[0]) == 0))
		free_memory_fork_and_exit(pipes, env_arr, env_ll, 126);
}

static void	go_in_child_process(t_pipes_ms *pipes,
	t_node_ms *node, t_env_ms *env_ll, int exit_code_redirs)
{
	char	**env_arr;
	char	*correct_path;
	int		exit_code;

	set_sigint_sigquit_to_default();
	env_arr = convert_env_ll_into_arr(env_ll);
	redirect_infile_outfile(pipes, node);
	if (exit_code_redirs != 0)
		free_memory_fork_and_exit(pipes, env_arr, env_ll, exit_code_redirs);
	if (env_arr == NULL || node->content == NULL)
		free_memory_fork_and_exit(pipes, env_arr, env_ll, 0);
	if (is_a_builtin(node->content[0]) == 0)
	{
		exit_code = exec_builtin(node, &env_ll, pipes, exit_code_redirs);
		free_memory_fork_and_exit(pipes, env_arr, env_ll, exit_code);
	}
	close_all_pipes(pipes);
	test_permission_and_directory(pipes, node, env_arr, env_ll);
	correct_path = verify_cmd_path(node->content[0], env_arr);
	if (correct_path == NULL)
		free_memory_fork_and_exit(pipes, env_arr, env_ll, 127);
	execve(correct_path, node->content, env_arr);
	ft_printf_fd(2, "%s: command not found\n", correct_path);
	free_memory_fork_and_exit(pipes, env_arr, env_ll, 2);
}

/****************************************************************/
/*																*/
/*	Creates the child process in which the command will be		*/
/*		executed												*/
/*																*/
/*	Parameters:													*/
/*		pipes		-	structure containing the two pipes		*/
/*		children	-	structure containing the fork-linked	*/
/*						variables								*/
/*		node		-	node to process							*/
/*		env_ll		-	linked list of the env_variables		*/
/*																*/
/*	Return:				*										*/
/*		 0	-	accomplished its duty							*/
/*		-1	-	something failed								*/
/*																*/
/****************************************************************/

int	execute_cmd(t_pipes_ms *pipes, t_children_ms *children,
	t_node_ms *node, t_env_ms **env_ll)
{
	int	exit_code_redirs;

	exit_code_redirs = handle_all_redirs(node, pipes, *env_ll);
	if (exit_code_redirs == 130)
		return (130);
	if (node->content && is_a_builtin(node->content[0]) == 0
		&& node->shell == TOK_SHELL)
		children->pid_arr[children->index] = exec_builtin(node,
				env_ll, pipes, exit_code_redirs);
	else
	{
		handler_before_fork();
		children->pid_arr[children->index] = fork();
		if (children->pid_arr[children->index] == -1)
		{
			ft_putstr_fd("Fork() failed\n", 2);
			return (-1);
		}
		if (children->pid_arr[children->index] == 0)
			go_in_child_process(pipes, node, *env_ll, exit_code_redirs);
	}
	if (node->shell == TOK_SHELL)
		set_dollar_underscore(*env_ll, node->content);
	children->index++;
	return (0);
}
