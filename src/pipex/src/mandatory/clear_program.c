/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:16:47 by kbrousse          #+#    #+#             */
/*   Updated: 2022/08/23 06:47:26 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	clear_pipex_tab_env_paths(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (pipex->tab_env_paths[++i] != NULL)
	{
		free(pipex->tab_env_paths[i]);
		pipex->tab_env_paths[i] = NULL;
	}
	free(pipex->tab_env_paths);
	pipex->tab_env_paths = NULL;
}

static void	clear_pipex_cmd(t_pipex_cmd *first_cmd)
{
	t_pipex_cmd	*copy;
	int			i;

	copy = first_cmd;
	while (copy != NULL)
	{
		copy = copy->next;
		i = -1;
		free(first_cmd->correct_path);
		first_cmd->correct_path = NULL;
		if (first_cmd->tab_cmd)
		{
			while (first_cmd->tab_cmd[++i] != NULL)
			{
				free(first_cmd->tab_cmd[i]);
				first_cmd->tab_cmd[i] = NULL;
			}
			free(first_cmd->tab_cmd);
			first_cmd->tab_cmd = NULL;
		}
		free(first_cmd);
		first_cmd = copy;
	}
}

void	clear_program(t_pipex *pipex, char *perror_str)
{
	if (pipex->first_cmd != NULL)
		clear_pipex_cmd(pipex->first_cmd);
	if (pipex->tab_env_paths != NULL)
		clear_pipex_tab_env_paths(pipex);
	free(pipex->tab_pid);
	free(pipex);
	pipex = NULL;
	if (perror_str != NULL)
	{
		perror(perror_str);
		exit(-1);
	}
	exit(0);
}
