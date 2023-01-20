/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_infile_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:56:09 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:57:53 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static void	redirect_infile(int *pipe_before, t_node_ms *node)
{
	int	fd;

	if (node->infile != NULL && node->infile_mode == TOK_INFILE)
	{
		fd = open(node->infile, O_RDONLY);
		dup2(fd, 0);
		if (fd != -1)
			close(fd);
	}
	if ((node->infile == NULL && node->infile_mode == TOK_PIPE)
		|| (node->infile != NULL && node->infile_mode == TOK_HEREDOC))
		dup2(pipe_before[0], 0);
}

static void	redirect_outfile(int *pipe_after, t_node_ms *node)
{
	int	fd;

	if (node->outfile != NULL)
	{
		if (node->outfile_mode == TOK_TRUNC)
			fd = open(node->outfile, O_WRONLY | O_TRUNC);
		if (node->outfile_mode == TOK_APPEND)
			fd = open(node->outfile, O_WRONLY | O_APPEND);
		dup2(fd, 1);
		if (fd != -1)
			close(fd);
	}
	if (node->outfile == NULL && node->outfile_mode == TOK_PIPE)
		dup2(pipe_after[1], 1);
}

void	redirect_infile_outfile(t_pipes_ms *pipes, t_node_ms *node)
{
	redirect_infile(pipes->before, node);
	redirect_outfile(pipes->after, node);
}
