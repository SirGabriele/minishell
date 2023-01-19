/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:41:01 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 23:11:27 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
