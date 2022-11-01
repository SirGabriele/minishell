#include "../../includes/minishell.h"

/*static int	how_many_shifts_in_a_row(const char *user_input, int i)
{
	int	j;

	j = 0;
	while (user_input[i + j] == '<' || user_input[i + j] == '>')
		j++;
	return (i + j);
}*/

int	ft_check_syntax_shifts(const char *user_input)
{
	int		i;

	i = 0;
	while (user_input[i] != '\0')
	{
		if ((user_input[i] == '>' && user_input[i + 1] == '>')
			&& (what_is_index_in(user_input, i) == 0))
		{
			if (ft_check_syntax_before_character(user_input, i, ">>") == -1)
				return (-1);
			i++;
		}
		else if (((user_input[i] == '>' && user_input[i] != '>')
			|| (user_input[i] == '<' && user_input[i] != '<'))
			&& (what_is_index_in(user_input, i) == 0))
		{
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
//	int	j;

	i = 0;
//	j = 0;
	while (user_input[i] != '\0')
	{
		if (((user_input[i] == '>' && user_input[i+ 1] == '<')
			|| (user_input[i] == '<' && user_input[i + 1] == '>'))
			&& what_is_index_in(user_input, i) == 0)
		{
			ft_printf("minishell syntax error\n");
			highlight_syntax_error(user_input, i + 1, i + 1);
			return (-1);
		}
/*		if ((user_input[i] == '<' && user_input[i] != '<')
			|| (user_input[i] == '>' && user_input[i] != '>'))
		{
			j = how_many_shifts_in_a_row(user_input, i);
			if (j > 2)
			{
				ft_printf("minishell syntax error\n");
				highlight_syntax_error(user_input, i, i + j - 1);
				return (-1);
			}
		}*/
		i++;
	}
	return (0);
}
