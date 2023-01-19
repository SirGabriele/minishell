/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_list_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:51:37 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:51:38 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static t_token_ms	*get_right_list(t_token_ms *tokens, int index_token)
{
	while (index_token)
	{
		tokens = tokens->next;
		index_token--;
	}
	return (tokens);
}

static t_token_ms	*set_everything_to_null(t_token_ms *tokens)
{
	tokens = ft_lstnew_token();
	if (!tokens)
		return (NULL);
	tokens->type = TOK_NULL;
	tokens->content = NULL;
	tokens->next = NULL;
	return (tokens);
}

static t_token_ms	**get_both_halves(t_token_ms *first_half, int index_token)
{
	t_token_ms	**splitted_tokens;
	t_token_ms	*second_half;

	splitted_tokens = malloc(3 * sizeof(t_token_ms *));
	if (!splitted_tokens)
		return (NULL);
	if (is_operator(first_half->type))
		splitted_tokens[0] = set_everything_to_null(splitted_tokens[0]);
	else
	{
		splitted_tokens[0] = get_first_half(first_half, index_token);
		if (!splitted_tokens[0])
			return (NULL);
	}
	second_half = get_right_list(first_half, index_token + 1);
	splitted_tokens[1] = get_second_half(second_half);
	if (!splitted_tokens[1])
	{
		free_splitted_tokens(splitted_tokens);
		return (NULL);
	}
	splitted_tokens[2] = NULL;
	return (splitted_tokens);
}

/************************************************************/
/*															*/
/*	Splits the linked list in two							*/
/*															*/
/*	Parameters:												*/
/*		tokens	-	linked list								*/
/*															*/
/*	Return:													*/
/*		splitted_tokens	-	double array containing			*/
/*							both halves						*/
/*															*/
/************************************************************/

t_token_ms	**split_list(t_token_ms *tokens)
{
	t_token_ms	**splitted_tokens;
	t_token_ms	*cpy_tokens;
	int			index_token;

	cpy_tokens = tokens;
	index_token = 1;
	while (cpy_tokens)
	{
		if ((cpy_tokens->next && is_operator(cpy_tokens->next->type)
				&& is_token_in_parenthesis(tokens, index_token + 1) \
				== TOK_SHELL)
			|| (is_operator(cpy_tokens->type) && index_token == 1))
		{
			splitted_tokens = get_both_halves(tokens, index_token);
			if (!splitted_tokens)
				return (NULL);
			return (splitted_tokens);
		}
		index_token++;
		cpy_tokens = cpy_tokens->next;
	}
	return (NULL);
}
