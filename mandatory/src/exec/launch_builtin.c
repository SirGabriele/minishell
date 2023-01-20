/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:42:27 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 23:45:03 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env_ms	*make_a_copy_of_env_ll(t_env_ms *env_ll)
{
	t_env_ms	*forked_env_ll;
	t_env_ms	*head;

	forked_env_ll = lstnew_env_link();
	if (!forked_env_ll)
	{
		perror(NULL);
		return (NULL);
	}
	head = forked_env_ll;
	while (env_ll != NULL)
	{
		forked_env_ll->key = ft_strdup(env_ll->key);
		forked_env_ll->value = ft_strdup(env_ll->value);
		forked_env_ll->next = env_ll->next;
		env_ll = env_ll->next;
		if (env_ll != NULL)
		{
			forked_env_ll->next = lstnew_env_link();
			forked_env_ll = forked_env_ll->next;
		}
	}
	forked_env_ll->next = NULL;
	return (head);
}

int	is_a_builtin(char *content)
{
	if (!ft_strcmp(content, "echo")
		|| !ft_strcmp(content, "cd")
		|| !ft_strcmp(content, "pwd")
		|| !ft_strcmp(content, "export")
		|| !ft_strcmp(content, "unset")
		|| !ft_strcmp(content, "env")
		|| !ft_strcmp(content, "exit"))
		return (0);
	return (1);
}

static int	select_builtin_to_go_in(t_node_ms *node,
	t_env_ms **env_ll, t_pipes_ms *pipes)
{
	int	ret;

	ret = 0;
	if (!ft_strcmp(node->content[0], "echo"))
		ret = ft_echo(node, pipes);
	else if (!ft_strcmp(node->content[0], "cd"))
		ret = ft_cd(node->content + 1, *env_ll);
	else if (!ft_strcmp(node->content[0], "pwd"))
		ret = ft_pwd(node->outfile, node->outfile_mode, pipes);
	else if (!ft_strcmp(node->content[0], "export"))
		ret = ft_export(node, *env_ll, pipes);
	else if (!ft_strcmp(node->content[0], "unset"))
		ret = ft_unset(node->content + 1, env_ll);
	else if (!ft_strcmp(node->content[0], "env"))
		ret = ft_env(node, *env_ll, pipes);
	else if (!ft_strcmp(node->content[0], "exit"))
		ret = ft_exit(node->content + 1, *env_ll, pipes);
	return (ret);
}

int	exec_builtin(t_node_ms *node, t_env_ms **env_ll,
	t_pipes_ms *pipes, int exit_code_redirs)
{
	t_env_ms	*forked_env_ll;
	int			ret;

	if (exit_code_redirs != 0)
		return (exit_code_redirs);
	if (node->shell == TOK_SUBSHELL)
	{
		forked_env_ll = make_a_copy_of_env_ll(*env_ll);
		if (!forked_env_ll)
			return (-1);
		ret = select_builtin_to_go_in(node, &forked_env_ll, pipes);
		free_env_list(forked_env_ll);
	}
	else
		ret = select_builtin_to_go_in(node, env_ll, pipes);
	return (ret);
}
