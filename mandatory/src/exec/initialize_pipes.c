/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:22:30 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 23:44:58 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/****************************************************************/
/*																*/
/*	Initializes the children structure aswell as its content	*/
/*																*/
/*	Parameters:													*/
/*		children	-	the children structure					*/
/*		nb_nodes	-	the amout of nodes						*/
/*																*/
/*	Return:														*/
/*		children	-	the initialized structure				*/
/*		NULL		-	a malloc failed							*/
/*																*/
/****************************************************************/

t_pipes_ms	*initialize_pipes(t_node_ms *root, t_children_ms *children)
{
	t_pipes_ms	*pipes;

	pipes = malloc(sizeof(t_pipes_ms));
	if (pipes == NULL)
	{
		perror(NULL);
		return (NULL);
	}
	if (pipe(pipes->before) == -1 || pipe(pipes->after) == -1)
	{
		free(pipes);
		return (NULL);
	}
	pipes->tree_root = root;
	pipes->children = children;
	return (pipes);
}
