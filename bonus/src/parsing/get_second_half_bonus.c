/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_second_half_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:51:20 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:51:21 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static t_token_ms	*incremente_half_2_if_needed(t_token_ms *half_2, \
	t_token_ms *tokens)
{
	if (count_nb_of_tokens_left(tokens->next))
	{
		half_2->next = ft_lstnew_token();
		if (!half_2->next)
			return (NULL);
		half_2 = half_2->next;
	}
	else
		half_2->next = NULL;
	return (half_2);
}

/***********************************************/
/*            get_second_half :                */
/*                                             */
/*   copy the token (that represents           */
/*   the second half) in cpy_half_2            */
/*                                             */
/*   The function is called in split_list      */
/*   by get_both_halves(tokens, index_token)   */
/***********************************************/

t_token_ms	*get_second_half(t_token_ms *tokens)
{
	t_token_ms	*half_2;
	t_token_ms	*cpy_half_2;

	half_2 = ft_lstnew_token();
	if (!half_2)
		return (NULL);
	cpy_half_2 = half_2;
	while (tokens)
	{
		half_2->content = NULL;
		half_2->content = ft_strjoin(half_2->content, tokens->content);
		if (!half_2->content)
			return (NULL);
		half_2->type = tokens->type;
		half_2 = incremente_half_2_if_needed(half_2, tokens);
		if (!half_2)
		{
			free_tokens(cpy_half_2);
			return (NULL);
		}
		tokens = tokens->next;
	}
	return (cpy_half_2);
}
