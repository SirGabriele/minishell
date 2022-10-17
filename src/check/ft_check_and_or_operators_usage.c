#include "../../includes/minishell.h"

static int	is_previous_syntax_valid(const char *user_input, int i)
{
	int	j;
	
	j = i - 1;
	while (j != 0 && !((user_input[j] == '&' && user_input[j - 1] == '&')
		|| (user_input[j] == '|' && user_input[j - 1] == '|')))
	{
		if (ft_isalnum(user_input[j]) == 0)
			j--;
		else
			return (0);
	}
	if (j == 0 || ((user_input[j] == '&' && user_input[j - 1] == '&')
		|| (user_input[j] == '|' && user_input[j - 1] == '|')))
		return (-1);
	return (0);
}

/************************************************************/
/*															*/
/*	Verifies if '&&' or '||' operators have a valid string	*/
/*	before them												*/
/*															*/
/*	Parameters:												*/
/*		user_input - line from the terminal         		*/
/*	Return:													*/
/*		0 - both are valid									*/
/*		1 - one or both string aren't valid					*/
/*															*/
/************************************************************/
int	ft_check_syntax_before_operators(const char *user_input)
{
	int		i;

	i = 0;
	while (user_input[i] != '\0')
	{
		if ((user_input[i] == '&' && user_input[i + 1] == '&')
			|| (user_input[i] == '|' && user_input[i + 1] == '|'))
		{
			if (is_previous_syntax_valid(user_input, i) == -1)
			{
				ft_printf_error("bash: syntax error near unexpected"\
					" token `%c%c'\n", user_input[i], user_input[i + 1]);
				highlight_syntax_error(user_input, i, i + 1);
				return (-1) ;
			}
		}
		i++;
	}
	return (0);
}

int	ft_are_all_and_or_operators_closed(const char *user_input)
{
	int	i;

	i = 0;
	while (user_input[i])
	{
		if ((user_input[i] == '&' && user_input[i + 1] == '&')
			|| (user_input[i] == '|' && user_input[i + 1] == '|'))

		{
			while (ft_isalnum(user_input[i]) == 0 && user_input[i] != '\0')
				i++;
			if (user_input[i] == '\0')
				return (-1);
		}
		i++;
	}
	return (0);
}
