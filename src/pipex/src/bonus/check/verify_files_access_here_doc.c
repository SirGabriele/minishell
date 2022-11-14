/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_files_access_here_doc.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 15:42:40 by kbrousse          #+#    #+#             */
/*   Updated: 2022/08/27 15:44:24 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	verify_files_access_here_doc(t_pipex *pipex, int argc, char **argv)
{
	int	fd;

	fd = open(argv[argc - 1], O_RDONLY | O_CREAT, 0777);
	if (fd == -1)
		clear_program(pipex, "Outfile opening failed");
	if (close(fd) == -1)
		clear_program(pipex, "Outfile closing failed");
}
