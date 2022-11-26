#include "../../includes/minishell.h"

static t_token_ms	*malloc_token(void)
{
	t_token_ms	*tokens;

	tokens = malloc(sizeof(t_token_ms));
	if (!tokens)
		return (NULL);
	tokens->content = NULL;
	tokens->next = NULL;
	tokens->type = 0;
	return (tokens);
}

static t_token_ms	*assign_token_delim(t_token_ms *tokens, char *user_input, char *delim[7])
{
	tokens = lst_fill(tokens, user_input, delim);
	if (!tokens)
	{
		ft_putstr_fd("Error : malloc could not be done\n", 2);
		return (NULL);
	}
	if (ft_strlen(tokens->content) != ft_strlen(user_input))
	{
		tokens->next = lstnew_token();
		if (!tokens->next)
		{
			ft_putstr_fd("Error : malloc could not be done\n", 2);
			return (NULL);
		}
		tokens = tokens->next;
	}
	else
		tokens->next = NULL;
	return (tokens);
}

t_token_ms	*get_tokens(char *user_input, char *delim[7])
{
	t_token_ms	*tokens;
	t_token_ms	*tmp_tokens;
	int			i;

	tokens = malloc_token();
	if (!tokens)
		return (NULL);
	tmp_tokens = tokens;
	i = 0;
	while (ft_isspace(user_input[i]) && !what_is_index_in(user_input, i))
		i++;
	while (user_input[i])
	{
		tokens = assign_token_delim(tokens, user_input + i, delim);
		if (!tokens)
		{
			free_tokens(tmp_tokens);
			return (NULL);
		}
		i += token_length(user_input + i, delim);
		while (ft_isspace(user_input[i]) && !what_is_index_in(user_input, i))
			i++;
	}
	return (tmp_tokens);
}
