/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_outfile_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:57:05 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:58:10 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void	redirect_outfile(int *pipe_after, t_node_ms *node)
{
	int	fd;

	if (node->outfile != NULL)
	{
		if (node->outfile_mode == TOK_TRUNC)
			fd = open(node->outfile, O_WRONLY | O_TRUNC);
		if (node->outfile_mode == TOK_APPEND)
			fd = open(node->outfile, O_WRONLY | O_APPEND);
		dup2(fd, 1);
		close(fd);
	}
	if (node->outfile == NULL && node->outfile_mode == TOK_PIPE)
		dup2(pipe_after[1], 1);
	close(pipe_after[1]);
	close(pipe_after[0]);
}
