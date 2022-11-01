#include "../../includes/minishell.h"

/********************************************************************/
/*                                                     				*/
/*  Determines if the ampersand is between single/double quotes		*/
/*	or not in any sort of quotes									*/
/*                                                     	 			*/
/*  Parameters:														*/
/*		user_input - line from the terminal							*/
/*		i - index of the ampersand found							*/
/*  Return:															*/
/*		0 - ampersand is alone										*/
/*	   -1 - ampersand is between single or double 					*/
/********************************************************************/
static int	what_is_ampersand_in(const char *user_input, int i)
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
		else if (user_input[j] == '&' && user_input[j + 1] != '&'
			&& user_input[j - 1] != '&')
			return (0);
		j++;
	}
	return (0);
}

/************************************************************/
/*															*/
/*	Detects all isolated ampersands 						*/
/*															*/
/*	Parameters:												*/
/*		user_input - line from the terminal         		*/
/*	Return:													*/
/*		0 - no isolated ampersand is detected				*/
/*		1 - an isolated ampersand is detected				*/
/*															*/
/************************************************************/
int	ft_check_isolated_ampersands(const char *user_input)
{
	int		i;

	i = 0;
	while (user_input[i] != '\0')
	{
		if (user_input[i] == '&' && what_is_ampersand_in(user_input, i) == 0)
		{
				ft_printf("minishell syntax error\n"); //remplacer avec ft_printf_fd
				highlight_syntax_error(user_input, i, i);
				return (-1) ;
		}
		i++;
	}
	return (0);
}
