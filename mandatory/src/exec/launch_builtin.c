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

int	exec_builtin(t_node_ms *node, t_env_ms **env_ll,
	t_pipes_ms *pipes, int exit_code_redirs)
{
	int	ret;

	if (exit_code_redirs != 0)
		return (exit_code_redirs);
	ret = 0;
	if (!ft_strcmp(node->content[0], "echo"))
		ret = ft_echo(node);
	else if (!ft_strcmp(node->content[0], "cd"))
		ret = ft_cd(node->content + 1, *env_ll);
	else if (!ft_strcmp(node->content[0], "pwd"))
		ret = ft_pwd(node->outfile, node->outfile_mode);
	else if (!ft_strcmp(node->content[0], "export"))
		ret = ft_export(node, *env_ll);
	else if (!ft_strcmp(node->content[0], "unset"))
		ret = ft_unset(node->content + 1, env_ll);
	else if (!ft_strcmp(node->content[0], "env"))
		ret = ft_env(node, *env_ll);
	else if (!ft_strcmp(node->content[0], "exit"))
		ret = ft_exit(node->content + 1, *env_ll, pipes);
	return (ret);
}
