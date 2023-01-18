/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_node_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:13:34 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:13:35 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void	initialize_node(t_node_ms *node)
{
	node->left = NULL;
	node->right = NULL;
	node->first_redir = NULL;
	node->content = NULL;
	node->infile = NULL;
	node->outfile = NULL;
	node->infile_mode = TOK_NULL;
	node->infile_mode = TOK_NULL;
	node->shell = TOK_NULL;
	node->operator = TOK_NULL;
}
