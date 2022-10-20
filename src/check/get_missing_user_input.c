#include "../../includes/minishell.h"

static char	*join_strings_and_add_space(char **user_input, char *missing_input)
{
	char	*new_user_input;
	char	*tmp;

	tmp = ft_strjoin(*user_input, " ");
	new_user_input = ft_strjoin(tmp, missing_input);
	free(tmp);
	return (new_user_input);
	
}

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
			new_user_input = join_strings_and_add_space(user_input, missing_input);
			free(*user_input);
			user_input = NULL;
			return (new_user_input);
		}
	}
	return (new_user_input);
}
