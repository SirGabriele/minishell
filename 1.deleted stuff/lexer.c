#include "../../includes/minishell.h"

/*static t_token_ms	identify_token(char **user_input, char **delimiters)
{
}*/

static void	fill_delimiters(char **delimiters)
{
	delimiters[0] = "(";
	delimiters[1] = ")";
	delimiters[2] = "<<";
	delimiters[3] = ">>";
	delimiters[4] = "<";
	delimiters[5] = ">";
	delimiters[6] = "||";
	delimiters[7] = "&&";
	delimiters[8] = "|";
	delimiters[9] = NULL;
}

int	lexer(t_token_ms **arr_tokens, const char *user_input)
{
	char	*delimiters[10];
	int	nb_tokens;
//	int		i;

	fill_delimiters(delimiters);
	nb_tokens = get_nb_tokens(user_input, delimiters);
	printf("%d\n", nb_tokens);
//	i = 0;
/*	while (*user_input != '\0')
	{
		while (ft_isspace(*user_input) == 1)
			user_input++;
//		arr_tokens[i] = identify_token(&user_input, delimiters);	
	}*/
	(void)arr_tokens;
	return (0);
}
