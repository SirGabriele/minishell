/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_infile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:56:09 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 23:45:20 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirect_infile(int *pipe_before, t_node_ms *node)
{
	int	fd;

	if (node->infile != NULL && node->infile_mode == TOK_INFILE)
	{
		fd = open(node->infile, O_RDONLY);
		dup2(fd, 0);
		close(fd);
	}
	if ((node->infile == NULL && node->infile_mode == TOK_PIPE)
		|| (node->infile != NULL && node->infile_mode == TOK_HEREDOC))
		dup2(pipe_before[0], 0);
	close(pipe_before[0]);
	close(pipe_before[1]);
}
