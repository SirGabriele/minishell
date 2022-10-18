#include "../../includes/minishell.h"

/********************************************************************/
/*                                                     				*/
/*  Determines if the pipe is between single/double quotes			*/
/*	or not in any sort of quotes									*/
/*                                                     	 			*/
/*  Parameters:														*/
/*		user_input - line from the terminal							*/
/*		i - index of the operator found								*/
/*  Return:															*/
/*		0 - pipe is alone											*/
/*	   -1 - pipe is between single or double quotes					*/
/********************************************************************/
static int	what_is_pipe_in(const char *user_input, int i)
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
		else if (user_input[j] == '|' && user_input[j + 1] != '|')
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
static int	is_previous_syntax_valid(const char *user_input, int i)
{
	int	j;
	int	booly;

	j = 0;
	while (j <= i)
	{
		if (ft_isalnum(user_input[j]) == 1)
			booly = 0;
		if (user_input[j] == '|' && user_input[j + 1] != '|')
		{
			booly = -1;
			j++;
		}
		j++;
	}
	return (booly);	
}

/*static int	is_previous_syntax_valid(const char *user_input, int i)
{
	int	j;
	
	j = i - 1;
	while (j != 0 && !((user_input[j] == '|' && user_input[j - 1] != '|')
		|| (user_input[j] == '&' && user_input[j - 1] == '&')
		|| (user_input[j] == '|' && user_input[j - 1] == '|')))
	{
		if (ft_isalnum(user_input[j]) == 0)
			j--;
		else
			return (0);
	}
	if (j == 0 || (user_input[j] == '|' && user_input[j - 1] != '|')
		|| (user_input[j] == '&' && user_input[j - 1] == '&')
		|| (user_input[j] == '|' && user_input[j - 1] == '|'))
		return (-1);
	return (0);
}*/

/************************************************************/
/*															*/
/*	Verifies if '|' operators have a valid string			*/
/*	before them												*/
/*															*/
/*	Parameters:												*/
/*		user_input - line from the terminal         		*/
/*	Return:													*/
/*		0 - it is valid										*/
/*		1 - it isn't valid									*/
/************************************************************/
int	ft_check_syntax_before_pipes(const char *user_input, int i)
{
	if ((what_is_pipe_in(user_input, i) == 0)
		&& (is_previous_syntax_valid(user_input, i) == -1))
	{
		ft_printf_error("minishell: syntax error near unexpected"\
			" token `|'\n");
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
