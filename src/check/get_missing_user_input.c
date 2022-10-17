#include "../../includes/minishell.h"

char	*get_missing_user_input(char **user_input)
{
	char	*new_user_input;
	char	*missing_input;

	missing_input = NULL;
	while (1)
	{
		missing_input = readline("> ");
		if (!missing_input)
		{
			write(1, "exit\n", 5);
			return (NULL);
		}
		else if (ft_strlen(missing_input) > 0)
		{
			new_user_input = ft_strjoin(*user_input, missing_input);
			free(*user_input);
			user_input = NULL;
			return (new_user_input);
		}
	}
	return (new_user_input);
}
