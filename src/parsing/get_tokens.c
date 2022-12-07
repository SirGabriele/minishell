#include "../../includes/minishell.h"

static t_token_ms	*initialize_token(void)
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

static int	check_tokens_left(char *user_input)
{
	int	i;

	i = 0;
	while (user_input[i])
	{
		if (ft_isspace(user_input[i]) && !what_is_index_in(user_input, i))
			break;
		i++;
	}
	while (user_input[i])
	{
		if (!ft_isspace(user_input[i]))
			return (1);
		i++;
	}
	return (0);
}

static t_token_ms	*assign_token_delim(t_token_ms *tokens, char *user_input, char *delim[10], char **env)
{
	tokens = lst_fill(tokens, user_input, delim, env);
	if (!tokens)
		return (NULL);
	if (check_tokens_left(user_input))
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

t_token_ms	*get_tokens(char *user_input, char *delim[10], char **env)
{
	t_token_ms	*tokens;
	t_token_ms	*tmp_tokens;
	int			i;

	tokens = initialize_token();
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
			tokens = assign_token_delim(tokens, user_input + i, delim, env);
			if (!tokens)
			{
				free_tokens(tmp_tokens);
				return (NULL);
			}
			i += token_length(user_input + i, delim);
		}
	}
	return (tmp_tokens);
}
