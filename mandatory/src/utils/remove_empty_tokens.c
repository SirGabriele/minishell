/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_empty_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:44:21 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/19 00:34:10 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token_ms	*remove_firsts_empty_tokens(t_token_ms *tokens_parsed, \
	t_token_ms *tokens_unparsed)
{
	t_token_ms	*cursor;

	while (tokens_parsed)
	{
		if (!ft_strcmp(tokens_parsed->content, "")
			&& tokens_unparsed->content[0] == '0')
		{
			cursor = tokens_parsed->next;
			free(tokens_parsed->content);
			tokens_parsed->content = NULL;
			free(tokens_parsed);
			tokens_parsed = cursor;
		}
		else
			return (tokens_parsed);
		tokens_unparsed = tokens_unparsed->next;
	}
	return (tokens_parsed);
}

static t_token_ms	*delete_token(t_token_ms *tokens_parsed)
{
	t_token_ms	*cursor;

	cursor = tokens_parsed->next->next;
	free(tokens_parsed->next->content);
	tokens_parsed->next->content = NULL;
	free(tokens_parsed->next);
	tokens_parsed->next = cursor;
	return (tokens_parsed->next);
}

t_token_ms	*remove_empty_tokens(t_token_ms *tokens_parsed, \
	t_token_ms *tokens_unparsed)
{
	t_token_ms	*head;

	tokens_parsed = remove_firsts_empty_tokens(tokens_parsed, tokens_unparsed);
	head = tokens_parsed;
	while (tokens_parsed)
	{
		if (tokens_parsed->next && tokens_unparsed->next
			&& !ft_strcmp(tokens_parsed->next->content, "")
			&& tokens_unparsed->next->content[0] == '0')
		{
			tokens_parsed->next = delete_token(tokens_parsed);
			tokens_unparsed = tokens_unparsed->next;
		}
		else
		{
			tokens_parsed = tokens_parsed->next;
			tokens_unparsed = tokens_unparsed->next;
		}
	}
	return (head);
}
