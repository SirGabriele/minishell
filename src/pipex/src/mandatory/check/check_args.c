/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 01:58:09 by kbrousse          #+#    #+#             */
/*   Updated: 2022/08/23 02:20:05 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	check_args(t_pipex *pipex, int argc, char **argv, char **env)
{
	verify_files_access(pipex, argc, argv);
	verify_cmd_access(pipex, argc, argv, env);
}
