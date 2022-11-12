#include "../../includes/minishell.h"

t_tokens_ms	*get_token(char *user_input, int i)
{
	
}

char	*parsing(char *user_input, t_token_ms *arr_tokens)
{
	int		i;

	i = 0;
	arr_tokens = malloc((get_nb_tokens + 1) * sizeof(t_token_ms));
	if (!arr_tokens)
		return (-1);
	while (*user_input == ' ')
		user_input++;
	while (user_input[i])
	{
		if (user_input[i] == ' ' && !what_is_index_in(user_input, i))
		{
			arr_tokens = get_token(user_input, i);
			user_input += i;
			while (*user_input == ' ')
				user_input++;
		}
		else
			i++;
	}
}
