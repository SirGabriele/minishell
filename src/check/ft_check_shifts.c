#include "../../includes/minishell.h"

int	ft_check_syntax_shifts(const char *user_input)
{
	int		i;

	i = 0;
	while (user_input[i] != '\0')
	{
		if ((user_input[i] == '>' && user_input[i + 1] == '>')
			&& (what_is_index_in(user_input, i) == 0))
		{
			printf(">> detected\n");
			if (ft_check_syntax_before_character(user_input, i, ">>") == -1)
				return (-1);
			i++;
		}
		else if ((user_input[i] == '>' || user_input[i] == '<')
			&& (what_is_index_in(user_input, i) == 0))
		{
			printf("> | < detected\n");
			if (ft_check_syntax_before_character(user_input, i, &user_input[i]) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}

int	ft_check_shift_association(const char *user_input)
{
	int	i;

	i = 0;
	while (user_input[i] != '\0')
	{
		if (((user_input[i] == '>' && user_input[i+ 1] == '<')
			|| (user_input[i] == '<' && user_input[i + 1] == '>'))
			&& what_is_index_in(user_input, i) == 0)
		{
			ft_printf("Syntax error\n");
			highlight_syntax_error(user_input, i + 1, i + 1);
			return (-1);
		}
		i++;
	}
	return (0);
}
