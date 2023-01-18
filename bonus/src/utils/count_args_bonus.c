/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_args_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:08:22 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:08:28 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

/****************************************************************/
/*																*/
/*	Counts the number of arguments that the command has			*/
/*																*/
/*	Parameters:													*/
/*		content	-	a double array containing the command and	*/
/*					its arguments								*/
/*																*/
/*	Return:														*/
/*		i		-	the count									*/
/*																*/
/****************************************************************/

int	count_args(char **content)
{
	int	i;

	i = 0;
	while (content[i])
		i++;
	return (i);
}
