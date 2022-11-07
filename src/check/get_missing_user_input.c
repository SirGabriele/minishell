#include "../../includes/minishell.h"

static char	*join_strings_add_space(char **user_input, char *missing_input)
{
	char	*new_user_input;
	char	*tmp;

	tmp = ft_strjoin_free_first(*user_input, " ");
	new_user_input = ft_strjoin_free_first(tmp, missing_input);
	return (new_user_input);
}

char	*get_missing_user_input(char **user_input)
{
	char	*new_user_input;
	char	*missing_input;
	char	*err_msg;

	err_msg = "minishell: syntax error: unexpected end of file\nexit\n";
	missing_input = NULL;
	while (1)
	{
		missing_input = readline("> ");
		if (!missing_input)
		{
			write(2, err_msg, ft_strlen(err_msg));
			return (NULL);
		}
		else if (ft_strlen(missing_input) > 0)
		{
			new_user_input = join_strings_add_space(user_input, missing_input);
			add_history(new_user_input);
			return (new_user_input);
		}
	}
	return (new_user_input);
}
