#include "../../includes/minishell.h"

static char	*get_content_delim(char *delim)
{
	char	*content;
	int		len_delim;

	len_delim = ft_strlen(delim);
	content = malloc((len_delim + 1) * sizeof(char));
	if (!content)
		return (NULL);
	ft_strncpy(content, delim, len_delim);
	return (content);
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
/*		tokens - link										*/
/*		user_input - command line							*/
/*		delim - delimiters									*/
/*		env - environment variables							*/
/*															*/
/*	Return:													*/
/*		tokens - link										*/
/*															*/
/************************************************************/

t_token_ms	*fill_token(t_token_ms *tokens, char *user_input, char *delim[10], \
	char **env)
{
	int	index_delim;

	index_delim = get_index_delimiter(user_input, delim, 0);
	if (index_delim >= 0)
	{
		tokens->type = identify_delim_token(index_delim);
		tokens->content = get_content_delim(delim[index_delim]);
		if (!tokens->content)
			return (NULL);
	}
	else
	{
		tokens->type = TOK_STRING;
		tokens->content = get_content_string(user_input, delim);
		if (!tokens->content)
			return (NULL);
		tokens->content = expand_var_with_dollar(tokens->content, env);
		if (!tokens->content)
			return (NULL);
	}
	return (tokens);
}
