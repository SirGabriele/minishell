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

int	lexer(t_token_ms *tokens, char *user_input)
{
	int		i;
	char	*delim[7];

	i = 0;
	fill_delimiters(delim);
	tokens = get_tokens(tokens, user_input, delim);
	return (0);
}
