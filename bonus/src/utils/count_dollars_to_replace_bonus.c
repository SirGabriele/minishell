/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_dollars_to_replace_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:06:55 by kbrousse          #+#    #+#             */
/*   Updated: 2023/01/18 16:06:56 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

/****************************************************************/
/*																*/
/*	Counts the number of dollars to replace in the user's line	*/
/*																*/
/*	Parameters:													*/
/*		content	-	a double array containing the command and	*/
/*					its arguments								*/
/*																*/
/*	Return:														*/
/*		nb_dollars	-	the count								*/
/*																*/
/****************************************************************/

int	count_dollars_to_replace(char *content)
{
	int	i;
	int	nb_dollars;

	i = 0;
	nb_dollars = 0;
	while (content[i])
	{
		if (content[i] == '$' && !what_is_dollar_in(content, i))
			nb_dollars++;
		i++;
	}
	return (nb_dollars);
}
