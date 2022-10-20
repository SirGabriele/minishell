#include "../../includes/minishell.h"

/********************************************************************/
/*                                                     				*/
/*  Determines if the environment variable found is between			*/
/*	single/double quotes or not in any sort of quotes				*/
/*                                                     	 			*/
/*  Parameters:														*/
/*		user_input - line from the terminal							*/
/*		i - index of the '$' symbol found							*/
/*  Return:															*/
/*		0 - env_variable is between double quotes or alone			*/
/*		1 - env_variable is between single quotes					*/
/********************************************************************/

int	check_space(char *user_input, int index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (user_input[i] == ' ' && user_input[i])
		i++;
	while (j + i < index - 1 && user_input[i + j])
		j++;
	while (j && user_input[i + j] == ' ')
		j--;
	return (j);
}

int	what_is_character_in(const char *user_input, int i)
{
	int		j;
	char	cpy;

	j = 0;
	while (user_input[j] != '\0')
	{
		if (user_input[j] == '\"' || user_input[j] == '\'')
		{
			cpy = user_input[j];
			j++;
			while (user_input[j] != cpy && user_input[j] != '\0')
				j++;
			if (j > i && cpy == '\'')
				return (0);
			else if (j > i && cpy == '\"')
				return (1);
		}
		j++;
	}
	return (2);
}
/*
char	*get_tmp_without_quotes(char *tmp, char *user_input)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (user_input[j])
	{
		if (user_input[j] == '\'' || user_input[j] == '\"')
		{
			k = j;
			j++;
			while (user_input[j] !=  user_input[k])
			{
				tmp[i] = user_input[j];
				i++;
				j++;
			}
			j++;
		}
		else
		{
			tmp[i] = user_input[j];
			i++;
			j++;
		}	
	}
	tmp[i] = '\0';
	return (tmp);
}*/
