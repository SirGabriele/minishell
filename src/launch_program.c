#include "../includes/minishell.h"

static int	ft_check_closed_pipes(char **user_input)
{
	while (are_all_pipes_closed(*user_input) == -1)
	{
		*user_input = get_missing_user_input(user_input);
		if (*user_input == NULL)
			return (-1);
		else
			continue ;
	}
	return (0);
}

static int	ft_check_syntax_pipes(const char *user_input)
{
	int	i;

	i = 0;
	while (user_input[i] != '\0')
	{
/*		if (user_input[i] == '|' && user_input[i + 1] == '|'
			&& (what_is_index_in(user_input, i)) == 0)
		{
			ft_printf("Syntax error\n");// changer tous les printf end printf_fd
			highlight_syntax_error(user_input, i + 1, i + 1);
			return (-1);
		}*/
		if (user_input[i] == '|' && what_is_index_in(user_input, i) == 0)
		{
			if (ft_check_syntax_before_character(user_input, i, "|") == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}

static int	ft_check_syntax_error(char **user_input)
{
	if (ft_check_isolated_quotes(*user_input) == -1)
		return (-1);
	if (ft_check_isolated_ampersands(*user_input) == -1)
		return (-1);
	if (ft_check_shift_association(*user_input) == -1)
		return (-1);
	if (ft_check_closed_pipes(user_input) == -1)
		return (-1);
	if (ft_check_syntax_pipes(*user_input) == -1)
		return (-1);
	if (ft_check_syntax_shifts(*user_input) == -1)
		return (-1);
	return (0);
}

int	launch_program(char **user_input)
{
	if (ft_check_syntax_error(user_input) == -1)
		return (-1);
//	*user_input = add_spaces_around_pipes_and_shifts(user_input);
//	if (init_struct_array(user_input) == -1)
//		return (-1);
	return (0);
}
