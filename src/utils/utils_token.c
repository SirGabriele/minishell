#include "../../includes/minishell.h"

/************************************************************/
/*															*/
/*	Definition:	Get the length of token's content			*/
/*															*/
/*	Parameters:												*/
/*		user_input - command line							*/
/*		delim - delimiters									*/
/*															*/
/*	Return:													*/
/*		i - token's content length							*/
/*															*/
/************************************************************/

int	token_content_length(char *user_input, char *delim[10])
{
	int	i;
	int	index_delim;

	i = 0;
	while (user_input[i])
	{
		index_delim = get_index_delimiter(user_input, delim, i);
		if (index_delim >= 0 && i)
			return (i);
		else if (index_delim >= 0 && !i)
			return (ft_strlen(delim[index_delim]));
		else if (ft_isspace(user_input[i]) && !what_is_index_in(user_input, i))
			return (i);
		i++;
	}
	return (i);
}

/************************************************************/
/*															*/
/*	Definition: get the delimiter's index if the token 		*/
/*				is a delimiter								*/
/*															*/
/*	Parameters:												*/
/*		user_input - command line							*/
/*		delim - delimiters									*/
/*		index - index of the character(s) to check			*/
/*				in user_input								*/
/*															*/
/*	Return:													*/
/*		 i - index of delimiter								*/
/*		-1 - if not a delimite								*/
/*															*/
/************************************************************/

int	get_index_delimiter(const char *user_input, char *delim[10], int index)
{
	int	i;
	int	length_delim;

	i = 0;
	while (delim[i] != NULL)
	{
		length_delim = ft_strlen(delim[i]);
		if (ft_strncmp(user_input + index, delim[i], length_delim) == 0
			&& !what_is_index_in(user_input, index))
			return (i);
		i++;
	}
	return (-1);
}

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

int	check_if_token_is_redir(t_enum_token token_type)
{
	if (token_type == TOK_INFILE)
		return (1);
	if (token_type == TOK_TRUNC)
		return (2);
	if (token_type == TOK_HEREDOC)
		return (3);
	if (token_type == TOK_APPEND)
		return (4);
	return (0);
}

int	is_operator(t_enum_token type)
{
	if (type == TOK_AND_OPER || type == TOK_OR_OPER || type == TOK_PIPE)
		return (1);
	return (0);
}
