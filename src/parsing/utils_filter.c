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

int	character_emplacement(const char *user_input, int i)
{
	int		j;
	char	k;

	j = 0;
	while (user_input[j] != '\0')
	{
		if (user_input[j - 1] == '\"' || user_input[j - 1] == '\'')
		{
			k = j - 1;
			while (user_input[j] != user_input[k] && user_input[j] != '\0')
				j++;
			if (j == k + 1 && user_input[j] == user_input[k])
				return (1);
			else if (j == k + 1 && user_input[j] == user_input[k])
				return (2);
			else if (j > i && user_input[j] == '\'')
				return (3);
			else if (j > i && user_input[j] == '\"')
				return (4);
		}
		j++;
	}
	return (0);
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
