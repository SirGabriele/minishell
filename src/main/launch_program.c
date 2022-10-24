#include "../../includes/minishell.h"
/*
static int	ft_check_closed_operators_and_pipes(char **user_input)
{
	while (are_all_and_or_operators_closed(*user_input) == -1
		|| are_all_pipes_closed(*user_input) == -1)
	{
		*user_input = get_missing_user_input(user_input);
		if (*user_input == NULL)
			return (-1);
		else
			continue ;
	}
	return (0);
}

static int	ft_check_syntax_before_operators_and_pipes(char **user_input)
{
	if (ft_check_syntax_before_operators(*user_input) == -1)
		return (-1);
	if (ft_check_syntax_before_pipes(*user_input) == -1)
		return (-1);
	return (0);
}

static int	ft_check_syntax_error(char **user_input)
{
	if (ft_check_isolated_quotes(*user_input) == -1)
		return (-1);
	if (ft_check_isolated_ampersands(*user_input) == -1)
		return (-1);
	if (ft_check_triple_and_or(*user_input) == -1)
		return (-1);
	if (ft_check_closed_operators_and_pipes(user_input) == -1)
		return (-1);
	if (ft_check_syntax_before_operators_and_pipes(user_input) == -1)
		return (-1);
	return (0);
}
*/
int	launch_program(char *user_input)
{
	t_cmd_ms	*commands;

	/*if (ft_check_syntax_error(user_input) == -1)
		return (-1);*/
	commands = init_struct_array(user_input);
	if (commands == NULL)
		return (-1);
	commands = parsing(commands, count_pipes(user_input));
	free_commands(commands, count_pipes(user_input) + 1);
	return (0);
}
