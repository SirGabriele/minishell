#include "../../includes/minishell.h"

static char	*get_content(char *user_input, char *delim[7])
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
	t_token_ms	*tmp_token;
	int			index_delimiter;

	tmp_token = tokens;
	index_delimiter = is_a_delimiter(user_input, delim, 0);
	if (index_delimiter >= 0)
	{
		tmp_token->content = NULL;
		tmp_token->type = identify_delim_token(user_input, delim);
	}
	else
	{
		tmp_token->type = TOK_STRING;
		tmp_token->content = get_content(user_input, delim);
		if (!tmp_token->content)
		{
			ft_putstr_fd("Error : malloc could not be done\n", 2);
			return (NULL);
		}
	}
	return (tmp_token);
}

t_token_ms	*lstnew(void)
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
