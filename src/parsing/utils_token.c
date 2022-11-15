#include "../../includes/minishell.h"

t_tokens	identify_delim_token(char *user_input, char *delim[7])
{
	t_tokens	token_type;
	int			index_delimiter;

	token_type = 0;
	index_delimiter = is_a_delimiter(user_input, delim);
	if (index_delimiter == 2 && user_input[0] == user_input[1])
		token_type = TOK_HEREDOC;
	else if (index_delimiter == 3 && user_input[0] == user_input[1])
		token_type = TOK_OUTF_APPEND;
	else if (index_delimiter == 4 && user_input[0] == user_input[1])
		token_type = TOK_AND_OPER;
	else if (index_delimiter == 5 && user_input[0] == user_input[1])
		token_type = TOK_OR_OPER;
	else if (index_delimiter == 0)
		token_type = TOK_OP_PAR;
	else if (index_delimiter == 1)
		token_type = TOK_CL_PAR;
	else if (index_delimiter == 2)
		token_type = TOK_INFILE;
	else if (index_delimiter == 3)
		token_type = TOK_OUTF_TRUNC;
	else if (index_delimiter == 5)
		token_type = TOK_PIPE;
	return (token_type);
}

int	token_length(char *user_input, char *delim[7])
{
	int	i;

	i = 0;
	while (user_input[i])
	{
		if (is_a_delimiter(user_input + i, delim) >= 0 && i)
			return (i);
		else if (is_a_delimiter(user_input, delim) >= 0 && !i)
		{
			if (user_input[0] == user_input[1])
				return (2);
			else
				return (1);
		}
		else if (ft_isspace(user_input[i]) && !what_is_index_in(user_input, i))
			return (i);
		i++;
	}
	return (i);
}

int	is_a_delimiter(const char *user_input, char *delim[7])
{
	int	i;
	int	length_delim;

	i = 0;
	while (delim[i] != NULL)
	{
		length_delim = ft_strlen(delim[i]);
		if (ft_strncmp(user_input, delim[i], length_delim) == 0
			&& !what_is_index_in(user_input, 0))
			return (i);
		i++;
	}
	return (-1);
}

