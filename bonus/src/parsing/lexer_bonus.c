/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:51:25 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:51:25 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

/************************************************************/
/*															*/
/*	Verifies if other tokens are left in user_input			*/
/*															*/
/*	Parameters:												*/
/*		user_input	-	line from the terminal				*/
/*															*/
/*	Return:													*/
/*		1	-	Yes											*/
/*		0	-	No											*/
/*															*/
/************************************************************/

static int	are_there_tokens_left(char *user_input)
{
	int	i;

	i = 0;
	while (user_input[i]
		&& ft_isspace(user_input[i])
		&& !what_is_index_in(user_input, i))
		i++;
	while (user_input[i])
	{
		if (!ft_isspace(user_input[i]))
			return (1);
		i++;
	}
	return (0);
}

static t_token_ms	*assign_token(t_token_ms *tokens, \
	char *user_input, char *delim[10])
{
	int	token_len;

	tokens = fill_token(tokens, user_input, delim);
	if (!tokens)
		return (NULL);
	token_len = token_content_length(user_input, delim);
	if (are_there_tokens_left(user_input + token_len))
	{
		tokens->next = ft_lstnew_token();
		if (!tokens->next)
			return (NULL);
		tokens = tokens->next;
	}
	else
		tokens->next = NULL;
	return (tokens);
}

static t_token_ms	*create_token_list(char *user_input, char *delim[10])
{
	t_token_ms	*tokens;
	t_token_ms	*tmp_tokens;
	int			i;

	tokens = ft_lstnew_token();
	if (!tokens)
		return (NULL);
	tmp_tokens = tokens;
	i = 0;
	while (user_input[i])
	{
		if (ft_isspace(user_input[i]) && !what_is_index_in(user_input, i))
			i++;
		else
		{
			tokens = assign_token(tokens, user_input + i, delim);
			if (!tokens)
			{
				free_tokens(tmp_tokens);
				return (NULL);
			}
			i += token_content_length(user_input + i, delim);
		}
	}
	return (tmp_tokens);
}

static void	fill_delimiters(char **delimiters)
{
	delimiters[0] = "(";
	delimiters[1] = ")";
	delimiters[2] = "<<";
	delimiters[3] = ">>";
	delimiters[4] = "<";
	delimiters[5] = ">";
	delimiters[6] = "||";
	delimiters[7] = "|";
	delimiters[8] = "&&";
	delimiters[9] = NULL;
}

/****************************************************************/
/*																*/
/*	Converts user_input into a link list containing all tokens	*/
/*																*/
/*	Parameters:													*/
/*		user_input	-	command line							*/
/*		env			-	environment variables					*/
/*																*/
/*	Return:														*/
/*		tokens	-	the link list								*/
/*		NULL	-	something failed							*/
/*																*/
/****************************************************************/

t_token_ms	*lexer(char *user_input)
{
	t_token_ms	*tokens;
	char		*delimiters[10];

	fill_delimiters(delimiters);
	tokens = create_token_list(user_input, delimiters);
	if (!tokens)
		return (NULL);
	return (tokens);
}
