#include "../../includes/minishell.h"

static void	print_error_message(const char *user_input, int i, int nb_operators)
{
	if (nb_operators % 2 == 0)
	{
		ft_printf_error("minishell: syntax error near unexpected"\
			" token `%c%c'\n", user_input[i + nb_operators - 2], user_input[i + nb_operators - 1]);
		highlight_syntax_error(user_input, i + nb_operators - 2, i + nb_operators - 1);
		return ;
	}
	else if (nb_operators % 2 == 1)
	{
		ft_printf_error("minishell: syntax error near unexpected"\
			" token `%c'\n", user_input[i + nb_operators - 1]);
		highlight_syntax_error(user_input, i + nb_operators - 1, i + nb_operators - 1);
		return ;
	}
}

/********************************************************************/
/*                                                     				*/
/*  Determines if the association is between single/double quotes	*/
/*	or not in any sort of quotes									*/
/*                                                     	 			*/
/*  Parameters:														*/
/*		user_input - line from the terminal							*/
/*		i - index of the triplet found								*/
/*  Return:															*/
/*		0 - assocation is alone										*/
/*	   -1 - association is between single or double 				*/
/********************************************************************/
static int	what_is_association_in(const char *user_input, int i)
{
	int		j;
	char	c;

	j = 0;
	while (user_input[j] != '\0')
	{
		if (user_input[j] == '\"' || user_input[j] == '\'')
		{
			c = user_input[j];
			j++;
			while (user_input[j] != c && user_input[j] != '\0')
				j++;
			if (j > i)
				return (-1);
		}
		else if (j == i)
			break ;
		j++;
	}
	return (0);
}

static int	how_many_operators_in_a_row(const char *user_input, int i)
{
	int	j;
	int	nb_operators;

	j = i;
	nb_operators = 0;
	while ((user_input[j] == '&' || user_input[j] == '|')
		&& (user_input[j] != '\0'))
	{
		nb_operators++;
		j++;
	}
	return (nb_operators);
}

/****************************************************************/
/*																*/
/*	Detects all if more than two '&' and '|' are in a row		*/
/*																*/
/*	Parameters:													*/
/*		user_input - line from the terminal         			*/
/*	Return:														*/
/*		0 - not more than two in a row							*/
/*		1 - more than two in a row								*/
/****************************************************************/
int	ft_check_more_than_two_and_or(const char *user_input)
{
	int	i;
	int	nb_operators;

	i = 0;
	while (user_input[i] != '\0')
	{
		if ((user_input[i] == '&' || user_input[i] == '|')
			&& (how_many_operators_in_a_row(user_input, i) > 2)
			&& (what_is_association_in(user_input, i) == 0))
		{
			nb_operators = how_many_operators_in_a_row(user_input, i);
			print_error_message(user_input, i, nb_operators);
			return (-1);
		}
		i++;
	}
	return (0);
}
