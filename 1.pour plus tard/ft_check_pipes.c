#include "../../includes/minishell.h"

/********************************************************************/
/*                                                     				*/
/*  Determines if the syntax before the pipe is valid or not		*/
/*                                                     	 			*/
/*  Parameters:														*/
/*		user_input - line from the terminal							*/
/*		i - index of the operator found								*/
/*  Return:															*/
/*		0 - syntax is valid											*/
/*	   -1 - syntax is not valid										*/
/********************************************************************/
/*int	is_previous_syntax_valid(const char *user_input, int i)//A ajouter dans utils
{
	int	booly;

	if (i == 0)
		return (-1);
	booly = -1;
	i--;
	while (i >= 0 && user_input[i] != '|' && user_input[i] != '<' && user_input[i] != '>')
	{
		if ((user_input[i] >= 9 && user_input[i] <= 13) || user_input[i] == ' ')
			booly = -1;
		else
		{
			booly = 0;
			break ;
		}
		i--;
	}
	return (booly);
}*/

/************************************************************/
/*															*/
/*	Verifies if '|' operators have a valid string			*/
/*	before them												*/
/*															*/
/*	Parameters:												*/
/*		user_input - line from the terminal         		*/
/*		i - index of the pipe found							*/
/*	Return:													*/
/*		0 - it is valid										*/
/*		1 - it isn't valid									*/
/************************************************************/
/*int	ft_check_syntax_before_character(const char *user_input, int i, const char *character)// A ajouter dans utils
{
	if (is_previous_syntax_valid(user_input, i) == -1)
	{
		ft_printf_fd(2, "minishell: syntax error near unexpected"\
			" token `%s'\n", character);
		highlight_syntax_error(user_input, i, i);
		return (-1);
	}
	return (0);
}*/
