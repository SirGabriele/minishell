/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_files_access.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 02:00:21 by kbrousse          #+#    #+#             */
/*   Updated: 2022/08/23 02:06:02 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	verify_files_access(t_pipex *pipex, int argc, char **argv)
{
	int	fd;

	fd = open(argv[argc - 1], O_RDONLY | O_CREAT, 0777);
	if (fd == -1)
		clear_program(pipex, "Outfile opening failed");
	if (close(fd) == -1)
		clear_program(pipex, "Outfile closing failed");
}
