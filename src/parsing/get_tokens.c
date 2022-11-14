#include "../../includes/minishell.h"

static t_token_ms	*assign_token_delim(t_token_ms *tokens, char *user_input, char *delim[7])
{
	tokens = lst_fill(tokens, user_input, delim);
	tokens->next = lstnew();
	if (!tokens->next)
	{
		ft_printf_error("Error : malloc could not be done\n");
		free_lst_content(tokens);
		exit(1);
	}
	tokens = tokens->next;
	return (tokens);
}

t_token_ms	*get_tokens(t_token_ms *tokens, char *user_input, char *delim[7])
{
	t_token_ms	*tmp_tokens;
	int			i;
	
	tmp_tokens = tokens;
	i = 0;
	while (user_input[i])
	{
		while (ft_isspace(user_input[i]) && !what_is_index_in(user_input, i))
			i++;
		tokens = assign_token_delim(tokens, user_input + i, delim);
		i += token_length(user_input + i, delim);
	}
	return (tmp_tokens);
}

