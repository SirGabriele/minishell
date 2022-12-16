#include "../../includes/minishell.h"

/************************************************************/
/*															*/
/*	Definition:	Verify if there are upcoming tokens			*/
/*															*/
/*	Parameters:												*/
/*		user_input = command line							*/
/*															*/
/*	Return:													*/
/*		1 - Upcoming token(s)								*/
/*		0 - No upcoming token(s)							*/
/*															*/
/************************************************************/

static int	check_tokens_left(char *user_input)
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
	char *user_input, char *delim[10], char **env)
{
	int	token_len;

	tokens = fill_token(tokens, user_input, delim, env);
	if (!tokens)
		return (NULL);
	token_len = token_content_length(user_input, delim);
	if (check_tokens_left(user_input + token_len))
	{
		tokens->next = lstnew_token();
		if (!tokens->next)
			return (NULL);
		tokens = tokens->next;
	}
	else
		tokens->next = NULL;
	return (tokens);
}

static t_token_ms	*get_tokens(char *user_input, char *delim[10], char **env)
{
	t_token_ms	*tokens;
	t_token_ms	*tmp_tokens;
	int			i;

	tokens = lstnew_token();
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
			tokens = assign_token(tokens, user_input + i, delim, env);
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

static void	fill_delimiters(char **delim)
{
	delim[0] = "(";
	delim[1] = ")";
	delim[2] = "<<";
	delim[3] = ">>";
	delim[4] = "<";
	delim[5] = ">";
	delim[6] = "||";
	delim[7] = "|";
	delim[8] = "&&";
	delim[9] = NULL;
}

/************************************************************/
/*															*/
/*	Definition: Convert user_input into a link list			*/
/*				containing all tokens						*/
/*															*/
/*	Parameters:												*/
/*		user_input - command line							*/
/*		env - environment variables							*/
/*															*/
/*	Return:													*/
/*		tokens - the link list								*/
/*		NULL - failure										*/
/*															*/
/************************************************************/

t_token_ms	*lexer(char *user_input, char **env)
{
	t_token_ms	*tokens;
	char		*delim[10];

	fill_delimiters(delim);
	tokens = get_tokens(user_input, delim, env);
	if (!tokens)
		return (NULL);
	return (tokens);
}
