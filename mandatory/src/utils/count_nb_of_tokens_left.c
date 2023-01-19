/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_nb_of_tokens_left.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:43:03 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:43:04 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/****************************************************************/
/*																*/
/*	Counts the number of tokens left in tokens's linked list	*/
/*																*/
/*	Parameters:													*/
/*		content	-	a linked list containing all the tokens		*/
/*																*/
/*	Return:														*/
/*		nb_toknes	-	the count								*/
/*																*/
/****************************************************************/

int	count_nb_of_tokens_left(t_token_ms *tokens)
{
	int	nb_tokens;

	nb_tokens = 0;
	while (tokens)
	{
		nb_tokens++;
		tokens = tokens->next;
	}
	return (nb_tokens);
}
