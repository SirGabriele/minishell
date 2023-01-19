/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_is_index_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:44:43 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:44:44 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/********************************************************************/
/*                                                     				*/
/*  Determines if the index is between single/double quotes			*/
/*	or not in any sort of quotes									*/
/*                                                     	 			*/
/*  Parameters:														*/
/*		user_input	-	line from the terminal						*/
/*		i			-	index of the character to check				*/
/*																	*/
/*  Return:															*/
/*		 0	-	character is alone									*/
/*		-1	-	character is between single or double quotes		*/
/*																	*/
/********************************************************************/

int	what_is_index_in(const char *user_input, int i)
{
	int		j;
	char	c;

	j = 0;
	while (user_input[j] != '\0')
	{
		if (user_input[j] == '\"' || user_input[j] == '\'')
		{
			c = user_input[j];
			j++;
			while (user_input[j] != c && user_input[j] != '\0')
				j++;
			if (j > i)
				return (-1);
		}
		else if (j == i)
			return (0);
		j++;
	}
	return (0);
}
