/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_token_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <jsauvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 22:50:58 by jsauvain          #+#    #+#             */
/*   Updated: 2023/01/18 22:50:58 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static t_enum_token	check_second_half(int index_delimiter, \
	t_enum_token token_type)
{
	if (index_delimiter == 5)
		token_type = TOK_TRUNC;
	else if (index_delimiter == 6)
		token_type = TOK_OR_OPER;
	else if (index_delimiter == 7)
		token_type = TOK_PIPE;
	else if (index_delimiter == 8)
		token_type = TOK_AND_OPER;
	else if (index_delimiter == 9)
		token_type = TOK_NULL;
	return (token_type);
}

static t_enum_token	get_token_type(int index_delimiter)
{
	t_enum_token	token_type;

	token_type = TOK_NULL;
	if (index_delimiter == 0)
		token_type = TOK_OP_PAR;
	else if (index_delimiter == 1)
		token_type = TOK_CL_PAR;
	else if (index_delimiter == 2)
		token_type = TOK_HEREDOC;
	else if (index_delimiter == 3)
		token_type = TOK_APPEND;
	else if (index_delimiter == 4)
		token_type = TOK_INFILE;
	else
		token_type = check_second_half(index_delimiter, token_type);
	return (token_type);
}

static char	*get_content_string(char *user_input, char *delim[10])
{
	char	*tmp;
	int		tok_length;

	tok_length = token_content_length(user_input, delim);
	tmp = malloc((tok_length + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	ft_strncpy(tmp, user_input, tok_length);
	return (tmp);
}

/************************************************************/
/*															*/
/*	Fills link's content and type							*/
/*															*/
/*	Parameters:												*/
/*		tokens		-	the link to be filled				*/
/*		user_input	-	line from the terminal				*/
/*		delim		-	delimiters							*/
/*		env			-	linked list of all env variables	*/
/*															*/
/*	Return:													*/
/*		tokens	-	the filled link							*/
/*															*/
/************************************************************/

t_token_ms	*fill_token(t_token_ms *tokens, char *user_input, char *delim[10])
{
	int	index_delim;

	index_delim = get_index_delimiter(user_input, delim, 0);
	if (index_delim >= 0)
	{
		tokens->type = get_token_type(index_delim);
		tokens->content = ft_strdup(delim[index_delim]);
		if (!tokens->content)
			return (NULL);
	}
	else
	{
		tokens->type = TOK_STRING;
		tokens->content = get_content_string(user_input, delim);
		if (!tokens->content)
			return (NULL);
	}
	return (tokens);
}
