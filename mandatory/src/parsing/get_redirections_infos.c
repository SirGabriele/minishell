/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirections_infos.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:41:42 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:41:42 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	nb_redirs(t_token_ms *tokens)
{
	while (tokens)
	{
		if (is_token_type_a_redir(tokens->type))
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

/****************************************************************/
/*																*/
/*	Gets redirections and stocks them in a list. Gets mode		*/
/*	and file_name of the last infile and outfile redirection	*/
/*																*/
/*	Parameters:													*/
/*		tokens		-	link									*/
/*		operators	-	the last two operators of the			*/
/*						command line							*/
/*																*/
/*	Return:														*/
/*		root	-	edited binary tree							*/
/*																*/
/****************************************************************/

t_node_ms	*get_redirections_infos(t_node_ms *root, t_token_ms *tokens)
{
	if (nb_redirs(tokens))
	{
		root->first_redir = get_redirections_list(tokens);
		if (!root->first_redir)
			return (NULL);
		root = manage_modes_and_files(root);
		if (!root)
			return (NULL);
	}
	return (root);
}
