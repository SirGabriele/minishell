#include "../../includes/minishell.h"

static char	*get_content_delim(char *user_input, char *delim)
{
	char	*content;

	if (user_input[0] == user_input[1])
	{
		content = malloc(3 * sizeof(char));
		if (!content)
			return (NULL);
		content[0] = delim[0];
		content[1] = delim[0];
		content[2] = '\0';
	}
	else
	{
		content = malloc(2 * sizeof(char));
		if (!content)
			return (NULL);
		content[0] = delim[0];
		content[1] = '\0';
	}
	return (content);
}

static char	*get_content_string(char *user_input, char *delim[7])
{
	char	*tmp;
	int		i;
	int		tok_length;

	tok_length = token_length(user_input, delim);
	tmp = malloc((tok_length + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < tok_length)
	{
		tmp[i] = user_input[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

t_token_ms	*lst_fill(t_token_ms *tokens, char *user_input, char *delim[7])
{
	int	index_delim;

	index_delim = is_a_delimiter(user_input, delim, 0);
	if (index_delim >= 0)
	{
		tokens->type = identify_delim_token(user_input, delim);
		tokens->content = get_content_delim(user_input, delim[index_delim]);
		if (!tokens->content)
		{
			ft_putstr_fd("Error : malloc could not be done\n", 2);
			return (NULL);
		}
	}
	else
	{
		tokens->type = TOK_STRING;
		tokens->content = get_content_string(user_input, delim);
		if (!tokens->content)
		{
			ft_putstr_fd("Error : malloc could not be done\n", 2);
			return (NULL);
		}
	}
	return (tokens);
}

t_token_ms	*lstnew_token(void)
{
	t_token_ms	*elem;

	elem = malloc(sizeof(t_token_ms));
	if (!elem)
	{
		ft_putstr_fd("Error : malloc could not be done\n", 2);
		return (NULL);
	}
	elem->type = 0;
	elem->content = NULL;
	elem->next = NULL;
	return (elem);
}
