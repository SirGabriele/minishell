#include "../../includes/minishell.h"

static void	fill_delimiters(char **delim)
{
	delim[0] = "(";
	delim[1] = ")";
	delim[2] = "<";
	delim[3] = ">";
	delim[4] = "&&";
	delim[5] = "|";
	delim[6] = NULL;
}

t_token_ms	*lexer(char *user_input)
{
	t_token_ms	*tokens;
	int			i;
	char		*delim[7];

	i = 0;
	fill_delimiters(delim);
	tokens = get_tokens(user_input, delim);
	if (!tokens)
		return (NULL);
	return (tokens);
}
