#include "../../includes/minishell.h"

/********************************************/
/*											*/
/*	Parameters:								*/
/*		user_input - line from the terminal	*/
/*		i - index of the quote to delete	*/
/*	Return:									*/
/*		MALLOC'ED line without the quote	*/
/*											*/
/********************************************/
static char	*delete_quote(char *user_input, int i)
{
	int		j;
	int		k;
	char	*dup;

	j = 0;
	k = 0;
	dup = ft_calloc(sizeof(char), ft_strlen(user_input));
	while (user_input[k] != '\0')
	{
		if (k == i)
			k++;
		else
		{
			dup[j] = user_input[k];
			j++;
			k++;
		}
	}
	dup[j] = '\0';
	return (dup);
}

static int	is_quote_closed(char *user_input, int i)
{
	int	j;
	
	j = i + 1;
	while (user_input[j] != user_input[i] && user_input[j] != '\0')
		j++;
	if (user_input[j] == '\0')
		return (-1);
	return (0);
}

/************************************************************/
/*															*/
/*	Detects all isolated quote and deletes it from the line	*/
/*															*/
/*	Parameters:												*/
/*		user_input - line from the terminal         		*/
/*	Return:													*/
/*		MALLOC'ED line without all isolated quotes			*/
/*															*/
/************************************************************/
static char	*delete_isolated_quotes(char *user_input)
{
	int		i;
	char	save;

	i = 0;
	while (user_input[i] != '\0')
	{
		if (user_input[i] == '\"' || user_input[i] == '\'')
		{
			save = user_input[i];
			if (is_quote_closed(user_input, i) == -1)
			{
				user_input = delete_quote(user_input, i);
				continue ;
			}
			i++;
			while (user_input[i] != save)
				i++;
		}
		i++;
	}
	return (user_input);
}

/************************************************************/
/*                                                          */
/*  Delete all the extremity quotes from the line 			*/
/*                                                          */
/*  Parameters:												*/
/*		user_input - line from the terminal					*/
/*	Example:												*/
/*		"he'll'o w'orl'd" -> he'll'o w'orl'd				*/
/*  Return:													*/
/*		line without extremity quotes						*/
/*                                                          */
/************************************************************/
/*static char	*delete_closed_quotes(char *user_input)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (user_input[i])
	{
		if (user_input[i] == '\'' || user_input[i] == '\"')
			j++;
		i++;
	}
	tmp = malloc((ft_strlen(user_input) - j + 1) * sizeof(char));
	tmp = get_tmp_without_quotes(tmp, user_input);
	free(user_input);// CHECK SI UTILE
	return (tmp);
}*/

char	*filter_cmd_line(char *user_input, char **env)
{
	user_input = delete_isolated_quotes(user_input);
	user_input = convert_var_with_dollar(user_input, env);
/*	while (user_input[i] != '\0')
	{
//		if (user_input[i] == '\"')
	//		user_input = convert_var_with_dollar(user_input, env);
		if (user_input[i] == '$')
			user_input = conver_var_with_dollar(user_input, env);
		i++;
	}*/
	//user_input = delete_closed_quotes(user_input);	
	return (user_input);
}
