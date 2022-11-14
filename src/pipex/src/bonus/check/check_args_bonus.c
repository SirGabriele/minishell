/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 15:54:05 by kbrousse          #+#    #+#             */
/*   Updated: 2022/08/27 15:54:33 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	check_args_bonus(t_pipex *pipex, int argc, char **argv, char **env)
{
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		verify_files_access_here_doc(pipex, argc, argv);
		verify_cmd_access_here_doc(pipex, argc, argv, env);
	}
	else
	{
		verify_files_access(pipex, argc, argv);
		verify_cmd_access(pipex, argc, argv, env);
	}
}
