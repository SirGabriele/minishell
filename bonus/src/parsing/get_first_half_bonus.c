/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_first_half_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:51:01 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:51:02 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static t_token_ms	*incremente_half_if_needed(t_token_ms *half_1, \
	int index_token)
{
	if (index_token > 1)
	{
		half_1->next = ft_lstnew_token();
		if (!half_1->next)
			return (NULL);
		half_1 = half_1->next;
	}
	else
		half_1->next = NULL;
	return (half_1);
}

/***********************************************/
/*              get_left_list :               */
/*                                             */
/*   copy the token (that represents           */
/*   the first half) in cpy_half_1             */
/*                                             */
/*   index_token represent where the initial   */
/*   token was split                           */
/***********************************************/

t_token_ms	*get_first_half(t_token_ms *tokens, int index_token)
{
	t_token_ms	*half;
	t_token_ms	*cpy_half;

	half = ft_lstnew_token();
	if (!half)
		return (NULL);
	cpy_half = half;
	while (index_token)
	{
		half->content = NULL;
		half->content = ft_strjoin(half->content, tokens->content);
		if (!half->content)
			return (NULL);
		half->type = tokens->type;
		half = incremente_half_if_needed(half, index_token);
		if (!half)
		{
			free_tokens(cpy_half);
			return (NULL);
		}
		tokens = tokens->next;
		index_token--;
	}
	return (cpy_half);
}
