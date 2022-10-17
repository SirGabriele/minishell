#include "../../includes/minishell.h"

/********************************************************************/
/*                                                     				*/
/*  Determines if the triplet is between single/double quotes		*/
/*	or not in any sort of quotes									*/
/*                                                     	 			*/
/*  Parameters:														*/
/*		user_input - line from the terminal							*/
/*		i - index of the triplet found								*/
/*  Return:															*/
/*		0 - triplet is alone										*/
/*	   -1 - triplet is between single or double 					*/
/********************************************************************/
static int	what_is_triplet_in(const char *user_input, int i)
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
		else if ((user_input[j] == '&' || user_input[j] == '|')
			&& (user_input[j] == '&' || user_input[j + 1] == '|')
			&& (user_input[j + 2] == '&' || user_input[j + 2] == '|'))
			return (0);
		j++;
	}
	return (0);
}

/************************************************************/
/*															*/
/*	Detects all triple association of '&' and '|'			*/
/*															*/
/*	Parameters:												*/
/*		user_input - line from the terminal         		*/
/*	Return:													*/
/*		0 - no isolated ampersand is detected				*/
/*		1 - an isolated ampersand is detected				*/
/*															*/
/************************************************************/
int	ft_check_triple_and_or(const char *user_input)
{
	int		i;

	i = 0;
	while (user_input[i] != '\0')
	{
		if ((user_input[i] == '&' || user_input[i] == '|')
			&& (user_input[i + 1] == '&' || user_input[i + 1] == '|')
			&& (user_input[i + 2] == '&' || user_input[i + 2] == '|')
			&& (what_is_triplet_in(user_input, i) == 0))
		{
				ft_printf_error("minishell: syntax error near unexpected"\
					" token `%c'\n", user_input[i + 2]);
				highlight_syntax_error(user_input, i, i + 2);
				return (-1) ;
		}
		i++;
	}
	return (0);
}
