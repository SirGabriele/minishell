/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:16:14 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/20 01:24:59 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	fill_int_array(int *int_array, t_node_ms *root, int *i)
{
	if (root->left != NULL)
		fill_int_array(int_array, root->left, i);
	if (root->operator != TOK_PIPE)
	{
		if (root->content && is_a_builtin(root->content[0]) == 0
			&& root->shell == TOK_SHELL)
			int_array[*i] = 0;
		else
			int_array[*i] = 1;
		(*i)++;
	}
	if (root->right != NULL)
		fill_int_array(int_array, root->right, i);
}

static void	wait_for_all_the_forks(t_children_ms *children, t_env_ms *env_ll,
	int nb_nodes, t_node_ms *root)
{
	int	*int_array;
	int	i;
	int	wstatus;
	int	exit_code;

	i = 0;
	exit_code = 0;
	wstatus = 0;
	int_array = malloc(sizeof(int) * nb_nodes);
	fill_int_array(int_array, root, &i);
	i = 0;
	while (i < children->index)
	{
		if (int_array[i] == 1)
			waitpid(children->pid_arr[i], &wstatus, WUNTRACED);
		else
			exit_code = children->pid_arr[i];
		i++;
	}
	if (g_signal != 130 && int_array[i - 1] == 1 && WIFEXITED(wstatus))
		exit_code = WEXITSTATUS(wstatus);
	else if ((g_signal == 130 || int_array[i - 1] == 1) && WIFSIGNALED(wstatus))
		exit_code = WTERMSIG(wstatus) + 128;
	set_exit_code(env_ll, exit_code);
	free(int_array);
}

static int	get_nb_nodes(t_node_ms *root, int *i)
{
	if (root->left != NULL)
		get_nb_nodes(root->left, i);
	if (root->left == NULL)
		(*i)++;
	if (root->right != NULL)
		get_nb_nodes(root->right, i);
	return (*i);
}

/****************************************************************/
/*																*/
/*	Carries out the whole execution process (preparation		*/
/*		execution, fork waiting)								*/
/*																*/
/*	Parameters:													*/
/*		root	-	root of the binary tree						*/
/*		env_ll	-	linked list containing the env variables	*/
/*																*/
/*	Return:														*/
/*		 0	-	accomplished its duty							*/
/*		-1	-	something failed								*/
/*																*/
/****************************************************************/

int	launch_exec(t_node_ms *root, t_env_ms *env_ll)
{
	t_children_ms	*children;
	t_pipes_ms		*pipes;
	int				nb_nodes;
	int				ret;

	ret = 0;
	nb_nodes = 0;
	nb_nodes = get_nb_nodes(root, &nb_nodes);
	children = initialize_children(nb_nodes);
	if (children == NULL)
		return (-1);
	pipes = initialize_pipes(root, children);
	ret = start_recursive(pipes, children, root, env_ll);
	if (ret == 130)
		set_exit_code(env_ll, 130);
	if (close(pipes->before[0]) == -1 || close(pipes->before[1]) == -1
		|| close(pipes->after[0]) == -1 || close(pipes->after[1]) == -1)
		return (-1);
	if (ret != -1 && ret != 130)
		wait_for_all_the_forks(children, env_ll, nb_nodes, root);
	free(children->pid_arr);
	free(children);
	free(pipes);
	return (0);
}
