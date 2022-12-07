#include "../../includes/minishell.h"

t_tokens	identify_delim_token(char *user_input, char *delim[10])
{
	t_tokens	token_type;
	int			index_delimiter;

	token_type = 0;
	index_delimiter = is_a_delimiter(user_input, delim, 0);
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
	else if (index_delimiter == 5)
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

int	token_length(char *user_input, char *delim[10])
{
	int	i;
	int	index_delim;

	i = 0;
	while (user_input[i])
	{
		index_delim = is_a_delimiter(user_input, delim, i);
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

int	is_a_delimiter(const char *user_input, char *delim[10], int index)
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
