/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 07:23:01 by kbrousse          #+#    #+#             */
/*   Updated: 2022/08/27 20:18:44 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	prepare_bonus(t_pipex *pipex, int argc, char **argv, char **env)
{
	int	i;	

	i = -1;
	pipex->pipefd = ft_calloc((argc - 4), sizeof(int *));
	if (pipex->pipefd == NULL)
		clear_program(pipex, "In prepare_bonus.c, malloc failed");
	while (++i < argc - 4)
	{
		pipex->pipefd[i] = ft_calloc(2, sizeof(int));
		if (*(pipex->pipefd)[i] == -1)
			clear_program(pipex, "In prepare_bonus.c, malloc failed");
	}
	several_commands_requested(pipex, argc, argv, env);
}
