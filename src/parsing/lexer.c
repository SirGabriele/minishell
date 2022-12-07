#include "../../includes/minishell.h"

static void	fill_delimiters(char **delim)
{
	delim[0] = "(";
	delim[1] = ")";
	delim[2] = "<<";
	delim[3] = ">>";
	delim[4] = "<";
	delim[5] = ">";
	delim[6] = "||";
	delim[7] = "|";
	delim[8] = "&&";
	delim[9] = NULL;
}

/*void	print_tokens(t_token_ms *tokens)
{
	while (tokens)
	{
		ft_printf("%s\n", tokens->content);
		tokens = tokens->next;
	}
}*/

t_token_ms	*lexer(char *user_input, char **env)
{
	t_token_ms	*tokens;
	char		*delim[10];

	fill_delimiters(delim);
	tokens = get_tokens(user_input, delim, env);
	if (!tokens)
		return (NULL);
	//print_tokens(tokens);//a supprimer
	return (tokens);
}
