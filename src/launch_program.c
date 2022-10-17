#include "../includes/minishell.h"

static int	ft_check_syntax_error(char **user_input)
{
	if (ft_check_quotes(*user_input) == -1)
		return (-1);
	while (ft_are_all_and_or_operators_closed(*user_input) == -1)
	{
		*user_input = get_missing_user_input(user_input);
		if (*user_input == NULL)
			return (-1);
	}
	if (ft_check_syntax_before_operators(*user_input) == -1)
		return (-1);
/*	if (ft_are_all_pipes_closed(user_input) == -1)
		user_input = get_missing_user_input(user_input);
	if (ft_check_pipes_usage(user_input) == -1)
		return (-1);*/
	return (0);
}

int	launch_program(char **user_input)
{
	if (ft_check_syntax_error(user_input) == -1)
		return (-1);
//	if (init_struct_array(user_input) == -1)
//		return (-1);
	return (0);
}
