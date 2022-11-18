#include "../../includes/minishell.h"

static int	is_a_delimiter(const char *user_input, char **delimiters)
{
	int	i;
	int	length_delim;

	i = 0;
	while (delimiters[i] != NULL)
	{
		length_delim = ft_strlen(delimiters[i]);
		if (ft_strncmp(user_input, delimiters[i], length_delim) == 0)
			return (0);
		i++;
	}
	return (-1);
}

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
		{
			count++;
			i++; // probleme ici, si le delim fait que 1 seul caractere, i ne devrait pas sincrementer test "(d)";
		}
		if (ft_isprint(user_input[i]) == 1)
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
