/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_and_handling_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:36:47 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:52:26 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static t_node_ms	*skip_commands_until_or_operator(t_node_ms *node)
{
	while (node && node->operator != TOK_OR_OPER)
		node = node->right;
	return (node);
}

static int	get_last_cmd_exit_code(t_node_ms *node, t_children_ms *children)
{
	int	wstatus;
	int	exit_code;

	wstatus = 0;
	exit_code = 0;
	if (!node->left->content || (is_a_builtin(node->left->content[0]) == 0
			&& node->left->shell == TOK_SUBSHELL)
		|| is_a_builtin(node->left->content[0]) == 1)
	{
		waitpid(children->pid_arr[children->index - 1], &wstatus, WUNTRACED);
		if (WIFEXITED(wstatus))
			exit_code = WEXITSTATUS(wstatus);
	}
	else
		exit_code = children->pid_arr[children->index - 1];
	return (exit_code);
}

/************************************************************************/
/*																		*/
/*	Prints the content of the previous pipe and checks if the previous	*/
/*		command succeeded or failed. If it succeeded, the next command	*/
/*		will be executed normally. If it failed, all the next &&		*/
/*		operators will be skipped										*/
/*																		*/
/*	Parameters:															*/
/*		pipes		-	structure containing the program's two pipes	*/
/*		children	-	structure containing the fork-linked			*/
/*						variables										*/
/*		node		-	the node corresponding to the && operator		*/
/*		env_ll		-	linked list of the env_variables				*/
/*																		*/
/*	Return:																*/
/*		node	-	the node from which the execution must continue		*/
/*		NULL	-	something failed									*/
/*																		*/
/************************************************************************/

t_node_ms	*apply_and_operator(t_pipes_ms *pipes, t_children_ms *children,
	t_node_ms *node, t_env_ms *env_ll)
{
	int	exit_code;

	exit_code = 0;
	print_content_pipe(pipes, env_ll);
	if (close(pipes->before[0]) == -1 || close(pipes->before[1]) == -1
		|| close(pipes->after[0]) == -1 || close(pipes->after[1]))
		return (NULL);
	exit_code = get_last_cmd_exit_code(node, children);
	set_exit_code(env_ll, exit_code);
	if (pipe(pipes->before) == -1 || pipe(pipes->after) == -1)
		return (NULL);
	if (exit_code != 0)
	{
		node = skip_commands_until_or_operator(node->right);
		return (node);
	}
	return (node);
}
