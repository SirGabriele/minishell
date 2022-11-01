#include "../../includes/minishell.h"

/********************************************************************/
/*                                                     				*/
/*  Determines if the index is between single/double quotes			*/
/*	or not in any sort of quotes									*/
/*                                                     	 			*/
/*  Parameters:														*/
/*		user_input - line from the terminal							*/
/*		i - index of the character to check							*/
/*  Return:															*/
/*		0 - character is alone										*/
/*	   -1 - character is between single or double quotes			*/
/********************************************************************/
int	what_is_index_in(const char *user_input, int i)//A ajouter dans utils
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
			return (0);
		j++;
	}
	return (0);
}

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
int	is_previous_syntax_valid(const char *user_input, int i)//A ajouter dans utils
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
}

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
int	ft_check_syntax_before_character(const char *user_input, int i, const char *character)// A ajouter dans utils
{
	if (is_previous_syntax_valid(user_input, i) == -1)
	{
		ft_printf_error("minishell: syntax error near unexpected"\
			" token `%s'\n", character);
		highlight_syntax_error(user_input, i, i);
		return (-1) ;
	}
	return (0);
}

int	are_all_pipes_closed(const char *user_input)
{
	int	i;

	i = 0;
	while (user_input[i])
	{
		if ((user_input[i] == '|' && user_input[i + 1] != '|')
			&& (user_input[i - 1] != '|'))
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
