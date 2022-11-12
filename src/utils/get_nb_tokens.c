#include "../../includes/minishell.h"

/********************************************************************/
/*                                                     				*/
/*  Calculates the amout of tokens in user_input					*/
/*                                                     	 			*/
/*  Parameters:														*/
/*		user_input - line from the terminal							*/
/*																	*/
/*  Return:															*/
/*		The number of tokens										*/
/*																	*/
/********************************************************************/
int	get_nb_tokens(const char *user_input, char **delimiters)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (user_input[i] != '\0')
	{
		while (ft_isspace(user_input[i]) == 1)
			i++;
		if (is_a_delimiter(user_input + i, delimiters) == 0)
			count++;
		else if (ft_isprint(user_input[i]) == 1)
		{
			count++;
			while (is_a_delimiter(user_input + i, delimiters) != 0
				&& user_input[i] != '\0')
				i++;
			continue ;
		}
		i++;
	}
	return (count);
}
//V1
/*int	get_nb_tokens(const char *user_input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (user_input[i] != '\0')
	{
		while (ft_isspace(user_input[i]) == 1)
			i++;
		if (user_input[i] == '|' && user_input[i + 1] != '|'
			&& what_is_index_in(user_input, i) == 0)
			count++;
		else if (user_input[i] == '<' && user_input[i + 1] != '<'
			&& what_is_index_in(user_input, i) == 0)
			count++;
		else if (user_input[i] == '>' && user_input[i + 1] != '>'
			&& what_is_index_in(user_input, i) == 0)
			count++;
		else if (user_input[i] == '(' && what_is_index_in(user_input, i) == 0)
			count++;
		else if (user_input[i] == ')' && what_is_index_in(user_input, i) == 0)
			count++;
		else if (user_input[i] == '<' && user_input[i + 1] == '<'
			&& what_is_index_in(user_input, i) == 0)
		{
			i++;
			count++;
		}
		else if (user_input[i] == '>' && user_input[i + 1] == '>'
			&& what_is_index_in(user_input, i) == 0)
		{
			i++;
			count++;
		}
		else if (user_input[i] == '&' && user_input[i + 1] == '&'
			&& what_is_index_in(user_input, i) == 0)
		{
			i++;
			count++;
		}
		else if (user_input[i] == '|' && user_input[i + 1] == '|'
			&& what_is_index_in(user_input, i) == 0)
		{
			i++;
			count++;
		}
		i++;
		//missing string
	}
	return (count);
}*/
