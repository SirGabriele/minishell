/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_children_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:22:33 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:42:43 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static pid_t	*initialize_pid_arr(pid_t *pid_arr, int nb_cmd)
{
	pid_arr = ft_calloc(sizeof(pid_t), nb_cmd);
	if (pid_arr == NULL)
	{
		perror(NULL);
		return (NULL);
	}
	return (pid_arr);
}

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

t_children_ms	*initialize_children(int nb_nodes)
{
	t_children_ms	*children;

	children = malloc(sizeof(t_children_ms));
	if (children == NULL)
	{
		perror(NULL);
		return (NULL);
	}
	children->pid_arr = initialize_pid_arr(children->pid_arr, nb_nodes);
	if (children->pid_arr == NULL)
	{
		perror(NULL);
		free(children);
		return (NULL);
	}
	children->index = 0;
	return (children);
}
