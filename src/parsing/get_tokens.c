#include "../../includes/minishell.h"

int	is_a_delimiter(const char *user_input, char *delim[7])
{
	int	i;
	int	length_delim;

	i = 0;
	while (delim[i] != NULL)
	{
		length_delim = ft_strlen(delim[i]);
		if (ft_strncmp(user_input, delim[i], length_delim) == 0
			&& !what_is_index_in(user_input, i))
			return (i);
		i++;
	}
	return (0);
}

int	assign_token_delim(t_token_ms *tokens, char *user_input, char *delim[7])
{
	char	*delim_tmp[3];
	int		index_delimiter;
	
	index_delimiter = is_a_delimiter(user_input, delim);
	if (user_input[0] == user_input[1])
	{
		delim_tmp[0] = delim[index_delimiter];
		delim_tmp[1] = delim[index_delimiter];
		delim_tmp[2] = '\0';
		tokens->next = ft_lstnew(delim_tmp);
		tokens->type = identify_token(index_delimiter, 2);
		tokens = tokens->next;
		return (2);
	}
	else
	{
		tokens->next = ft_lstnew(delim[index_delimiter]);
		tokens->type = identify_token(index_delimiter, 1);
		tokens = tokens->next;
		return (1);
	}
	return (0);
}

int	assign_token_no_delim(t_token_ms *tokens, char *user_input, char *delim[7])
{
	(void)tokens;
	(void)user_input;
	(void)delim;
	return (0);
}

t_token_ms	*get_tokens(t_token_ms *tokens, char *user_input, char *delim[7])
{
	t_token_ms	*tmp_tokens;
	int	i;
	
	tmp_tokens = tokens;
	i = 0;
	while (*user_input == ' ' && *user_input)
		user_input++;
	while (user_input[i])
	{
		if (is_a_delimiter(user_input, delim))
			i += assign_token_delim(tokens, user_input + i, delim);
		else if (user_input[i] == ' ' && !what_is_index_in(user_input, i))
			i++; 
		else
			i += assign_token_no_delim(tokens, user_input, delim);
	}
	return (tmp_tokens);
}

